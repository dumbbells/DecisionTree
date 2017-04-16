/*
 * decisionNode.h
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#ifndef DECISIONNODE_H_
#define DECISIONNODE_H_
#include <list>
#include <utility>
#include <iostream>
#include <math.h>

using namespace std;



class decisionNode {
	list<list <pair<int, bool> > > population;
	list<list<pair<int, bool> > >::iterator Lit;
	list<pair<int, bool> >::iterator lit;
	bool decision, leafNode;
	int feature;
	decisionNode *nodePtrF, *nodePtrT;

	void print();		//displays sample set
	void prepList();	//splits sample into two and creates new nodes
	bool findMode();	//finds the majority in sample's class
	bool isHomogenous();//ideal leaf node circumstance
	int findFeature();	//finds best feature to split on
	double getEntropy(list<pair<bool, bool> >, int);//calculates data
	double IGOnSplit(int);//gives findFeature data

public:
	//function to classify new examples
	bool classify(list<pair<int, bool> >);

	decisionNode(list<list <pair<int, bool> > >);
	~decisionNode();

};

#endif /* DECISIONNODE_H_ */

