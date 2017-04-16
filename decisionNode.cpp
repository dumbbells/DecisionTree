/*
 * decisionNode.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: gregclimer
 */

#include "decisionNode.h"
using namespace std;

//This function checks if the current sample set's classification is
//homogenous. If all of the last pieces of data are the same, we have
//a leaf node
bool decisionNode::isHomogenous(){
	Lit = population.begin();
	lit = --Lit->end();
	decision = get<1>(*lit);				//initializes class based on first pied of data
	cout << "checking if node is a leaf..." << endl
			<< "all samples must match classification: "
			<< decision << endl;
	for (; Lit != population.end(); Lit++){	//loops through each sample checking last
		lit = --Lit->end();					//piece of data
		if (decision != get<1>(*lit)){
			cout << "sample is not a homogenous classification.\n";
			return false;
		}
	}
	cout << "sample classification is a match!\n";
	return true;
}

//Function to find the feature that is best to split on
int decisionNode::findFeature(){
	double infoGain = 0, maxGain = 0;
	int feature;
	lit = population.begin()->begin();

	cout << "attempting find feature\n";

	for(;lit != --population.begin()->end();lit++){		//loops through each pair in the fist list
		cout << "Split based on " << get<0>(*lit) << "?\n";
		infoGain = IGOnSplit(get<0>(*lit));				//returns amount of info based on feature split
		cout << "info gain is: " << infoGain << endl;
		if (infoGain > maxGain){						//finds maximum gain and sets feature
			maxGain = infoGain;							//to the feature with max gain
			feature = get<0>(*lit);
		}
	}
	return feature;
}

