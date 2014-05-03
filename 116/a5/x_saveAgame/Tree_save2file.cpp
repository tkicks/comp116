
// put this in Tree.h
private:
	Node* root;    // pointer to root node of tree

	ofstream FOUT;
	ifstream FIN;

	// private methods
	void  RecursiveNodeSAVEtoFile(Node* root);
	Node* RecursiveNodeREADfromFile( );

};// class Tree




// put this in Tree.cpp
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
	
	if ( pNode->LChild() != 0 )
	{
		this->FOUT << 1 << endl;
		RecursiveNodeSAVEtoFile( pNode->LChild() );
	}
	else
		this->FOUT << 0 << endl;
	
	
	if ( pNode->RChild() != 0 )
	{
		this->FOUT << 1 << endl;
		RecursiveNodeSAVEtoFile( pNode->RChild() );
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
		pNode->AppendLeft( RecursiveNodeREADfromFile() );
	else
		pNode->AppendLeft(0);
	
	this->FIN >> marker;   getline(this->FIN, flushRestOfLine );
	
	if (marker == 1 ) 
		pNode->AppendRight( RecursiveNodeREADfromFile() );
	else
		pNode->AppendRight(0);
	
	
	return pNode;
	
} // RecursiveNodeREADfromFile