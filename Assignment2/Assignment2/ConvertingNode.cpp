//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a node representation for a data type
// cast (Int -> Float).
// -----------------------------------------------------------------
#include "ConvertingNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
//
// Version 1.0
// ----------------------------------------------------------
ConvertingNode::ConvertingNode()
{
	type = INT2FLOAT;
	dataType = FLOAT;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void ConvertingNode::setNodeType(node_type nt)
{
	//Can only be a converting node type
	type = INT2FLOAT;
}

// ----------------------------------------------------------
// This function sets this node's data type.
// @dt: The new data type for this node.
// Note: dt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void ConvertingNode::setDataType(data_type dt)
{
	//Can only be an Integer
	dataType = FLOAT;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void ConvertingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "(FLOAT)[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void ConvertingNode::accept(Phase* p)
{
	p->visit(this);
}