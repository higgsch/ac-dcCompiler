//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a root node for the AST.
// -----------------------------------------------------------------
#include "ProgramNode.h"
#include "Phases.h"
#include "AbstractNode.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor.
//
// Version 1.0
// ----------------------------------------------------------
ProgramNode::ProgramNode()
{
	//type = "program";
	currentNode = 0;
}

// ----------------------------------------------------------
// Adds a line of code's root node to the AST.
// @absNode: The line's root node.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::addNode(AbstractNode * absNode)
{
	if (currentNode < MAXLINES)
	{
		progLines[currentNode] = absNode;
		currentNode++;
	}
	else
		cout << "COMPILER ERROR: too many lines of code" << endl;
}

// ----------------------------------------------------------
// AST traversal in order with visitor pattern.
// @ph: The visitor to run over the AST.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::traverseNodesInOrder(Phase * ph)
{
	for (int node = 0; node < currentNode; node++)
	{
		//progLines[node]->visitInOrder(ph);
	}
}

// ----------------------------------------------------------
// AST traversal post order with visitor pattern.
// @ph: The visitor to run over the AST.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::traverseNodesPostOrder(Phase * ph)
{
	for (int node = 0; node < currentNode; node++)
	{
		//progLines[node]->visitPostOrder(ph);
	}
}

// ----------------------------------------------------------
// AST traversal of code lines' root nodes.
// @ph: The visitor to run over the AST.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::traverseNodesTopLevel(Phase * ph)
{
	for (int node = 0; node < currentNode; node++)
	{
		//progLines[node]->visit(ph);
	}
}

// ----------------------------------------------------------
// Prints the in order AST traversal to the output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::printNodesInOrder(ostream* out)
{
	cout << "Printing in Order" << endl;
	for (int node = 0; node < currentNode; node++)
	{
		progLines[node]->printInOrder(out);
		*out << endl;
	}
	*out << endl;
}

// ----------------------------------------------------------
// Prints the post order AST traversal to the output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::printNodesInPostOrder(ostream* out)
{
	cout << "Printing post Order" << endl;
	for (int node = 0; node < currentNode; node++)
	{
		progLines[node]->printPostOrder(out);
		*out << endl;
	}
	*out << endl;
}

// ----------------------------------------------------------
// This function starts double dispatch required for visitor 
// pattern.
// @p: The visitor to run over the AST.
//
// Version 1.0
// ----------------------------------------------------------
void ProgramNode::traverseNodes(Phase* p)
{
	for (int i = 0; i < currentNode; i++)
	{
		progLines[i]->accept(p);
	}
}