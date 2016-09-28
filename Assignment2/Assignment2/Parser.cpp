//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.1
// -----------------------------------------------------------------
// This program parses a stream of tokens to determine validity in 
// the ac language and builds an AST for the input source code. 
// -----------------------------------------------------------------
#include "Parser.h"
#include "Nodes.h"
#include "Token.h"
#include "Scanner.h"
using namespace std;

// ----------------------------------------------------------
// This is the default constructor.
//
// Version 1.0
// ----------------------------------------------------------
Parser::Parser()
{
	current_token = Token::NOTOK;
	lookahead[0] = Token::NOTOK;
}

// ----------------------------------------------------------
// This function opens the input and output files.
// @inFile: The .mic file to open.
// @outFile: The .asm file to create/open.
// Note: File reference from project directory.
//
// Version 1.0
// ----------------------------------------------------------
void Parser::open(string inFile)
{
	scanner.open(inFile);
}

// ----------------------------------------------------------
// This function initiates the parse and returns a pointer
// to the root node in the AST.
//
// Version 1.1
// ----------------------------------------------------------
ProgramNode * Parser::getAST()
{
	prog();
	return root;
	cout << "Program successfully compiled" << endl;
}

// ----------------------------------------------------------
// This function represents production rule #1:
// <Prog> => <Dcls> <Stmts> $
//
// Version 1.1
// ----------------------------------------------------------
void Parser::prog()	
{
	root = new ProgramNode();
	dcls(); stmts(); match(SCANEOF);
}

// ----------------------------------------------------------
// This function represents production rules #2 and #3:
// <Dcls> => <Dcl> <Dcls>
// <Dcls> => (Lambda)
//
// Version 1.0
// ----------------------------------------------------------
void Parser::dcls()	
{
	Token tok = next_token();
	switch (tok.type)
	{
	case FLOATDCL: 
	case INTDCL:
		dcl(); dcls();
		break;
	case ID:
	case PRINT:
	case SCANEOF:
		//No op
		break;
	default:
		syntax_error("Invalid Term - " + tok.lexeme);
		break;
	}	
}

// ----------------------------------------------------------
// This function represents production rules #4 and #5:
// <Dcl> => FLOATDCL ID
// <Dcl> => INTDCL ID
//
// Version 1.1
// ----------------------------------------------------------
void Parser::dcl()	
{
	Token dclTok = next_token();
	if (dclTok.type == FLOATDCL || dclTok.type == INTDCL)
	{
		match(dclTok.type); 
		Token idTok = next_token();
		match(ID);

		node_types type;
		if (dclTok.type == FLOATDCL)
		{
			type = FLOATDECLARING;
		}
		else if (dclTok.type == INTDCL)
		{
			type = INTDECLARING;
		}

		AbstractNode * dclNode = new SymDeclaringNode(type,idTok.lexeme[0]);
		root->addNode(dclNode);
	}
	else
		syntax_error("Invalid Term - " + dclTok.lexeme);
}

// ----------------------------------------------------------
// This function represents production rules #6 and #7:
// <Stmts> => <Stmt> <Stmts>
// <Stmts> => (lambda)
//
// Version 1.0
// ----------------------------------------------------------
void Parser::stmts()
{
	Token tok = next_token();
	switch (tok.type)
	{
	case ID:
	case PRINT:
		stmt(); stmts();
		break;
	case SCANEOF:
		//No op
		break;
	default:
		syntax_error("Invalid Term - " + tok.lexeme);
	}
}

// ----------------------------------------------------------
// This function represents production rules #8 and #9:
// <Stmt> => ID ASSIGNOP <Val> <Expr>
// <Stmt> => PRINT ID
//
// Version 1.1
// ----------------------------------------------------------
void Parser::stmt()	
{
	Token firstTok = next_token();
	if (firstTok.type == ID)
	{
		match(ID); 
		match(ASSIGNOP); 
		
		AssigningNode * aNode = new AssigningNode();
		aNode->addLeftChild(new SymReferencingNode(firstTok.lexeme[0]));

		AbstractNode * eNode = expr(val());
		aNode->addRightChild(eNode);

		root->addNode(aNode);
	}
	else if (firstTok.type == PRINT)
	{
		match(PRINT); 
		Token id = next_token();
		match(ID);

		root->addNode(new PrintingNode(id.lexeme[0]));
	}
	else
		syntax_error("Invalid Term - " + firstTok.lexeme);
}

