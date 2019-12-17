#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Node  {
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

public:
	// Constructor for the class
	Node(string name, string content = "") : name(name), content(content) {};
	void addChild(Node* node);
	Node* findNode(string name, string attribute, string value);
	bool isChild(Node* node);
	void deleteNode();
	Node* getChild(int i);
	void copy(Node* source, Node* destination);
	bool hasAttribute(string name, string value);
	bool removeLinkToParrent(Node* child);
	bool removeChild(Node* child);
	void addAttribute(string name, string value);
	void displayChildren(int spaces);
	void printChildren(ofstream& g, int spaces);
	void displayAttributes();
	void printAttributes(ofstream& g);
	void deleteAttributes();
};