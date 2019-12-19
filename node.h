#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Node {
	// Struct used to store an attribute and its value
	struct Attribute {
		string name;
		string value;

	};

private:
	string name;
	string content;

	list<unique_ptr<Attribute>> attributes;
	list<unique_ptr<Node>> child;

	friend class Tree;
protected:
	/* This function deletes the node
	   it is called from and all of the 
	   children of the node.
	   Do not use this function without calling
	   removeLinkToParent function.
	 */
	void deleteNode();
	// Recursive function to display a node and
	// the child nodes linked to it to the console
	void displayChildren(int spaces);
	// Recursive function to display a node and
	// the child nodes linked to it to the file
	void printChildren(ofstream& g, int spaces);


public:
	// Constructor for the class
	Node(string name, string content = "") : name(name), content(content) {};
	// Links the given node as child of the node 
	// it's called from
	void addChild(Node& node);
	// Returns a node with matching
	// name and content
	Node& findNode(string name, string content);
	// Returns a node with a matching
	// name and the given attribute
	Node& findNode(string name, string attribute, string value);
	// Returns the i-th child of the
	// node it is called from
	Node& getChild(int i);
	// Returns true if the node has the given attribute
	bool hasAttribute(string name, string value);
	// Removes the given child from the 
	// list of children of it's parrent
	bool removeLinkToParent(const Node& child);
	// Adds an attribute to the node it's called from
	void addAttribute(string name, string value);
	// Removes a given attribute from the
	// node it is called from
	void removeAttribute(string name, string value);
	// Used to display a node and it's 
	// attributes to the console
	void displayNode();
	// Outputs the attributes of the
	// given node to the console
	void displayAttributes();
	// Outputs the attributes of the
	// given node to the file
	void printAttributes(ofstream& g);
	// Removes all the attributes from a node3
	void deleteAttributes();
};
