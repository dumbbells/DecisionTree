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
	list<list<pair<int, bool> > >::iterator Lit;
	list<pair<int, bool> >::iterator lit;
	bool decision, leafNode;
	int feature;
	decisionNode *nodePtrF, *nodePtrT;

	void print(list<list <pair<int, bool> > >);
	void prepList(list<list<pair<int, bool> > >);
	double getEntropy(list<pair<bool, bool> >, int);
	double IGOnSplit(list<list <pair<int, bool> > > population,
			int feature);

public:
	decisionNode(list<list <pair<int, bool> > >);
	~decisionNode();

	bool isHomogenous(list<list <pair<int, bool> > >);
	int findFeature(list<list <pair<int, bool> > >);

};

#endif /* DECISIONNODE_H_ */

