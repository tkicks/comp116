#include <iostream>
#include <stdlib.h>

#include "Tree.h"

// ======================================================================
Tree::Tree()								//CTOR
//..........................................
//POST: new tree is created with a root
{
	this->root = new Node;
	
	// NOTE:  we must use the functions in the Node class to change things!
	root->AppendYes( 0 );
	root->AppendNo( 0 );
}//CTOR


// ======================================================================
Tree::Tree(string questionText, string yesObject, string noObject)
//..........................................
//POST: new tree is created with a root with known question and yes/no objects
{
	this->root = new Node(questionText);
	
	// NOTE:  we must use the functions in the Node class to change things!
	root->AppendYes( new Node(yesObject) );
	root->AppendNo( new Node(noObject) );
}//CTOR


// ======================================================================
Tree::~Tree()								//DTOR
{

	// MOM!  my FINGER HURTS!! ...
	// (ok, you'll have to write this one ... :)
	this->DeleteAll(this->root);
} //DTOR
	
	
// ======================================================================
bool Tree::IsEmpty(void) const
//..........................................
//POST: RETURN == whether or not the root node has children
{
	return (root->NChild() == 0  &&  root->YChild() == 0 );
}// IsEmpty


// ======================================================================
Node* Tree::GetRoot(void) const
//..........................................
//POST: RETURN == address of root node
{
	return root;
}// GetRoot

// ======================================================================
void Tree::DeleteAll(Node* T)
//..........................................
//POST: tree deleted
{
	if (T != 0)
	{
		DeleteAll(T->YChild());
		DeleteAll(T->NChild());
		delete T;
	}
}// DeleteAll


// ======================================================================
void Tree::SaveTreeToFile(string outputFileName) 
//..........................................
//POST: entire tree saved to a file
{
	this->FOUT.clear();                         // reset the stream just in case
	this->FOUT.open( outputFileName.c_str() );	// attempt to OPEN output FILE
	
	// TRAP
	if (FOUT.fail() )			// but did open fail?
	{
	 	cout << "ERROR: output file called " << outputFileName
		<< " didn't open " << endl << "Program terminating ..." << endl;
	 	// system("PAUSE");
		exit(-1);
	} // if
	
	// call recursive (private) method to do all the work
	this->RecursiveNodeSAVEtoFile( this->root );
	
	this->FOUT.close();
	
} // SaveTreeToFile


// ======================================================================
void Tree::RecursiveNodeSAVEtoFile(Node* pNode) 
//..........................................
// PRE:  outstream is open and ready
//       Assigned(pNode) (any node in tree)
// POST: pNode and children written to file
{
	
	this->FOUT << pNode->GetText() << endl;
	
	if ( pNode->YChild() != 0 )
	{
		this->FOUT << 1 << endl;
		RecursiveNodeSAVEtoFile( pNode->YChild() );
	}
	else
		this->FOUT << 0 << endl;
	
	
	if ( pNode->NChild() != 0 )
	{
		this->FOUT << 1 << endl;
		RecursiveNodeSAVEtoFile( pNode->NChild() );
	}
	else
		this->FOUT << 0 << endl;
	
} // RecursiveNodeSAVEtoFile


// ======================================================================
void Tree::ReadTreeFromFile(string inputFileName) 
//..........................................
//POST: entire tree loaded from a file
{
	this->FIN.clear();					// reset the stream just in case
	this->FIN.open( inputFileName.c_str() );		// attempt to OPEN output FILE
	
	// TRAP
	if (FIN.fail() )			// but did open fail?
	{
	 	cout << "ERROR: input file called " << inputFileName
		<< " didn't open " << endl << "Program terminating ..." << endl;
	 	// system("PAUSE");
		exit(-1);
	} // if
	
	// call recursive (private) method to do all the work
	this->root = this->RecursiveNodeREADfromFile( );
	
	this->FIN.close();
	
} // ReadTreeFromFile



Node* Tree::RecursiveNodeREADfromFile( ) 
//..........................................
// PRE:  ifstream is open and ready
//       Assigned(pNode) (any node in tree)
// POST: pNode and children read from file and saved in Tree

{
	short marker;
	string theText;
	string flushRestOfLine;
	
	getline(this->FIN, theText );
	Node* pNode = new Node(theText);
	
	this->FIN >> marker;   getline(this->FIN, flushRestOfLine );
	if (marker == 1 ) 
		pNode->AppendYes( RecursiveNodeREADfromFile() );
	else
		pNode->AppendYes(0);
	
	this->FIN >> marker;   getline(this->FIN, flushRestOfLine );
	
	if (marker == 1 ) 
		pNode->AppendNo( RecursiveNodeREADfromFile() );
	else
		pNode->AppendNo(0);
	
	
	return pNode;
	
} // RecursiveNodeREADfromFile