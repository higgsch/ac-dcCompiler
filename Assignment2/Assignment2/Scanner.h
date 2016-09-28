// -----------------------------------------------------------------
// This is the header file for the Scanner class
// -----------------------------------------------------------------
#pragma once

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//forward declarations
class Token;

// ----------------------------------------------------------
// This class reads through an .ac file and converts strings
// of chars to tokens.
//
// Version 1.0
// ----------------------------------------------------------
class Scanner
{
private:
	string token_buffer; //a buffer to build the current token
	ifstream source; //an input stream for the .ac code file
	int lineNo; //a count variable for the current line number

	void lexical_error(int, string);

public:
	Scanner(void);
	~Scanner(void);
	void open(string);
	Token scan(void);
	int getLineNo(void);
};