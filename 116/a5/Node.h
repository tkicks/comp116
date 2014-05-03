/* last modified: 4/18/2014 */


#ifndef NODE
#define NODE

#include "constants.h"

class Node         		
{
  public:
	Node();				// default CTOR
	Node(string);		// CTOR when string is known
	
	Node(const Node&);  // COPY CTOR
	
	~Node();			// DTOR
    
    // ---------- SETTERS ------------------------
	void StoreText(const string /*in*/ newText);
	//..........................................
	// PRE:   newText is a valid string
	// POST:  node contains the string in it

	void AppendNo(Node* /*in*/ newNode);
	//..........................................
	// PRE: Assigned(newNode)
	// POST: this-> node has a new no child


	void AppendYes(Node* /*in*/ newNode);
	//..........................................
	// PRE: Assigned(newNode)
	// POST: this-> node has a new yes child



	// ---------- GETTERS ------------------------
	string GetText() const;
	//..........................................
	// POST: RETURN == string in current node

	Node* YChild() const;
	//..........................................
	// PRE: this != NULL
	// POST: RETURN == pointer to yes node

	Node* NChild() const;
	//..........................................
	// PRE: this != NULL
	// POST: RETURN == pointer to no node


	// ---------- QUERIES ------------------------
	bool IsLeaf() const;
	//..........................................
	// PRE: this != NULL
	// POST: RETURN T/F whether or not this-> is a leaf node

  
  private:
	 Node* yes;	// pointer to a yes  child node
	 Node* no;	// pointer to a no child node
	 
	 string Qthing;	// question at a node OR if a leaf node the name of an object
	
}; // class Node


#endif