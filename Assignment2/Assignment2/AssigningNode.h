// -----------------------------------------------------------------
// This is the header file for the AssigningNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for the assignment
// operation.
//
// Version 1.0
// ----------------------------------------------------------
class AssigningNode : public AbstractNode
{
public:
	AssigningNode();
	void setNodeType(node_type);
	void printMe(ostream *);
	void accept(Phase*);
};