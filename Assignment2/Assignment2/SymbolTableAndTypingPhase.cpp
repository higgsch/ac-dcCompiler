//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program represents a visitor for building the symbol 
// table and data typing the AST.
// -----------------------------------------------------------------
#include "SymbolTableAndTypingPhase.h"
#include "Nodes.h"
#include <iostream>
#include <sstream>
using namespace std;

// ----------------------------------------------------------
// This is the default constructor.
//
// Version 1.0
// ----------------------------------------------------------
SymbolTableAndTypingPhase::SymbolTableAndTypingPhase()
{
	// populate variable name space
	int symbolOffset = 0;
	for (int sym = 0; sym < 23; sym++)
	{

		symbolTable[sym][0] = 'a' + sym + symbolOffset;
		switch (symbolTable[sym][0])
		{
		case 'f':
		case 'i':
		case 'p':
			symbolOffset++;
			symbolTable[sym][0]++;
			break;
		default:
			//no op
			break;
		}

		symbolTable[sym][1] = '0';
	}
}

// ----------------------------------------------------------
// This function processes a variable declaration.
// @n: The node representing the declaration.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(SymDeclaringNode * n)	 
{
	if (isDefined(n->getID()))
	{
		//Error, already defined
		semantic_error(ctos(n->getID()) + " is already defined.");
	}
	else
		define(n->getID(),n->getDataType());
}

// ----------------------------------------------------------
// This function processes a variable reference.
// @n: The node representing the reference.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(SymReferencingNode * n) 
{
	if (!isDefined(n->getID()))
	{
		//Error, variable not defined
		semantic_error(ctos(n->getID()) + " is not defined.");
	}
	else
	{
		char dt = symbolTable[mapIDToIndex(n->getID())][1];
		if (dt == 'i')
			n->setDataType(INTEGER);
		else if (dt == 'f')
			n->setDataType(FLOAT);
	}
}

// ----------------------------------------------------------
// This function processes an assignment operation.
// @n: The node representing the operation.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(AssigningNode * n)		 
{
	AbstractNode * val = n->getRightChild();
	AbstractNode * var = n->getLeftChild();

	var->accept(this);
	val->accept(this);

	if (var->getDataType() == INTEGER && val->getDataType() == FLOAT)
	{
		//Error, type casting
		semantic_error("Illegal type cast when assigning " + ctos(var->getID()));
	}
	else if (var->getDataType() == FLOAT && val->getDataType() == INTEGER)
	{
		//Converting val node
		AbstractNode * conv = new ConvertingNode();
		n->replaceRightChild(conv);
		conv->addRightChild(val);
	}

	n->setDataType(var->getDataType());
}

// ----------------------------------------------------------
// This function processes an integer constant.
// @n: The node representing the constant.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(IntConstingNode * n)	 
{
	//No op
}

// ----------------------------------------------------------
// This function processes a float constant.
// @n: The node representing the constant.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(FloatConstingNode * n)	 
{
	//No op
}

// ----------------------------------------------------------
// This function processes an arithmetic computation.
// @n: The node representing the computation.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(ComputingNode * n)		 
{
	AbstractNode * left = n->getLeftChild();
	AbstractNode * right = n->getRightChild();

	left->accept(this);
	right->accept(this);

	if (left->getDataType() == FLOAT || right->getDataType() == FLOAT)
	{
		n->setDataType(FLOAT);
		if (left->getDataType() == INTEGER)
		{
			//Converting left node
			AbstractNode * conv = new ConvertingNode();
			n->replaceLeftChild(conv);
			conv->addRightChild(left);
		}
		else if (right->getDataType() == INTEGER)
		{
			//Converting right node
			AbstractNode * conv = new ConvertingNode();
			n->replaceRightChild(conv);
			conv->addRightChild(right);
		}
	}
	else 
		n->setDataType(INTEGER);
}

// ----------------------------------------------------------
// This function processes a print statement.
// @n: The node representing the print statement.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(PrintingNode * n)		 
{
	if (!isDefined(n->getID()))
	{
		//Error, variable not defined
		semantic_error(ctos(n->getID()) + " is not defined.");
	}
	else
	{
		char dt = symbolTable[mapIDToIndex(n->getID())][1];
		if (dt == 'i')
			n->setDataType(INTEGER);
		else if (dt == 'f')
			n->setDataType(FLOAT);
	}
}

// ----------------------------------------------------------
// This function processes a type cast operation.
// @n: The node representing the type cast.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::visit(ConvertingNode * n)	 
{
	//No op
}

// ----------------------------------------------------------
// Determines if the given variable has already been defined.
// @id: The variable in question.
//
// Version 1.0
// ----------------------------------------------------------
bool SymbolTableAndTypingPhase::isDefined(char id)
{
	return symbolTable[mapIDToIndex(id)][1] != '0';
}

// ----------------------------------------------------------
// Adds a definition for the given variable.
// @id: The variable to be defined.
// @dt: The variable's data type.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::define(char id,data_type dt)
{
	if (dt == data_type::INTEGER)
		symbolTable[mapIDToIndex(id)][1] = 'i';
	else if (dt == data_type::FLOAT)
		symbolTable[mapIDToIndex(id)][1] = 'f';
}

// ----------------------------------------------------------
// This function returns the index corresponding to a given id.
// @id: The variable name to match.
//
// Version 1.0
// ----------------------------------------------------------
int SymbolTableAndTypingPhase::mapIDToIndex(char id)
{
	if (id >= 'a' && id < 'f')
		return id - 'a';
	else if (id > 'f' && id < 'i')
		return id - 'a' - 1;
	else if (id > 'i' && id < 'p')
		return id - 'a' - 2;
	else if (id > 'p' && id <= 'z')
		return id - 'a' - 3;
	else
		return -1;
}

// ----------------------------------------------------------
// This function returns the id corresponding to a given index.
// @index: The index to match.
//
// Version 1.0
// ----------------------------------------------------------
char SymbolTableAndTypingPhase::mapIndexToID(int index)
{
	char sym = index + 'a';
	if (sym >= 'a' && sym < 'f')
		return sym;
	else if (++sym > 'f' && sym < 'i')
		return sym;
	else if (++sym > 'i' && sym < 'p')
		return sym;
	else if (++sym > 'p' && sym <= 'z')
		return sym;
	else
		return '0';
}

// ----------------------------------------------------------
// This function displays the symbol table to cout.
//
// Version 1.0
// ----------------------------------------------------------
void SymbolTableAndTypingPhase::printSymbolTable()
{
	for (int i = 0; i < 23; i++)
	{
		if (symbolTable[i][1] == '0')
			cout << symbolTable[i][0] << " is undefined." << endl;
		else if (symbolTable[i][1] == 'i')
			cout << symbolTable[i][0] << " is an Integer." << endl;
		else if (symbolTable[i][1] == 'f')
			cout << symbolTable[i][0] << " is a Float." << endl;
		else
			cout << symbolTable[i][0] << " caused an Error." << endl;
	}
}

// ----------------------------------------------------------
// This function converts a char to a string for ease of use.
// @c: The char to convert.
//
// Version 1.0
// ----------------------------------------------------------
string SymbolTableAndTypingPhase::ctos(char c)
{
	stringstream ss;
	string s;
	ss << c;
	ss >> s;
	return s;
}