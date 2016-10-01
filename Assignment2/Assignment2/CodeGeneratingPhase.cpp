#include "CodeGeneratingPhase.h"
#include "Nodes.h"
#include <iostream>
using namespace std;

CodeGeneratingPhase::CodeGeneratingPhase(ostream* outstream)
{
	out = outstream;
}

void CodeGeneratingPhase::visit(SymDeclaringNode * n)	
{
	//No op
}

void CodeGeneratingPhase::visit(SymReferencingNode * n)	
{
	//Load var
	*out << " l" << n->getID();
}

void CodeGeneratingPhase::visit(AssigningNode * n)		
{
	n->getRightChild()->accept(this);

	//Store var
	*out << " s" << n->getLeftChild()->getID();
	//Integer precision
	*out << " 0 k";
}

void CodeGeneratingPhase::visit(IntConstingNode * n)	
{
	*out << " " << n->getVal();
}

void CodeGeneratingPhase::visit(FloatConstingNode * n)	
{
	//Float precision
	*out << " 5 k ";
	*out << n->getVal();
}

void CodeGeneratingPhase::visit(ComputingNode * n)		
{
	n->getLeftChild()->accept(this);
	n->getRightChild()->accept(this);

	if (n->getType() == PLUS)
		*out << " +";
	else if (n->getType() == MINUS)
		*out << " -";
}

void CodeGeneratingPhase::visit(PrintingNode * n)		
{
	//Load var
	*out << " l" << n->getID();
	//Print
	*out << " p";
	//Pop top into unused i var
	*out << " si";
}

void CodeGeneratingPhase::visit(ConvertingNode * n)		
{
	n->getRightChild()->accept(this);

	//Float precision
	*out << " 5 k";
}