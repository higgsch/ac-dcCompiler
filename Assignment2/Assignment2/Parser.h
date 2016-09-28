// -----------------------------------------------------------------
// This is the header for the Parser class.
// -----------------------------------------------------------------
#pragma once

#include "Scanner.h"
#include "Token.h"
using namespace std;

//forward declarations
class ProgramNode; 
class AbstractNode;

// ----------------------------------------------------------
// This class parses a stream of tokens to determine validity in 
// the ac language and builds an AST for the input source code.
//
// Version 1.1
// ----------------------------------------------------------
class Parser
{
private:
	Scanner scanner; //the scanning object that provides a Token stream
	Token current_token; //the currently-selected Token
	Token lookahead[1]; //storage location for one lookahead Token
	ProgramNode * root; //the root of the AST

	void prog();
	void dcls();
	void dcl();
	void stmts();
	void stmt();
	AbstractNode * expr(AbstractNode*);
	AbstractNode * val();

	void match(token_type);
	void syntax_error(string);

	Token next_token();

public:
	Parser();
	void open(string);
	ProgramNode * getAST();
};