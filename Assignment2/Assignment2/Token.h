// -----------------------------------------------------------------
// This is the header for the Token class. It also includes an enum
// for token categories.
// -----------------------------------------------------------------
#pragma once

#include <string>
using namespace std;

// set of ac token categories
typedef enum token_types {
	NOTOK = -1, FLOATDCL, INTDCL, PRINT, ID, ASSIGNOP, PLUSOP, MINUSOP,
	INUM, FNUM, 
	//BLANK, //Blank isn't used in the CFG
	SCANEOF
} token_type;

// ----------------------------------------------------------
// This class acts as a struct for tokens but includes 
// constructors for ease of use and static "constants" for 
// compact use. 
//
// Version 1.0
// ----------------------------------------------------------
class Token
{ //Glorified Struct with public members and static placeholders
public:
	token_type type; //The category the token belongs to
	string lexeme; //The textual content of the token

	Token(){NOTOK,"<None>";}
	Token(token_type, string);

	//static "constants" used for simplified processing of language
	//static tokens
	static Token NOTOK;
	static Token FLOATDCL;
	static Token INTDCL;
	static Token PRINT;
	static Token ASSIGN;
	static Token PLUS;
	static Token MINUS;
	//static Token BLANK; //Not used in the CFG
	static Token SCANEOF;
};