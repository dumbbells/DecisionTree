/*
 * decisionNode.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#include "decisionNode.h"
using namespace std;

bool decisionNode::isHomogenous(list<list <bool> > population){
	return false;
}
int decisionNode::findFeature(list<list <bool> > population){
	return 0;
}


decisionNode::decisionNode(list<list <bool> > population) {
	if (isHomogenous(population)){
		leafNode = true;
		popit = population.begin();
		indit = --popit->end();
		decision = *indit;
	}
	else{
		leafNode = false;
		feature = findFeature(population);

	}

}

//decisionNode::~decisionNode() {
	// TODO Auto-generated destructor stub
//}




