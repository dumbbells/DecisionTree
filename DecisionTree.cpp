//============================================================================
// Name        : DecisionTree.cpp
// Author      : Greg Climer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <utility>
#include <fstream>
#include <string>
#include "decisionNode.h"

using namespace std;


int main() {
	//pointers for dynamically allocating pairs (feature #, data bool)
	pair<int, bool>* data;
	list<pair<int, bool> >* individual;

	list<list<pair<int, bool> > > population;
	decisionNode* tree;

	string fileName = "a.in";
	ifstream in;

	//popSize represents the number of samples at entry, complexity is the
	//length of the string associated with each sample dummy is simply used
	//for input purposes
	int popSize, complexity;
	int dummy;

	cout << "Enter the file you would like to read from: ";
	cin >> fileName;
	in.open(fileName);
	in >> complexity;
	in >> popSize;

	//loop that reads in data and pushes it into the appropriate list
	//& position
	for (int i = 0; i < popSize; i++){
		individual = new list<pair<int, bool> >;
		for (int ii = 0; ii <= complexity; ii++){
			in >> dummy;
			data = new pair<int, bool>(ii, dummy);
			individual->push_back(*data);
		}
		population.push_back(*individual);
	}

	//constructor that builds the tree recursively and returns
	//a pointer to the root node
	tree = new decisionNode(population);
	cout << "tree is completed\n";

	while (1){
		individual->clear();				//clear the list for next input
		cout << "enter a novel example of " << complexity
				<< ", or enter '2' to end:\n";
		for (int i = 0; i < complexity; i ++){
			cin >> dummy;
			if (dummy == 2) goto end;		//goto that exits the program
			data = new pair<int, bool>(i, dummy);
			individual->push_back(*data);
		}
		//call recursive function that returns the classification based on tree
		cout << "class is: " << tree->classify(*individual) << endl;
	}
	end:
	delete tree;
	population.clear();
	cout << "goodbye!\n";

	return 0;

}
