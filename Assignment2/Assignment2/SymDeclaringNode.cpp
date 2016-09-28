//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a node representation for a variable
// declaration.
// -----------------------------------------------------------------
#include "SymDeclaringNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
// @nt: The node's category.
// @id: The variable name.
//
// Version 1.0
// ----------------------------------------------------------
SymDeclaringNode::SymDeclaringNode(node_type nt, char id)
{
	setNodeType(nt); //Restriction exists
	this->id = id;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt can only be a Declaring type.
//
// Version 1.0
// ----------------------------------------------------------
void SymDeclaringNode::setNodeType(node_type nt)
{
	//Can only be a DCL node type
	if (nt == INTDECLARING)
	{
		type = nt;
		dataType = INTEGER;
	}
	else if (nt == FLOATDECLARING)
	{
		type = nt;
		dataType = FLOAT;
	}
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void SymDeclaringNode::printMe(ostream * out)
{
	if (type == INTDECLARING)
		*out << "<int>" << id;
	else if (type == FLOATDECLARING)
		*out << "<float>" << id;
	else
		*out << "<err>";

	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void SymDeclaringNode::accept(Phase* p)
{
	p->visit(this);
}