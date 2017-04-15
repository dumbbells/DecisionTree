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
#include "decisionNode.h"

using namespace std;


int main() {
	pair<int, bool>* data;
	list<pair<int, bool> >* individual;
	list<list<pair<int, bool> > > population;
	decisionNode* tree;

	list<list<pair<int, bool> > >::iterator popit;
	list<pair<int, bool> >::iterator indit;

	bool instance[4][3] = 	{{false, true, false},
							{true, false, true},
							{false, false, false},
							{true, true, true}};

	popit = population.begin();

	for (int i =0; i < 4; i++){
		individual = new list<pair<int, bool> >;

		for (int k = 0; k < 3; k++){
			data = new pair<int, bool>(k, instance[i][k]);
			individual->push_back(*data);
		}
		population.push_back(*individual);
	}

	popit = population.begin();

	for (int i =0; i < 4; i++){
		indit = popit->begin();
		for (int k = 0; k < 3; k++){
			cout << get<1>(*indit);
			indit++;
		}
		cout << endl;
		popit++;
	}

	tree = new decisionNode(population);

	delete tree;
	population.clear();


/*	cout << endl;
	popit = population.end();
	popit--;

	indit = popit->begin();
	cout << *indit;
	indit++;
	cout << *indit;
	indit = --popit->end();
	cout << *indit;



*/

}
