/*
 * helloWorld.cpp
 *
 * By Ryan Owens
 *
 * For CS438 
 * 
 * Created on 01/13/2018
 *
 * Runs a basic Block World example
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

#define DEBUG false

using namespace std;

int n = 0;
vector<vector<int>>* piles;
typedef struct operation {
	string type;
	int from;
	string modifier;
	int to;
};
queue<operation>* operations;

void readFile(string filename);
void performOperations();
void move(int from, string modifier, int to);
void pile(int from, string modifier, int to);
void printPiles(ostream& out);
vector<int>* findPileWith(int item);
int main (int argc, char** argv)
{
	// read and interpret input file
	if (argc < 2) {
		cerr << "Input filename not specified " << endl;
		exit(1);
	}
	readFile(argv[1]);
	// run through commands
	performOperations();
	// output piles
	ofstream file("blockOut.txt");
	printPiles(file);
	// perform cleanup
	delete(piles);
	piles = nullptr;
	delete(operations);
	operations = nullptr;
	system("pause");
	return 0;
}

void readFile(string filename) {
	ifstream infile;
	infile.open(filename);
	if (!infile) {
		cerr << "Could not open the file: " << filename << endl;
		system("pause");
		exit(1);
	}
	operations = new queue<operation>();
	string line;
	// Get the number of blocks
	infile >> n;
	getline(infile, line);
	while (getline(infile, line)) {
		operation op;
		istringstream iss(line);
		vector<string> parsed(istream_iterator<string>{iss}, istream_iterator<string>());
		if (parsed.size() < 3 && parsed.at(0) == "quit") {
			op.type = "quit";
			operations->push(op);
		}
		else if(parsed.size() == 4){
			op.type = parsed.at(0);
			op.from = stoi(parsed.at(1));
			op.modifier = parsed.at(2);
			op.to = stoi(parsed.at(3));
			if (op.from != op.to) {
				operations->push(op);

			}
		}
		else {
			cerr << "Unknown Command: " << line << endl;
			delete(operations);
			operations = nullptr;
			system("pause");
			exit(1);
		}
	}
	piles = new vector<vector<int>>(n);
	for (int i = 0; i < n; i++)
	{
		piles->at(i).push_back(i);
	}
}

void performOperations() {
	operation op = operations->front();
	operations->pop();
	while (op.type != "quit") {
		if (DEBUG) {
			cout << op.type << " " << op.from << " " << op.modifier << " " << op.to << endl;
		}
		if (op.type == "move") {
			move(op.from, op.modifier, op.to);
		}
		else if (op.type == "pile") {
			pile(op.from, op.modifier, op.to);
		}
		else {
			cerr << "Unknown operation type";
			system("pause");
		}
		op = operations->front();
		operations->pop();
		if (DEBUG) {
			printPiles(std::cout);
			cout << endl << endl;
		}
	}
}

void move(int from, string modifier, int to) {
	// find pile containing From
	vector<int>* fromPile = findPileWith(from);
	vector<int>* toPile = findPileWith(to);
	if (fromPile == nullptr) {
		cerr << "Could not find the pile with " << from << endl;
		return;
	}
	if (toPile == nullptr) {
		cerr << "Could not find the pile with " << to << endl;
		return;
	}

	if (fromPile == toPile) {
		return;
	}

	if (modifier == "onto") {
		// put items above 'A' onto their original piles
		for (int i = fromPile->size() - 1; i > -1; i--)
		{
			if (fromPile->at(i) == from) {
				break;
			}
			else {
				piles->at(i).push_back(fromPile->at(i));
				fromPile->pop_back();
			}
		}
		// put items above 'B' onto their original piles
		for (int i = toPile->size() - 1; i > -1; i--)
		{
			if (toPile->at(i) == to) {
				break;
			}
			else {
				piles->at(i).push_back(toPile->at(i));
				toPile->pop_back();
			}
		}

		// put 'A' onto 'B'
		toPile->push_back(from);
		fromPile->pop_back();
	}
	else if (modifier == "over") {
		// put items above 'A' onto their original piles
		for (auto i = fromPile->size() - 1; i > -1; i--)
		{
			if (fromPile->at(i) == from) {
				break;
			}
			else {
				piles->at(i).push_back(fromPile->at(i));
				fromPile->pop_back();
			}
		}

		// put 'A' onto 'B'
		toPile->push_back(from);
		fromPile->pop_back();
	}
	else {
		cerr << "Unknown move modifier" << endl;
		system("pause");
	}
}

void pile(int from, string modifier, int to) {
	// find pile containing From
	vector<int>* fromPile = findPileWith(from);
	vector<int>* toPile = findPileWith(to);
	if (fromPile == nullptr) {
		cerr << "Could not find the pile with " << from << endl;
		return;
	}
	if (toPile == nullptr) {
		cerr << "Could not find the pile with " << to << endl;
		return;
	}

	if (fromPile == toPile) {
		return;
	}
	
	stack<int> temp;

	if (modifier == "onto") {
		// put items above 'B' onto their original piles
		for (auto i = toPile->size() - 1; i > -1; i--)
		{
			if (toPile->at(i) == to) {
				break;
			}
			else {
				piles->at(i).push_back(toPile->at(i));
				toPile->pop_back();
			}
		}

		// Get all of the items above 'A' including 'A'
		while (fromPile->back() != from) {
			temp.push(fromPile->back());
			fromPile->pop_back();
		}
		temp.push(fromPile->back());
		fromPile->pop_back();
		
		// Put the items above 'A' including 'A' onto 'B' in the original order
		while (!temp.empty()) {
			toPile->push_back(temp.top());
			temp.pop();
		}
	}
	else if (modifier == "over") {
		// Get all of the items above 'A' including 'A'
		while (fromPile->back() != from) {
			temp.push(fromPile->back());
			fromPile->pop_back();
		}
		temp.push(fromPile->back());
		fromPile->pop_back();

		// Put the items above 'A' including 'A' onto 'B' in the original order
		while (!temp.empty()) {
			toPile->push_back(temp.top());
			temp.pop();
		}
	}
	else {
		cerr << "Unknown pile modifier" << endl;
	}
}

vector<int>* findPileWith(int item) {
	for (int i = 0; i < piles->size(); i++) {
		vector<int>* pile = &piles->at(i);
		if (find(pile->begin(), pile->end(), item) != pile->end()) {
			return pile;
		}
	}
	return nullptr;
}

void printPiles(ostream& out) {
	for (int i = 0; i < n; i++) {
		auto pile = piles->at(i);
		out << i << ":";
		for (int item : pile) {
			out << " " << item;
		}
		out << endl;
	}
}