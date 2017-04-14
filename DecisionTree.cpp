//============================================================================
// Name        : DecisionTree.cpp
// Author      : Greg Climer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
//#include "decisionNode.h"

using namespace std;


int main() {
	list<bool>* individual;
	list<list <bool> > population;

	list<list <bool> >::iterator popit;
	list<bool>::iterator indit;

	bool instance[4][3] = 	{{false, true, true},
							{true, false, true},
							{false, false, false},
							{true, true, true}};

	/*individual = new list<bool>;
	population.push_back(*individual);
	popit = population.begin();*/

	for (int i =0; i < 4; i++){
		individual = new list<bool>;
		population.push_front(*individual);
		popit = population.begin();
		for (int k = 0; k < 3; k++){
			popit->push_back(instance[i][k]);
		}
		popit++;
	}

	popit = population.begin();

	for (int i =0; i < 4; i++){
		indit = popit->begin();
		for (int k = 0; k < 3; k++){
			cout << *indit;
			indit++;
		}
		cout << endl;
		popit++;
	}

	cout << endl;
	popit = population.end();
	popit--;

	indit = popit->begin();
	cout << *indit;
	indit++;
	cout << *indit;
	indit = --popit->end();
	cout << *indit;





}
