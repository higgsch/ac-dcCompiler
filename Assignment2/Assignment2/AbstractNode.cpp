//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides the base of the node inheritance for the 
// AST IR.
// -----------------------------------------------------------------
#include "AbstractNode.h"
#include "Phases.h"
using namespace std;

// ----------------------------------------------------------
// Default constructor initializes pointers.
//
// Version 1.0
// ----------------------------------------------------------
AbstractNode::AbstractNode()
{
	parent = NULL;
	leftChild = NULL;
	rightChild = NULL;
}

// ----------------------------------------------------------
// This function incorporates the given node as this node's
// left child.
// @absNode: The new left child for this node.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::addLeftChild(AbstractNode * absNode)
{
	if (leftChild == NULL)
	{
		absNode->setParent(this);
		absNode->setWhichSide(LEFT);
		leftChild = absNode;		
	}
	else
		cout << "COMPILER ERROR: expression not correct" << endl;
}

// ----------------------------------------------------------
// This function incorporates the given node as this node's
// right child.
// @absNode: The new right child for this node.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::addRightChild(AbstractNode * absNode)
{
	if (rightChild == NULL)
	{
		absNode->setParent(this);
		absNode->setWhichSide(RIGHT);
		rightChild = absNode;

	}
	else
		cout << "COMPILER ERROR: expression not correct" << endl;
}

// ----------------------------------------------------------
// This function replaces this node's current left child by 
// the given node.
// @absNode: The new left child for this node.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::replaceLeftChild(AbstractNode * absNode)  // For converting node insertion
{
	if (leftChild != NULL)
	{
		leftChild->setParent(NULL);
		absNode->setParent(this);
		absNode->setWhichSide(LEFT);
		leftChild = absNode;
	}
	else
		addLeftChild(absNode);
}

// ----------------------------------------------------------
// This function replaces this node's current right child by 
// the given node.
// @absNode: The new right child for this node.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::replaceRightChild(AbstractNode * absNode)  // For converting node insertion
{
	if (rightChild != NULL)
	{
		rightChild->setParent(NULL);
		absNode->setParent(this);
		absNode->setWhichSide(RIGHT);
		rightChild = absNode;
	}
	else
		addRightChild(absNode);
}

// ----------------------------------------------------------
// This function recursively calls each node's printMe method
// in post order.
// @out: The output stream to print the nodes to.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::printPostOrder(ostream * out)
{
	if (leftChild != NULL)
		leftChild->printPostOrder(out);
	if (rightChild != NULL)
		rightChild->printPostOrder(out);
	printMe(out);
}

// ----------------------------------------------------------
// This function recursively calls each node's printMe method
// in order.
// @out: The output stream to print the nodes to.
//
// Version 1.0
// ----------------------------------------------------------
void AbstractNode::printInOrder(ostream * out)
{
	if (leftChild != NULL)
		leftChild->printInOrder(out);
	printMe(out);
	if (rightChild!= NULL)
		rightChild->printInOrder(out);
}