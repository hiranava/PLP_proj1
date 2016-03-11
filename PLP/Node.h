#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <stdlib.h>
#include <string.h>

class Node{
public:
	Node();
	~Node();
	std::string value;
	Node* leftchild;
	Node* rightSibling;
};

#endif