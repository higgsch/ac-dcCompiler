// -----------------------------------------------------------------
// This is the header file for the ConvertingNode class. 
// -----------------------------------------------------------------
#pragma once

#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// This class provides a node representation for a data type
// cast (Int -> Float).
//
// Version 1.0
// ----------------------------------------------------------
class ConvertingNode : public AbstractNode
{
public:
	ConvertingNode();
	void setNodeType(node_type nt);
	void setDataType(data_type dt);
	void printMe(ostream * out);
	void accept(Phase* p);
};