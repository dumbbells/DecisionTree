/*
 * decisionNode.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#include "decisionNode.h"
using namespace std;

bool decisionNode::isHomogenous(list<list <pair<int, bool> > > population){
	if (population.size() < 3) return true;
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

	cout << "attempting find feature\n";

	for(;lit != --population.begin()->end();lit++){
		cout << "next set \n";
		infoGain = IGOnSplit(population, get<0>(*lit));
		if (infoGain > maxGain){
			maxGain = infoGain;
			feature = get<0>(*lit);
		}
	}
	return feature;
}

double decisionNode::getEntropy(list<pair<bool, bool> > data, int totalPop){
	double value = 0,  size = data.size(), weight;
	int pos = 0, neg = 0;
	list<pair<bool, bool> >::iterator datait = data.begin();
	weight = data.size()/(double)totalPop;

	for (;datait != data.end(); datait++){
		get<1>(*datait)? pos++ : neg ++;
	}

	cout << "pos is " << pos;
	cout << "\t neg is " << neg;

	if(pos != 0){
		value = (-1 * (pos/size) * log2(pos/size));
		if (neg != 0){
			value -= ((neg/size) * log2(neg/size));
		}
	}
	else if (neg != 0) value = (-1 * (neg/size) * log2(neg/size));

	value *= weight;
	cout << "\tvalue is: " << value << endl;
	return value;
}

double decisionNode::IGOnSplit(list<list <pair<int, bool> > > population, int feature){
	int total = population.size();
	pair<bool, bool>* makeNew;
	list<pair<bool, bool> > splitDecisionT;
	list<pair<bool, bool> > splitDecisionF;
	list<pair<int, bool> >::iterator scan;
	Lit = population.begin();
	scan = Lit->begin();

	while (Lit != population.end()){
		//cout << "attempting IG onSplit\n";
		while (scan != Lit->end()){
			if (get<0>(*scan) == feature){
				makeNew = new pair<bool, bool>;
				get<0>(*makeNew) = get<1>(*scan);
				scan = --Lit->end();
				get<1>(*makeNew) = get<1>(*scan);
				get<0>(*makeNew)?splitDecisionT.push_back(*makeNew)
						:splitDecisionF.push_back(*makeNew);
				cout << "feature " << feature << ": " <<
						get<0>(*makeNew) << " " << get<1>(*makeNew) << endl;
			}
			scan++;
		}
		Lit++;
		scan = Lit->begin();
	}
	return (1 - (getEntropy(splitDecisionF, total) +
			getEntropy(splitDecisionT, total)));
}

void decisionNode::prepList(list<list<pair<int, bool> > > population){
	list<list<pair<int, bool> > > newList;
	list<pair<int, bool> >* indCopy;

	cout << "prepare to split\n";

	print(population);
	lit = population.begin()->begin();
	Lit = population.begin();



	while (Lit != population.end()){
		lit = Lit->begin();
		while (lit != --Lit->end()){
			if (get<0>(*lit) == feature){
				cout << "found the feature " << get<0>(*lit) << get<1>(*lit) << endl;
				if (get<1>(*lit) == false){
					Lit->erase(lit);
					indCopy = new list<pair<int, bool> >();
					lit = indCopy->begin();
					indCopy->insert(lit, Lit->begin(), Lit->end());
					newList.push_back(*indCopy);
					Lit = population.erase(Lit);
				}
				else {
					Lit++;
				}
				Lit->erase(lit);
				break;
			}
			lit++;
		}
	}
	nodePtrF = new decisionNode(newList);
	nodePtrT = new decisionNode(population);

}

void decisionNode::print(list<list <pair<int, bool> > > population){
	for (Lit = population.begin(); Lit != population.end(); Lit++){
		for (lit = Lit->begin(); lit != Lit->end(); lit++){
			cout << get<1>(*lit);
		}
		cout << endl;
	}
	Lit = population.begin();
}

decisionNode::decisionNode(list<list <pair<int, bool> > > population) {
	print(population);
	Lit = population.begin();
	if (isHomogenous(population) || Lit->size() <= 1){
		leafNode = true;
		lit = --Lit->end();
		decision = get<1>(*lit);
		cout << "decision is: "<< get<1>(*lit) << endl;
	}
	else{
		cout << "Can not find decision\n";
		leafNode = false;
		feature = findFeature(population);
		cout << "the feature to split on is: " << feature << endl;
		prepList(population);
	}
}

decisionNode::~decisionNode() {
	delete nodePtrF;
	delete nodePtrT;
}




