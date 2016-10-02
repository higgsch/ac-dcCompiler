// -----------------------------------------------------------------
// This is the header for the SymbolTablePhase class.
// -----------------------------------------------------------------
#pragma once

#include "Phases.h"
#include "Nodes.h"
using namespace std;

// ----------------------------------------------------------
// This class represents a visitor for building the symbol 
// table and data typing the AST.
//
// Version 1.0
// ----------------------------------------------------------
class SymbolTableAndTypingPhase : public Phase
{
private:
	char symbolTable[23][2]; // storage location for variable information

	bool isDefined(char);
	void define(char,data_type);
	int mapIDToIndex(char);
	char mapIndexToID(int);

	string ctos(char);

public:
	SymbolTableAndTypingPhase();
	void printSymbolTable();

	void visit(SymDeclaringNode * n);
	void visit(SymReferencingNode * n);
	void visit(AssigningNode * n);
	void visit(IntConstingNode * n);
	void visit(FloatConstingNode * n);
	void visit(ComputingNode * n);
	void visit(PrintingNode * n);
	void visit(ConvertingNode * n);
};