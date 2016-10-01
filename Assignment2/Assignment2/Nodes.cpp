//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides node representations for the AST.
// -----------------------------------------------------------------
#include "Nodes.h"
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
		progLines[node]->accept(ph);
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

// ----------------------------------------------------------
// Default constructor.
//
// Version 1.0
// ----------------------------------------------------------
AssigningNode::AssigningNode()
{
	type = ASSIGNING;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void AssigningNode::setNodeType(node_type nt)
{
	//Can only be an ASSIGN node type
	type = ASSIGNING;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void AssigningNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "=[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void AssigningNode::accept(Phase* p)
{
	p->visit(this);
}

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

// ----------------------------------------------------------
// Default constructor.
// @val: The node's value.
//
// Version 1.0
// ----------------------------------------------------------
FloatConstingNode::FloatConstingNode(string val)
{
	type = FLOATCONSTING;
	dataType = FLOAT;
	this->val = val;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void FloatConstingNode::setNodeType(node_type nt)
{
	//Can only be a Float
	type = FLOATCONSTING;
}

// ----------------------------------------------------------
// This function sets this node's data type.
// @dt: The new data type for this node.
// Note: dt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void FloatConstingNode::setDataType(data_type dt)
{
	//Can only be a Float
	dataType = FLOAT;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void FloatConstingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "<F>" << val << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void FloatConstingNode::accept(Phase* p)
{
	p->visit(this);
}

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

// ----------------------------------------------------------
// Default constructor.
// @id: The variable name.
//
// Version 1.0
// ----------------------------------------------------------
SymReferencingNode::SymReferencingNode(char id)
{
	type = IDREF;
	this->id = id;
}

// ----------------------------------------------------------
// This function sets this node's category.
// @nt: The new category for this node.
// Note: nt is ignored.
//
// Version 1.0
// ----------------------------------------------------------
void SymReferencingNode::setNodeType(node_type nt)
{
	//Can only be an ID reference node type
	type = IDREF;
}

// ----------------------------------------------------------
// This function prints this node to the given output stream.
// @out: The stream to display to.
//
// Version 1.0
// ----------------------------------------------------------
void SymReferencingNode::printMe(ostream * out)
{
	char dt;
	if (dataType == FLOAT)
		dt = 'f';
	else if (dataType == INTEGER)
		dt = 'i';
	else
		dt = '?';

	*out << "<ref>" << id << "[" << dt << "]";
}

// ----------------------------------------------------------
// This function allows double dispatch required for visitor
// pattern.
// @p: The visitor to operate on this node.
//
// Version 1.0
// ----------------------------------------------------------
void SymReferencingNode::accept(Phase* p)
{
	p->visit(this);
}