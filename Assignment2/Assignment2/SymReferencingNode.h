// -----------------------------------------------------------------
// This is the header file for the SymReferencingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for a variable
// reference post-declaration.
//
// Version 1.0
// ----------------------------------------------------------
class SymReferencingNode : public AbstractNode
{
public:
	SymReferencingNode(char id);
	void setNodeType(node_type nt);
	void printMe(ostream * out);
	void accept(Phase* p);
};