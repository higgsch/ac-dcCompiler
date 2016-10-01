#pragma once

#include "Phases.h"
#include "Nodes.h"
using namespace std;

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