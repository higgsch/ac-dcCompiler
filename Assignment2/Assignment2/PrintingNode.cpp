//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a node representation for a print operation.
// -----------------------------------------------------------------
#include "PrintingNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
// @id: The variable reference to print.
//
// Version 1.0
// ----------------------------------------------------------
PrintingNode::PrintingNode(char id)
{
	type = PRINTING;
	this->id = id;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void PrintingNode::setNodeType(node_type nt)
{
	//Can only be a PRINT node type
	type = PRINTING;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void PrintingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "<Print>" << id << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void PrintingNode::accept(Phase* p)
{
	p->visit(this);
}