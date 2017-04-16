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
	pair<int, bool>* data;
	list<pair<int, bool> >* individual;
	list<list<pair<int, bool> > > population;
	decisionNode* tree;

	list<list<pair<int, bool> > >::iterator popit;
	list<pair<int, bool> >::iterator indit;

	string fileName = "a.in";
	ifstream in;
	int popSize, complexity;
	int dummy;

	cout << "Enter the file you would like to read from: ";
	//cin >> fileName;
	in.open(fileName);
	in >> complexity;
	in >> popSize;

	popit = population.begin();
	for (int i = 0; i < popSize; i++){
		individual = new list<pair<int, bool> >;
		for (int ii = 0; ii <= complexity; ii++){
			in >> dummy;
			data = new pair<int, bool>(ii, dummy);
			individual->push_back(*data);
		}
		population.push_back(*individual);
	}

	tree = new decisionNode(population);
	cout << "tree is completed\n";

	while (1){
		individual->clear();
		cout << "enter a novel example of " << complexity
				<< ", or enter '2' to end:\n";
		for (int i = 0; i < complexity; i ++){
			cin >> dummy;
			if (dummy == 2) goto end;
			data = new pair<int, bool>(i, dummy);
			individual->push_back(*data);
		}
		cout << "class is: " << tree->classify(*individual) << endl;
	}
	end:
	cout << "goodbye!\n";
	delete tree;
	population.clear();

	return 0;

}
