// -----------------------------------------------------------------
// This is the header for the CodeGeneratingPhase class.
// -----------------------------------------------------------------
#pragma once

#include "Phases.h"
#include "Nodes.h"
using namespace std;

// ----------------------------------------------------------
// This class represents a visitor for generating output code
// that reflects the current AST.
//
// Version 1.0
// ----------------------------------------------------------
class CodeGeneratingPhase : public Phase
{
private:
	ostream * out; // the output stream to print to

public:
	CodeGeneratingPhase(ostream*);

	void visit(SymDeclaringNode * n);
	void visit(SymReferencingNode * n);
	void visit(AssigningNode * n);
	void visit(IntConstingNode * n);
	void visit(FloatConstingNode * n);
	void visit(ComputingNode * n);
	void visit(PrintingNode * n);
	void visit(ConvertingNode * n);
};