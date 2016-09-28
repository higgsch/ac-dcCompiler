//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program provides a compact interface for tokens.
// -----------------------------------------------------------------
#include "Token.h"
using namespace std;

// ----------------------------------------------------------
// This is a straight-through constructor.
//
// Version 1.0
// ----------------------------------------------------------
Token::Token(token_type aType, string aLexeme)
{
	type = aType;
	lexeme = aLexeme;
}

//static "constants" used for simplified processing of language
//static tokens
Token Token::NOTOK		= Token(token_types::NOTOK,"<None>");
Token Token::FLOATDCL	= Token(token_types::FLOATDCL,"f");
Token Token::INTDCL		= Token(token_types::INTDCL,"i");
Token Token::PRINT		= Token(token_types::PRINT,"p");
Token Token::ASSIGN	= Token(token_types::ASSIGNOP,"=");
Token Token::PLUS		= Token(token_types::PLUSOP,"+");
Token Token::MINUS	= Token(token_types::MINUSOP,"-");
//Token Token::BLANK		= Token(token_types::BLANK," "); //Not used in the CFG
Token Token::SCANEOF	= Token(token_types::SCANEOF,"<EOF>");