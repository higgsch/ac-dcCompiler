// -----------------------------------------------------------------
// This is the header file for the FloatConstingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for a float const.
//
// Version 1.0
// ----------------------------------------------------------
class FloatConstingNode : public AbstractNode
{
public:
	FloatConstingNode(string val);
	void setNodeType(node_type nt);
	void setDataType(data_type dt);
	void printMe(ostream * out);
	void accept(Phase* p);
};