/*
 * decisionNode.h
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#ifndef DECISIONNODE_H_
#define DECISIONNODE_H_
#include <list>
using namespace std;

list<list <bool> >::iterator popit;
list<bool>::iterator indit;

class decisionNode {
//	list<list <bool> >::iterator popit;
//	list<bool>::iterator indit;
	bool decision, leafNode;
	int feature;
	//decisionNode *nodePtrF, *nodePtrT;

public:
	decisionNode(list<list <bool> >);
//	virtual ~decisionNode();

	bool isHomogenous(list<list <bool> >);
	int findFeature(list<list <bool> >);

};

#endif /* DECISIONNODE_H_ */

