// -----------------------------------------------------------------
// This is the header file for the Compiler class
// -----------------------------------------------------------------
#pragma once

#include <string>
#include "Parser.h"
using namespace std;

//forward declarations
class ProgramNode;

// ----------------------------------------------------------
// This class is the driver class for the compiler program.
// It can be used to compile an .ac source file to dc output.
//
// Version 1.0
// ----------------------------------------------------------
class Compiler
{
private:
	Parser parser;
	ProgramNode * root; //A pointer to the root of the AST for input source

public:
	void run(string,ostream*);
};