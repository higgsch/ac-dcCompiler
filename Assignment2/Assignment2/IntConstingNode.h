// -----------------------------------------------------------------
// This is the header file for the IntConstingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for an integer
// constant.
//
// Version 1.0
// ----------------------------------------------------------
class IntConstingNode : public AbstractNode
{
public:
	IntConstingNode(string val);
	void setNodeType(node_type nt);
	void setDataType(data_type dt);
	void printMe(ostream * out);
	void accept(Phase* p);
};