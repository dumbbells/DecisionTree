//============================================================================
// Name        : DecisionTree.cpp
// Author      : Greg Climer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "DecisionTree.h"

using namespace std;

int main() {
	list<bool>* individual;
	list<list <bool> > population;
	list<bool> l1, l2, l3, l4;
	list<bool>::iterator indit;
	list<list <bool> >::iterator popit;
	bool instance[4][3] = {{false, true, false},
							{true, false, true},
							{false, false, false},
							{true, true, true}};

	/*population.push_back(l1);
	population.push_back(l2);
	population.push_back(l3);
	population.push_back(l4);*/

	individual = new list<bool>;
	population.push_back(*individual);
	popit = population.begin();

	for (int i =0; i < 4; i++){
		individual = new list<bool>;
		population.push_back(*individual);
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



}
