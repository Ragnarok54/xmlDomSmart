#include "Tree.h"

void Tree::addElement(Node* newNode) {
	elements.push_back(unique_ptr<Node> (newNode));
}

void Tree::deleteNode(Node* node) {
	list<unique_ptr<Node>> ::iterator it = node->child.begin(), it2;

	while(it != node->child.end()) {
		it->get()->deleteNode();
		it = node->child.erase(it);
	}
	removeChild(node);
}

Node* Tree::findElement(string name, string atribute, string value) {
	Node* x = NULL;

	list <unique_ptr<Node>> ::iterator it;
	for (it = elements.begin(); it != elements.end(); it++) {
		x = (*it)->findNode(name, atribute, value);
		if (x != NULL)
			return x;
	}
	return NULL;
}

void  Tree::displayTree() {
	list <unique_ptr<Node>> ::iterator it;
	int i = 0;

	cout << "<?xml version = '1.0' encoding='UTF-8 standalone='yes'?>\n";
	cout << "<RootElement>\n";
	for (it = elements.begin(); it != elements.end(); it++) {
		(*it)->displayChildren(2);
		cout << endl;
	}
	cout << "</RootElement>\n\n";
}

void  Tree::printTree(ofstream &g) {
	list <unique_ptr<Node>> ::iterator it;
	int i = 0;

	g << "<?xml version = '1.0' encoding='UTF-8 standalone='yes'?>\n";
	g << "<RootElement>\n";
	for (it = elements.begin(); it != elements.end(); it++) {
		(*it)->printChildren(g, 2);
		g << endl;
	}
	g << "</RootElement>\n\n";
}
void Tree::moveElement(Node* source, Node* destination) {
	list<unique_ptr<Node>> ::iterator it;
	
	
	for (it = elements.begin(); it != elements.end(); it++) {
		if (it->get() == source) {
			elements.erase(it);
			break;
		}
		if (it->get()->removeLinkToParrent(source) == 1)
			break;
	}
	
	//This call here fails
	//destination->addChild(source);
}

void Tree::removeChild(Node * child) {
	list <unique_ptr<Node>> ::iterator it;
	
	for (it = elements.begin(); it != elements.end(); it++) {

		if (it->get() == child){
			elements.erase(it);
			break;
		}
		if (it->get()->removeChild(child) == 1)
			break;
	}
}