//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a node representation for an integer const.
// -----------------------------------------------------------------
#include "IntConstingNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
// @val: The node's value.
//
// Version 1.0
// ----------------------------------------------------------
IntConstingNode::IntConstingNode(string val)
{
	type = INTCONSTING;
	dataType = INTEGER;
	this->val = val;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void IntConstingNode::setNodeType(node_type nt)
{
	//Can only be an Integer
	type = INTCONSTING;
}

// ----------------------------------------------------------
// This function sets this node's data type.
// @dt: The new data type for this node.
// Note: dt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void IntConstingNode::setDataType(data_type dt)
{
	//Can only be an Integer
	dataType = INTEGER;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void IntConstingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "<I>" << val << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void IntConstingNode::accept(Phase* p)
{
	p->visit(this);
}