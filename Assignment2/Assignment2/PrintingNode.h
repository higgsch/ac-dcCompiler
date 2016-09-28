// -----------------------------------------------------------------
// This is the header file for the PrintingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for a print 
// operation.
//
// Version 1.0
// ----------------------------------------------------------
class PrintingNode : public AbstractNode
{
public:
	PrintingNode(char id);
	void setNodeType(node_type nt);
	void printMe(ostream * out);
	void accept(Phase* p);
};