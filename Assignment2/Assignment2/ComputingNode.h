// -----------------------------------------------------------------
// This is the header file for the ComputingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for an arithmetic
// computation.
//
// Version 1.0
// ----------------------------------------------------------
class ComputingNode : public AbstractNode
{
public:
	ComputingNode(node_type);
	void setNodeType(node_type);
	void printMe(ostream *);
	void accept(Phase*);
};