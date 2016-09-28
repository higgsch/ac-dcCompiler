//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a node representation for an arithmetic
// computation.
// -----------------------------------------------------------------
#include "ComputingNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
// @nt: The node category.
//
// Version 1.0
// ----------------------------------------------------------
ComputingNode::ComputingNode(node_type nt)
{
	setNodeType(nt); //Restrictions exist
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt must be either plus or minus.
//
// Version 1.0
// ----------------------------------------------------------
void ComputingNode::setNodeType(node_type nt)
{
	//Can only be an operator node type
	if (nt == PLUS || nt == MINUS)
		type = nt;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void ComputingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	if (type == PLUS)
		*out << "+";
	else if (type == MINUS)
		*out << "-";
	else
		*out << "<err>";

	*out << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void ComputingNode::accept(Phase* p)
{
	p->visit(this);
}