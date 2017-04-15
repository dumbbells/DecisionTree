/*
 * decisionNode.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#include "decisionNode.h"
using namespace std;

bool decisionNode::isHomogenous(list<list <pair<int, bool> > > population){
	Lit = population.begin();
	lit = --Lit->end();
	decision = get<1>(*lit);
	for (; Lit != population.end(); Lit++){
		lit = --Lit->end();
		if (decision != get<1>(*lit))
			return false;
	}
	return true;
}
int decisionNode::findFeature(list<list <pair<int, bool> > > population){
	double infoGain = 0, maxGain = 0;
	int feature;
	lit = population.begin()->begin();

	for(;lit != --population.begin()->end();lit++){
		infoGain = IGOnSplit(population, get<0>(*lit));
		if (infoGain > maxGain){
			maxGain = infoGain;
			feature = get<0>(*lit);
		}
	}
	return feature;
}

double decisionNode::IGOnSplit(list<list <pair<int, bool> > > population, int feature){
	list<list<pair<int, bool> > >::iterator scan;
	scan = population.begin()->begin();
	//need to work entropy and information gain

	double info;
	int pos = 0, neg = 0;


	return 0;
}

decisionNode::decisionNode(list<list <pair<int, bool> > > population) {
	if (isHomogenous(population)){
		leafNode = true;
		Lit = population.begin();
		lit = Lit->begin();
		decision = get<1>(*lit);
		cout << "decision is: "<< get<1>(*lit) << endl;
	}
	else{
		cout << "Can not find decision\n";
		leafNode = false;
		feature = findFeature(population);

	}
}

//decisionNode::~decisionNode() {
	// TODO Auto-generated destructor stub
//}




