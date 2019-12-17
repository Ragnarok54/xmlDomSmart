#pragma once
#include "node.h"

class Tree {
private:
	list<unique_ptr<Node>> elements;

public:
	//Tree();
	void addElement(Node *newNode);
	void deleteNode(Node* node);
	void moveElement(Node* source, Node* destination);
	void displayTree();
	void printTree(ofstream& g);
	void removeChild(Node* child);
	Node* findElement(string name, string atribute, string value);
	//~Tree();
};
