// -----------------------------------------------------------------
// This is the header file for the SymDeclaringNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for a variable
// declaration.
//
// Version 1.0
// ----------------------------------------------------------
class SymDeclaringNode : public AbstractNode
{
public:
	SymDeclaringNode(node_type nt, char id);
	void setNodeType(node_type nt);
	void printMe(ostream * out);
	void accept(Phase* p);
};