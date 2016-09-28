//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program reads through an .ac file and converts strings of 
// chars to tokens.
// -----------------------------------------------------------------
#include "Scanner.h"
#include "Token.h"
using namespace std;

// ----------------------------------------------------------
// This is the default constructor.
//
// Version 1.0
// ----------------------------------------------------------
Scanner::Scanner()
{
	lineNo = 1; //starts on the first line
}

// ----------------------------------------------------------
// This deconstructor makes sure the file stream is closed.
//
// Version 1.0
// ----------------------------------------------------------
Scanner::~Scanner(void)
{
	if(source.is_open())
		source.close();
}

// ----------------------------------------------------------
// This function opens the file stream.
// @filename: The .ac file to open (from project directory).
//
// Version 1.0
// ----------------------------------------------------------
void Scanner::open(string filename)
{
	source.open(filename);
}

// ----------------------------------------------------------
// This function scans for and returns the next token.
//
// Version 1.0
// ----------------------------------------------------------
Token Scanner::scan(void)
{
	char in_char;

	while ((in_char = source.get()) != EOF)
	{
		//Windows text files contain '\n' as part of the end of line sequence.
		//Other representations may require a '\r' instead to count lines properly.
		if (in_char == '\n')
		{
			lineNo++;
			continue;
		}
		else if (isspace(in_char))
			continue;
		else if (in_char == 'f')
			return Token::FLOATDCL;
		else if (in_char == 'i')
			return Token::INTDCL;
		else if (in_char == 'p')
			return Token::PRINT;
		else if (in_char == '=')
			return Token::ASSIGN;
		else if (in_char == '+')
			return Token::PLUS;
		else if (in_char == '-')
			return Token::MINUS;
		else if (isalpha(in_char)) //keywords would have already been caught
		{
			if (islower(in_char)) //Only lowercase ID's are allowed
			{
				token_buffer = in_char;
				return Token(token_type::ID, token_buffer);
			}
			else
			{
				string msg = "Identifier ";
				msg += in_char;
				msg += " is not lowercase";
				lexical_error(lineNo, msg);
			}
		}
		else if (isdigit(in_char))
		{
			token_buffer = in_char;
			while (isdigit(in_char = source.get()))
				token_buffer += in_char;

			if (in_char != '.')
			{
				source.unget();
				return Token(token_type::INUM, token_buffer);
			}

			token_buffer += in_char; //in_char must be '.'

			if (!isdigit(in_char = source.get()))
			{ // requires at least one digit after decimal point
				string msg = "Incomplete float literal - ";
				msg += token_buffer;
				msg += in_char;
				lexical_error(lineNo,msg);
			}
			else
				token_buffer += in_char;

			
			int dec_count = 1;

			while (isdigit(in_char = source.get()))
			{
				token_buffer += in_char;
				dec_count++;
			}

			source.unget();

			if (dec_count > 5)
			{
				string msg = "Float literal contains more than 5 decimal digits - ";
				msg += token_buffer;
				lexical_error(lineNo, msg);
			}

			return Token(token_type::FNUM, token_buffer);
		}
		else
		{
			string error = "Unrecognized symbol - ";
			error += in_char;
			lexical_error(lineNo, error);
		}
	}

	return Token::SCANEOF;
}

// ----------------------------------------------------------
// This function displays an error message to the user and 
// terminates the program.
// @lineNo: The line number that the error occurred on.
// @err_msg: The message to display to the user.
// 
// Version 1.0
// ----------------------------------------------------------
void Scanner::lexical_error(int lineNo, string err_msg)
{
	cout << "LEXICAL ERROR on line " << lineNo << ": " << err_msg << endl;
	cout << "Press Enter to Exit" << endl;

	getchar();
	exit(0);
}

// ----------------------------------------------------------
// This function returns the current line number.
//
// Version 1.0
// ----------------------------------------------------------
int Scanner::getLineNo(void)
{
	return lineNo;
}

//int main(int argc, char * argv[])
//{
//	string filename;
//	if (argc > 1)
//		filename = argv[1];
//	else
//		filename = "Sample.ac";
//
//	Scanner s = Scanner();
//	s.open(filename);
//	Token t = s.scan();
//
//	while (t.type != SCANEOF)
//	{
//		cout << t.type << ": " << t.lexeme << endl;
//		t = s.scan();
//	}
//
//	cout << "Press Enter to exit" << endl;
//	getchar();
//}