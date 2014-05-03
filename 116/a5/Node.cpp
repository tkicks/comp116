/* last modified: 4/18/2014 
				  4/23/2014*/


#include <iostream>
#include <stdlib.h>

#include "Node.h"

// ======================================================================
Node::Node()					// Default CTOR
{		
	this->Qthing = DEFAULT_TEXT;
		
	this->yes  = 0;			//make yes and no point to NULL
	this->no = 0;
	
}// CTOR

// ======================================================================
Node::Node(const string text)	// CTOR when text is known
{
	this->Qthing = text;		
	this->yes  = 0;			// make yes and no point to NULL
	this->no = 0;
	
}// CTOR

// ======================================================================
Node::Node(const Node& old)		// COPY CTOR 
{
	this->Qthing = old.Qthing;
		
	this->yes  = old.yes;		// new copy still points to the same children!
	this->no = old.no;
	
}// COPY CTOR

// ======================================================================
Node::~Node()	// DTOR
{
	// Tree DTOR does the work ...
}


// ======================================================================
// ---------- SETTERS ------------------------

void Node::StoreText(const string /*in*/ newText)
{
	this->Qthing = newText;
}// StoreText

// ======================================================================
void Node::AppendNo(Node* /*in*/ newNode)
{
	this->no = newNode;
}// AppendNo


// ======================================================================
void Node::AppendYes(Node* /*in*/ newNode)
{
	this->yes = newNode;
}// AppendYes


// ======================================================================
// ---------- GETTERS ------------------------

string Node::GetText() const
{
	return this->Qthing;		// return the text of current node
}// GetText


// ======================================================================
Node* Node::YChild() const
{
	return this->yes;			// return the yes child of the node
}// LChild


// ======================================================================
Node* Node::NChild() const
{
	return this->no;			// return the no child of the node
}// RChild


// ======================================================================
bool Node::IsLeaf() const
{
	return (this->NChild() == 0  &&  this->YChild() == 0 );
	
}// IsLeaf