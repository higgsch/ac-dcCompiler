// -----------------------------------------------------------------
// This is the header file for the AbstractNode class. It also
// includes enums for node categories, binary node children identification,
// and data typing.
// -----------------------------------------------------------------
#pragma once

#include <iostream>
#include <string>
using namespace std;

//forward declarations
class Phase;

// identification for which binary child a node is.
typedef enum node_sides{
	LEFT, RIGHT
} node_side;

// set of node categories
typedef enum node_types{
	INTDECLARING, FLOATDECLARING, PRINTING, IDREF, ASSIGNING, PLUS, MINUS, INTCONSTING, FLOATCONSTING,
	INT2FLOAT
} node_type;

// data typing
typedef enum data_types{
	INTEGER, FLOAT
} data_type;

// ----------------------------------------------------------
// This class provides the base of the node inheritance for
// the AST intermediate representation. Supports the visitor
// pattern for a Phase.
//
// Version 1.0
// ----------------------------------------------------------
class AbstractNode
{
protected:
	AbstractNode * parent; // this node's parent
	AbstractNode * leftChild; // this node's left child
	AbstractNode * rightChild; // this node's right child
	node_type type; // the node category
	char id; // a field to store an variable reference (if needed by node_type)
	string val; // a field to store a value (if needed by node_type)
	data_type dataType; // the data type for the variable or value
	node_side parent_side;	// indicates which child (left or right)

public:
	AbstractNode();

	// ----------------------------------------------------------
	// This function sets this node's parent.
	// @par: The new parent for this node.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setParent(AbstractNode * par)
	{
		parent = par;
	}

	// ----------------------------------------------------------
	// This function sets the side this node occupies in the
	// parent node.
	// @which: Side indicator
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setWhichSide(node_side which)
	{
		parent_side = which;
	}

	void addLeftChild(AbstractNode * absNode);
	void addRightChild(AbstractNode * absNode);
	void replaceLeftChild(AbstractNode *);
	void replaceRightChild(AbstractNode *);

	// ----------------------------------------------------------
	// This function sets this node's data type.
	// @dt: The new data type for this node.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setDataType(data_type dt)
	{
		dataType = dt;
	}

	// ----------------------------------------------------------
	// This function sets this node's category.
	// @nt: The new category for this node.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setNodeType(node_type nt)
	{
		type = nt;
	}

	// ----------------------------------------------------------
	// This function sets the variable reference this node represents.
	// @id: The new variable reference for this node.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setID(char id)
	{
		this->id = id;
	}

	// ----------------------------------------------------------
	// This function sets this node's value.
	// @val: The new value for this node.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void setVal(string val)
	{
		this->val = val;
	}

	// ----------------------------------------------------------
	// This function returns an indicator for which side of the
	// parent this node occupies.
	//
	// Version 1.0
	// ----------------------------------------------------------
	node_side getWhichSide()
	{
		return parent_side;
	}

	// ----------------------------------------------------------
	// This function returns this node's parent.
	//
	// Version 1.0
	// ----------------------------------------------------------
	AbstractNode * getParent()
	{
		return parent;
	}

	// ----------------------------------------------------------
	// This function returns this node's left child.
	//
	// Version 1.0
	// ----------------------------------------------------------
	AbstractNode * getLeftChild()
	{
		return leftChild;
	}

	// ----------------------------------------------------------
	// This function returns this node's right child.
	//
	// Version 1.0
	// ----------------------------------------------------------
	AbstractNode * getRightChild()
	{
		return rightChild;
	}

	// ----------------------------------------------------------
	// This function returns this node's category.
	//
	// Version 1.0
	// ----------------------------------------------------------
	node_type getType()
	{
		return type;
	}

	// ----------------------------------------------------------
	// This function returns the variable reference this node 
	// represents.
	//
	// Version 1.0
	// ----------------------------------------------------------
	char getID()
	{
		return id;
	}

	// ----------------------------------------------------------
	// This function returns this node's data type.
	//
	// Version 1.0
	// ----------------------------------------------------------
	data_type getDataType()
	{
		return dataType;
	}

	// ----------------------------------------------------------
	// This function returns this node's value.
	//
	// Version 1.0
	// ----------------------------------------------------------
	string getVal()
	{
		return val;
	}

	/*virtual void visitInOrder(Phase * ph) = 0;
	virtual void visitPostOrder(Phase *ph) = 0;
	virtual void visit(Phase *ph) = 0;
	virtual void printInOrder() = 0;*/

	// accept method for visitor pattern
	virtual void accept(Phase*)=0;

	// printing functions
	virtual void printMe(ostream*) = 0;
	void printPostOrder(ostream *);
	void printInOrder(ostream *);
	
};

