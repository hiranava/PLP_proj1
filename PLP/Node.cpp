#include "Node.h"

//default constructor
Node::Node(){
	leftchild = NULL;
	rightSibling = NULL;
}

//destructor
Node::~Node(){
	if (leftchild != NULL){
		delete leftchild;
	}
	if (rightSibling != NULL){
		delete rightSibling;
	}
}
