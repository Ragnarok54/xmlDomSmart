#pragma once
#include "node.h"

class Tree {
private:
	list<unique_ptr<Node>> elements;

public:
	//Tree();
	// Adds element to the root in the tree
	void addElement(Node* newNode);
	// Deletes a given element from the tree
	void deleteElement(Node* node);
	// Moves the source node as a
	// child to the destination node
	void moveElement(Node& source, Node& destination);
	// Outputs the tree to the console
	void displayTree();
	// Outputs the tree to the file
	void printTree(ofstream& g);
	// Removes the child from the list 
	// of children of its parrent
	void removeChild(Node& child);
	// Returns the node with matching
	// name and content
	Node& findElement(string name, string content);
	// Return the node with matching 
	// name and attribute
	Node& findElement(string name, string atribute, string value);
	~Tree();
};
