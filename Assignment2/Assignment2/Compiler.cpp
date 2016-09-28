//                      Christopher Higgs
//                      CS 6820 - 7:30 am
//                      Assignment #02
//                      Dr. Rague
//                      Due: 10/08/16
//                      Version: 1.0
// -----------------------------------------------------------------
// This program compiles an .ac source file to dc output.
// -----------------------------------------------------------------
#include "Compiler.h"
#include "SymbolTablePhase.h"
#include "Parser.h"
#include "Nodes.h"
using namespace std;

// ----------------------------------------------------------
// This function drives the compilation process.
// @inFile: The .ac file to open (from project directory).
// @out: The output stream that output source is sent to.
//
// Version 1.0
// ----------------------------------------------------------
void Compiler::run(string inFile, ostream * out)
{
	//Initialize the parser and open the files
	Parser p = Parser();
	p.open(inFile);

	//Initiate the compilation process
	ProgramNode * root = p.getAST();

	root->traverseNodes(new SymbolTablePhase);
	//stp.printSymbolTable();
	
	root->printNodesInOrder(out);
	root->printNodesInPostOrder(out);
}

// ----------------------------------------------------------
// The main function for the ac compiler. Takes a .ac 
// file and .dc file from command line and runs the 
// compilation process.
// Note: Command line accepts .ac filename then .dc filename.
//       Defaults to Sample.ac and Sample.dc if neither are 
//       included.
//
// Version 1.0
// ----------------------------------------------------------
int main(int argc, char* argv[])
{
	string inFile; //.ac filename
	string outFile; //.dc filename

	if (argc > 2)
	{ //filenames exist on command line
		inFile = argv[1];
		outFile = argv[2];
	}
	else
	{ //use default filenames
		inFile = "Sample.ac";
		outFile = "Sample.dc";
	}

	cout << "Starting Parse: " << inFile << " -> " << outFile << endl;

	Compiler c;

	c.run(inFile, &cout);

	/*ofstream out = ofstream();
	out.open(outFile);
	c.run(inFile, &out);
	out.close();*/

	cout << "Press Enter to exit" << endl;
	getchar();

	return 0;
}