// ----------------------------------------------------------
// This function represents production rules #10, #11, and #12:
// <Expr> => PLUSOP <Val> <Expr>
// <Expr> => MINUSOP <Val> <Expr>
// <Expr> => (lambda)
// Returns a pointer to the generated expression node.
// @lNode: The node to be assigned as this expression node's
//         left child.
//
// Version 1.1
// ----------------------------------------------------------
AbstractNode * Parser::expr(AbstractNode * lNode)
{
	Token tok = next_token();
	switch (tok.type)
	{
	case PLUSOP:
		{
			match(PLUSOP); 

			AbstractNode * plusNode = new ComputingNode(PLUS);
			plusNode->addLeftChild(lNode);
			plusNode->addRightChild(val()); 
			return expr(plusNode);
		}
		break; //never hit
	case MINUSOP:
		{
			match(MINUSOP); 

			AbstractNode * minusNode = new ComputingNode(MINUS);
			minusNode->addLeftChild(lNode);
			minusNode->addRightChild(val()); 
			return expr(minusNode);
		}
		break; //never hit
	case ID:
	case PRINT:
	case SCANEOF:
		return lNode;
		break; //never hit
	default:
		syntax_error("Invalid Term - " + tok.lexeme);
		return NULL; //never hit
	}
}

// ----------------------------------------------------------
// This function represents production rules #13, #14, and #15:
// <Val> => ID
// <Val> => ILITERAL
// <Val> => FLITERAL
// Returns a pointer to the generated value node.
//
// Version 1.1
// ----------------------------------------------------------
AbstractNode * Parser::val()	
{
	Token tok = next_token();
	switch (tok.type)
	{
	case ID:
		match(ID);
		return new SymReferencingNode(tok.lexeme[0]);
		break; //never hit		
	case INUM:
		match(INUM);
		return new IntConstingNode(tok.lexeme);
		break; //never hit
	case FNUM:
		match(FNUM);
		return new FloatConstingNode(tok.lexeme);
		break; //never hit
	default:
		syntax_error("Invalid Term - " + tok.lexeme);
		return NULL; //never hit
	}
}

// ----------------------------------------------------------
// This function tests if the next token matches toMatch and
// moves to the next token on success. It displayes an error
// on failure.
// @toMatch: The expected token category.
//
// Version 1.0
// ----------------------------------------------------------
void Parser::match(token_type toMatch)
{
	//if a match is found, move to next token
	if (next_token().type == toMatch)
	{
		current_token = lookahead[0];
		lookahead[0] = Token::NOTOK;
	}
	else
	{
		//User-friendly text for missing token type
		string type;
		switch (toMatch)
		{
		case ASSIGNING:
			type = "'='";
			break;
		case ID:
			type = "Identifier";
			break;
		case SCANEOF:
			type = "'<EOF>'";
			break;
		//f, i, p, -, and + cannot be hit here if the CFG is implemented correctly.
		case FLOATDCL:
			type = "'f'";
			break;
		case INTDCL:
			type = "'i'";
			break;
		case PRINT:
			type = "'p'";
			break;
		case MINUS:
		case PLUS:
			type = "'-' or '+'";
			break;
		default:
			type = "<type>";
			break;
		}

		syntax_error("Expected " + type + " - Found " + lookahead[0].lexeme);
	}
}

// ----------------------------------------------------------
// This function displays an error to the user and terminates
// the program.
// @err_msg: The message to display.
//
// Version 1.0
// ----------------------------------------------------------
void Parser::syntax_error(string err_msg)
{
	int lineNo = scanner.getLineNo();
	cout << "SYNTAX ERROR on line " << lineNo << ": " << err_msg << endl;
	cout << "Press Enter to Exit" << endl;

	getchar();
	exit(0);
}

// ----------------------------------------------------------
// This function populates and returns the lookahead token.
//
// Version 1.0
// ----------------------------------------------------------
Token Parser::next_token()
{
	if (lookahead[0].type == NOTOK)
		lookahead[0] = scanner.scan();

	return lookahead[0];
}

//int main(int argc, char * argv[])
//{
//	string inFile; //.ac filename
//	string outFile; //.dc filename
//
//	if (argc > 2)
//	{ //filenames exist on command line
//		inFile = argv[1];
//		outFile = argv[2];
//	}
//	else
//	{ //use default filenames
//		inFile = "Sample.ac";
//		outFile = "Sample.dc";
//	}
//
//	cout << "Starting Parse: " << inFile << " -> " << outFile << endl;
//
//	//Initialize the parser and open the files
//	Parser p = Parser();
//	p.open(inFile, outFile);
//
//	//Initiate the compilation process
//	ProgramNode * root = p.getAST();
//
//	root->printNodesInOrder();
//	root->printNodesInPostOrder();
//
//	cout << "Press Enter to exit" << endl;
//	getchar();
//
//	return 0;
//}