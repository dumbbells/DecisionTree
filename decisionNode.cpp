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
	cout << "checking if node is a leaf..." << endl
			<< "all samples must match classification: " << decision << endl;
	for (; Lit != population.end(); Lit++){
		lit = --Lit->end();
		if (decision != get<1>(*lit)){
			cout << "sample is not a homogenous classification.\n";
			return false;
		}
	}
	cout << "sample classification is a match!\n";
	return true;
}
int decisionNode::findFeature(list<list <pair<int, bool> > > population){
	double infoGain = 0, maxGain = 0;
	int feature;
	lit = population.begin()->begin();

	cout << "attempting find feature\n";

	for(;lit != --population.begin()->end();lit++){
		cout << "Split based on " << get<0>(*lit) << "?\n";
		infoGain = IGOnSplit(population, get<0>(*lit));
		cout << "info gain is: " << infoGain << endl;
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

	cout << "positive is " << pos;
	cout << "\t negative is " << neg;

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
	int count = 0;

	while (Lit != population.end()){
		while (scan != Lit->end()){
			if (get<0>(*scan) == feature){
				makeNew = new pair<bool, bool>;
				get<0>(*makeNew) = get<1>(*scan);
				scan = --Lit->end();
				get<1>(*makeNew) = get<1>(*scan);
				get<0>(*makeNew)?splitDecisionT.push_back(*makeNew)
						:splitDecisionF.push_back(*makeNew);
				cout << "sample " << count << ": " <<  get<0>(*makeNew);
				cout << " with class: " << get<1>(*makeNew) << endl;
			}
			scan++;
		}
		count++;
		Lit++;
		scan = Lit->begin();
	}
	return (1 - (getEntropy(splitDecisionF, total) +
			getEntropy(splitDecisionT, total)));
}

void decisionNode::prepList(list<list<pair<int, bool> > > population){
	list<list<pair<int, bool> > > newList;
	list<pair<int, bool> >* indCopy;

	lit = population.begin()->begin();
	Lit = population.begin();

	while (Lit != population.end()){
		lit = Lit->begin();
		while (lit != --Lit->end()){
			if (get<0>(*lit) == feature){
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
	cout << "Split complete\n";
	nodePtrF = new decisionNode(newList);
	nodePtrT = new decisionNode(population);
}

void decisionNode::print(list<list <pair<int, bool> > > population){
	cout << "This node's Sample(s):\n";
	for (Lit = population.begin(); Lit != population.end(); Lit++){
		cout << "\t";
		for (lit = Lit->begin(); lit != Lit->end(); lit++){
			cout << get<1>(*lit) << " ";
		}
		cout << endl;
	}
}

bool decisionNode::classify(list<pair<int, bool> > novel){
	if (leafNode){
		return decision;
	}
	for (lit = novel.begin(); lit != --novel.end(); lit++){
		if (get<0>(*lit) == feature){
			if (get<1>(*lit)) return nodePtrT->classify(novel);
			else return nodePtrF->classify(novel);
		}
	}
	cout << "error in classification\n";
	exit(1);
}

bool decisionNode::findMode(list<list <pair<int, bool> > > population){
	int count = 0;
	bool value;
	for (Lit = population.begin(); Lit != population.end(); Lit++){
			lit = --Lit->end();
			get<1>(*lit) ? count++ : count--;
	}
	if (abs(count) != population.size())
		cout << "\t!!! There are inconsistencies in the sample!!!\n";
	count > 0 ? value = true : value = false;
	return value;
}

decisionNode::decisionNode(list<list <pair<int, bool> > > population) {
	print(population);
	if (Lit->size() <= 2){
		leafNode = true;
		decision = findMode(population);
		cout << "classification for this node due to lack of features is: "
				<< decision << endl;
	}
	else if (isHomogenous(population)){
		leafNode = true;
		cout << "classification for this node is: "<< decision << endl;
	}
	else{
		leafNode = false;
		feature = findFeature(population);
		cout << "the feature to split on is: " << feature << endl;
		prepList(population);
	}

	return;
}

decisionNode::~decisionNode() {
	delete nodePtrF;
	delete nodePtrT;
}




