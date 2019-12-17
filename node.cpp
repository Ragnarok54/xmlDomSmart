#include "node.h"

void Node::addChild(Node* node) {
	this->child.push_back(unique_ptr<Node> (node));
}

bool Node::isChild(Node* node) {
	list<unique_ptr<Node>> ::iterator it = child.begin(), a;
	bool x = 0;
	
	for (it = child.begin(); it != child.end(); it++) {
		if (it->get() == node)
			x = 1;
		x = it->get()->isChild(node);
	}
	return x;
}

Node* Node::getChild(int i) {
	list<unique_ptr<Node>> ::iterator it = child.begin();

	advance(it, i);
	return it->get();
}

void Node::copy(Node* source, Node* destination) {
	Node* x = NULL;

	destination = new Node(source->name, source->content);
	
	list<unique_ptr<Node>> ::iterator it;

	for (it = source->child.begin(); it != source->child.end(); it++) {
		it->get()->copy(it->get(), x);
		destination->addChild(x);

	}
}

void Node::addAttribute(string name, string value) {
	Attribute* atb = new Attribute;

	atb->name = name;
	atb->value = value;

	attributes.push_back(unique_ptr<Attribute> (atb));
}

bool Node::hasAttribute(string name, string value) {
	bool flag = 0;
	list<unique_ptr<Attribute>> ::iterator it;

	if (attributes.size() > 0) {
		for (it = attributes.begin(); it != attributes.end(); it++) {
			if ((*it)->name == name && (*it)->value == value) {
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

Node* Node::findNode(string name, string attribute, string value) {
	Node* x = NULL;

	if (this->name == name && hasAttribute(attribute, value)) {
		return this;
	}
	else {
		list <unique_ptr<Node>> ::iterator it;
		for (it = child.begin(); it != child.end(); it++) {
			x = (*it)->findNode(name, attribute, value);
			if (x != NULL)
				return x;
		}
	}

	return NULL;
}

bool Node::removeChild(Node* child) {
	list<unique_ptr<Node>> ::iterator it, it2;
	bool x = 0;

	if (x == 1)
		return x;
	for (it = this->child.begin(); it != this->child.end(); it++) {
		if (it->get() == child) {
			it = this->child.erase(it);
			return x;
		}
		x = it->get()->removeChild(child);
	}
}

bool Node::removeLinkToParrent(Node* child) {
	list<unique_ptr<Node>> ::iterator it, it2;
	bool x = 0;

	for (it = this->child.begin(); it != this->child.end(); it++) {
		for (it2 = it->get()->child.begin(); it2 != it->get()->child.end(); it2++) {
			if (it2->get() == child) {
				it->get()->child.erase(it2);
				return 1;
			}
			x = it->get()->removeLinkToParrent(child);
			if (x == 1)
				return 1;
		}
	}
	return x;
}


void Node::displayAttributes() {
	list<unique_ptr<Attribute>> ::iterator it;

	for (it = attributes.begin(); it != attributes.end(); it++) {
		cout << " " << (*it)->name << "='" << (*it)->value << "'";
	}
}

void Node::printAttributes(ofstream& g) {
	list<unique_ptr<Attribute>> ::iterator it;

	for (it = attributes.begin(); it != attributes.end(); it++) {
		g << " " << (*it)->name << "='" << (*it)->value << "'";
	}
}


void Node::deleteNode() {
	deleteAttributes();

	if (child.size() > 0) {
		list<unique_ptr<Node>> ::iterator it = child.begin(), a;
		for (it = child.begin(); it != child.end(); it++) {
			(*it)->deleteAttributes();
			(*it)->deleteNode();
		}
	}
}

void Node::deleteAttributes() {
	list<unique_ptr<Attribute>> ::iterator it = attributes.begin();
	
	while (it != attributes.end()) {
		it = attributes.erase(it);
	}
}

void Node::displayChildren(int spaces) {
	int i = spaces;
	list <unique_ptr<Node>> ::iterator it;

	while (i) {
		cout << " ";
		i--;
	}
	cout << "<" << name;
	displayAttributes();
	cout << ">";

	for (it = child.begin(); it != child.end(); it++) {
		cout << endl;
		(*it)->displayChildren(spaces + 2);
	}

	if (content != "") {
		if (child.size() > 0) {
			cout << '\n';
			i = spaces;
			while (i) {
				cout << " ";
				i--;
			}
		}
		cout << content;
	}
	else {
		cout << endl;
		i = spaces;
		while (i) {
			cout << " ";
			i--;
		}
	}
	cout << "</" << name << ">";
}



void Node::printChildren(ofstream &g, int spaces) {
	int i = spaces;
	list <unique_ptr<Node>> ::iterator it;

	while (i) {
		g << " ";
		i--;
	}
	g << "<" << name;
	printAttributes(g);
	g << ">";

	for (it = child.begin(); it != child.end(); it++) {
		g << endl;
		(*it)->printChildren(g, spaces + 2);
	}

	if (content != "") {
		if (child.size() > 0) {
			g << '\n';
			i = spaces;
			while (i) {
				g << " ";
				i--;
			}
		}
		g << content;
	}
	else {
		g << endl;
		i = spaces;
		while (i) {
			g << " ";
			i--;
		}
	}
	g << "</" << name << ">";
}