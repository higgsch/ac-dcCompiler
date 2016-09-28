// -----------------------------------------------------------------
// This is the header file for the ProgramNode class. 
// -----------------------------------------------------------------
#pragma once

#include <string>
#include <iostream>
using namespace std;

//forward declarations
class AbstractNode;
class Phase;

// ----------------------------------------------------------
// This class provides a root node for the AST.
//
// Version 1.0
// ----------------------------------------------------------
class ProgramNode
{
private:
	const static int MAXLINES = 100;   // DCL or STMT
	AbstractNode * progLines[MAXLINES]; // collection of root nodes for each line
	int currentNode; // index counter for progLines
	//string type; //not used

public:
	ProgramNode();

	/*string getType()
	{
		return type;
	}*/

	void addNode(AbstractNode * absNode);
	void traverseNodesInOrder(Phase * ph);
	void traverseNodesPostOrder(Phase * ph);
	void traverseNodesTopLevel(Phase * ph);
	void printNodesInOrder(ostream* out);
	void printNodesInPostOrder(ostream* out);
	void traverseNodes(Phase* p);
};