//This function generates two additional lists to parse with getEntropy.
//It then returns 1 (all binary decision trees will have entropy of 1)
//minus the values returned from each list. The higher the number, the
//higher the info gain.
double decisionNode::IGOnSplit(int feature){
	int total = population.size();
	pair<bool, bool>* makeNew;
	list<pair<bool, bool> > splitDecisionT;
	list<pair<bool, bool> > splitDecisionF;
	list<pair<int, bool> >::iterator scan;
	Lit = population.begin();
	scan = Lit->begin();
	int count = 0;

	//function to find feature that is being tested, copies it, and then puts it into
	//new lists according to it's class
	while (Lit != population.end()){
		while (scan != Lit->end()){
			if (get<0>(*scan) == feature){
				makeNew = new pair<bool, bool>;
				get<0>(*makeNew) = get<1>(*scan);
				scan = --Lit->end();
				get<1>(*makeNew) = get<1>(*scan);
				get<0>(*makeNew) ? splitDecisionT.push_back(*makeNew)
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
	splitDecisionT.clear();
	splitDecisionF.clear();
	//final calculation for information gain
	return (1 - (getEntropy(splitDecisionF, total) +
			getEntropy(splitDecisionT, total)));
}

//Perhaps incorrectly named, This function does the calculation of the certainty
//based on the split list provided by IGOnSplit
double decisionNode::getEntropy(list<pair<bool, bool> > data, int totalPop){
	double value = 0,  size = data.size(), weight;
	int pos = 0, neg = 0;				//vars to keep track of how many neg and pos readings
	list<pair<bool, bool> >::iterator datait = data.begin();
	weight = data.size()/(double)totalPop;		//This is the fractional coefficient in the eq.

	for (;datait != data.end(); datait++){		//tallys up how many positive and negative results
		get<1>(*datait)? pos++ : neg ++;
	}

	cout << "positive is " << pos;
	cout << "\t negative is " << neg;

	//This block avoids doing log2(0) which is undefined. If there are no positive or no
	//negative examples we have max info gain and a leaf node.
	if(pos != 0){
		value = (-1 * (pos/size) * log2(pos/size));
		if (neg != 0){
			value -= ((neg/size) * log2(neg/size));
		}
	}
	else if (neg != 0) value = (-1 * (neg/size) * log2(neg/size));

	//applies fractional coefficient and returns the value
	value *= weight;
	cout << "\tvalue is: " << value << endl;
	return value;
}

//This function splits the list into 2 separate lists based on the data
//associated with the selected feature. It then creates new nodes based
//on these sorted lists with out the feature they are split on to
//improve performance.
void decisionNode::prepList(){
	list<list<pair<int, bool> > > newList;
	list<pair<int, bool> >* indCopy;

	lit = population.begin()->begin();
	Lit = population.begin();

	while (Lit != population.end()){
		lit = Lit->begin();
		while (lit != --Lit->end()){
			if (get<0>(*lit) == feature){		//scans list for feature
				//if data with feature is false, delete the pair, copy the list into
				//a new list, and then add the new list to the newList structure
				//remove it from the old list
				if (get<1>(*lit) == false){
					Lit->erase(lit);
					indCopy = new list<pair<int, bool> >();
					lit = indCopy->begin();
					indCopy->insert(lit, Lit->begin(), Lit->end());
					newList.push_back(*indCopy);
					Lit = population.erase(Lit);
				}
				//if it's true, simply erase the pair and leave the list alone
				else {
					Lit->erase(lit);
					Lit++;
				}
				break;
			}
			lit++;
		}
	}
	cout << "Split complete\n";
	//creates new nodes with the sub lists
	nodePtrF = new decisionNode(newList);
	nodePtrT = new decisionNode(population);
}

//This function prints the current sample set to help the user understand
//what the list is splitting on.
void decisionNode::print(){
	cout << "This node's Sample(s):\n";
	for (Lit = population.begin(); Lit != population.end(); Lit++){
		cout << "\t";
		for (lit = Lit->begin(); lit != Lit->end(); lit++){
			cout << get<1>(*lit) << " ";
		}
		cout << endl;
	}
}

//There can be a case where there are no more features to split on
//but there is still a discrepancy in the class of the remaining samples
//such as a sample set with 1 1 and 0 1. The program finds the majority
//and selects that, if it's tied, it selects false arbitrarily
bool decisionNode::findMode(){
	int count = 0;
	bool value;
	//for each samples class, if false, count is decremented, and incremented
	//for true. At the end it evaluates which one to return
	for (Lit = population.begin(); Lit != population.end(); Lit++){
			lit = --Lit->end();
			get<1>(*lit) ? count++ : count--;
	}
	if (abs(count) != population.size())
		cout << "\t!!! There are inconsistencies in the sample!!!\n";
	count > 0 ? value = true : value = false;
	return value;
}

//Recursive function for classifying novel examples entered by the user
bool decisionNode::classify(list<pair<int, bool> > novel){
	if (leafNode){
		return decision;
	}
	//loop to find the feature this node was split on, and then sort
	//this example into the appropriate split based on it's data
	for (lit = novel.begin(); lit != novel.end(); lit++){
		if (get<0>(*lit) == this->feature){
			if (get<1>(*lit) == true){
				novel.erase(lit);
				return nodePtrT->classify(novel);
			}
			else {
				novel.erase(lit);
				return nodePtrF->classify(novel);
			}
		}
	}
	cout << "error in classification\n";
	exit(1);
}

//constructor for each node in the decision tree. first assigns the
//incoming list as it's own population, checks if there are any features
//left to split on, it then checks if the class is homogenous
//finally it finds the best feature to split on with findFeature
//then generates two additional nodes with prepList
decisionNode::decisionNode(list<list <pair<int, bool> > > population) {
	this->population = population;
	nodePtrF = NULL;
	nodePtrT = NULL;
	print();
	Lit = population.begin();
	if (Lit->size() <= 1){
		leafNode = true;
		decision = findMode();
		cout << "classification for this node due to"
				" lack of features and/or samples is: "
				<< decision << endl;
	}
	else if (isHomogenous()){
		leafNode = true;
		cout << "classification for this node is: "<< decision << endl;
	}
	else{
		leafNode = false;
		feature = findFeature();
		cout << "the feature to split on is: " << feature << endl;
		prepList();
	}

	return;
}

decisionNode::~decisionNode() {
	if (nodePtrF != NULL)
	delete nodePtrF;
	if (nodePtrT != NULL)
	delete nodePtrT;
}
