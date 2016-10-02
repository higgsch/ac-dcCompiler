//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program represents a visitor for generating output code
// that reflects the current AST.
// -----------------------------------------------------------------
#include "CodeGeneratingPhase.h"
#include "Nodes.h"
#include <iostream>
using namespace std;

// ----------------------------------------------------------
// This is the default constructor.
//
// Version 1.0
// ----------------------------------------------------------
CodeGeneratingPhase::CodeGeneratingPhase(ostream* outstream)
{
	out = outstream;
}

// ----------------------------------------------------------
// This function processes a variable declaration.
// @n: The node representing the declaration.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(SymDeclaringNode * n)	
{
	//No op
}

// ----------------------------------------------------------
// This function processes a variable reference.
// @n: The node representing the reference.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(SymReferencingNode * n)	
{
	//Load var
	*out << " l" << n->getID();
}

// ----------------------------------------------------------
// This function processes an assignment operation.
// @n: The node representing the operation.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(AssigningNode * n)		
{
	n->getRightChild()->accept(this);

	//Store var
	*out << " s" << n->getLeftChild()->getID();
	//Integer precision
	*out << " 0 k";
}

// ----------------------------------------------------------
// This function processes an integer constant.
// @n: The node representing the constant.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(IntConstingNode * n)	
{
	*out << " " << n->getVal();
}

// ----------------------------------------------------------
// This function processes a float constant.
// @n: The node representing the constant.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(FloatConstingNode * n)	
{
	//Float precision
	*out << " 5 k ";
	*out << n->getVal();
}

// ----------------------------------------------------------
// This function processes an arithmetic computation.
// @n: The node representing the computation.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(ComputingNode * n)		
{
	n->getLeftChild()->accept(this);
	n->getRightChild()->accept(this);

	if (n->getType() == PLUS)
		*out << " +";
	else if (n->getType() == MINUS)
		*out << " -";
}

// ----------------------------------------------------------
// This function processes a print statement.
// @n: The node representing the print statement.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(PrintingNode * n)		
{
	//Load var
	*out << " l" << n->getID();
	//Print
	*out << " p";
	//Pop top into unused i var
	*out << " si";
}

// ----------------------------------------------------------
// This function processes a type cast operation.
// @n: The node representing the type cast.
//
// Version 1.0
// ----------------------------------------------------------
void CodeGeneratingPhase::visit(ConvertingNode * n)		
{
	n->getRightChild()->accept(this);

	//Float precision
	*out << " 5 k";
}