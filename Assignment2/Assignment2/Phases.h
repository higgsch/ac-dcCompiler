// -----------------------------------------------------------------
// This is the header for the Phase class.
// -----------------------------------------------------------------
#include <string>
#include <iostream>
using namespace std;

//forward declarations
class AbstractNode;
class SymDeclaringNode;
class SymReferencingNode;
class AssigningNode;
class IntConstingNode;
class FloatConstingNode;
class ComputingNode;
class PrintingNode;
class ConvertingNode;

// ----------------------------------------------------------
// This class provides the base of the visitor inheritance for
// the AST intermediate representation. 
//
// Version 1.0
// ----------------------------------------------------------
class Phase
{
public:
	//visit functions required by visitor pattern
	virtual void visit(SymDeclaringNode * n) = 0;
	virtual void visit(SymReferencingNode * n) = 0;
	virtual void visit(AssigningNode * n) = 0;
	virtual void visit(IntConstingNode * n) = 0;
	virtual void visit(FloatConstingNode * n) = 0;
	virtual void visit(ComputingNode * n) = 0;
	virtual void visit(PrintingNode * n) = 0;
	virtual void visit(ConvertingNode * n) = 0;

	// ----------------------------------------------------------
	// This function displays an error to the user and terminates
	// the program.
	// @msg: The message to display.
	//
	// Version 1.0
	// ----------------------------------------------------------
	void semantic_error(string msg)
	{
		cout << "SEMANTIC ERROR: " << msg << endl;
		cout << "Press Enter to Exit" << endl;

		getchar();
		exit(0);
	}
};

