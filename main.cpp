#include "tree.h"
#include <iostream>

using namespace std;

ofstream g("out.xml");

int main()
{
	Tree tree;
	Node* p, * x, * y, * z, * newElement, * source, * destination;

	cout << "The following DOM is the starting point.\n\n";
	p = new Node("Sectie");
	tree.addElement(p);
	x = new Node("CTI");
	x->addAttribute("An", "2010");
	x->addAttribute("Limba", "Romana");
	y = new Node("Lista elevi");
	p->addChild(x);
	x->addChild(y);

	z = new Node("Elev");
	z->addAttribute("Id", "52");
	z->addAttribute("Nume", "Popescu");
	z->addAttribute("Prenume", "Andreea");
	z->addAttribute("Studii", "Buget");
	y->addChild(z);
	x = new Node("Sex", "F");
	z->addChild(x);
	x = new Node("AnulNasterii", "1992");
	z->addChild(x);

	z = new Node("Elev");
	z->addAttribute("Id", "53");
	z->addAttribute("Nume", "Popa");
	z->addAttribute("Prenume", "Andrei");
	z->addAttribute("Studii", "Taxa");
	y->addChild(z);
	x = new Node("Sex", "M");
	z->addChild(x);
	x = new Node("AnulNasterii", "1991");
	z->addChild(x);

	x = new Node("CTI");
	x->addAttribute("An", "2010");
	x->addAttribute("Limba", "Engleza");
	p->addChild(x);

	y = new Node("Lista elevi");
	x->addChild(y);
	
	cout << "//////////////////////////////////////////////////////\n";
	tree.displayTree();
	cout << "/////////////////////////////////////////////////////\n";

	cout << "\nDelete Popa Andrei from CTI romana\n\n";
	
	tree.deleteNode(tree.findElement("Elev", "Nume", "Popa"));
	cout << "The DOM after the move:\n\n";
	cout << "//////////////////////////////////////////////////////\n";
	tree.displayTree();
	cout << "//////////////////////////////////////////////////////\n";

	cout << "\nAdd attribute to Popescu Andreea\n";
	tree.findElement("Elev", "Nume", "Popescu")->addAttribute("Medie", "9.63");

	cout << "The DOM after the operation:\n\n";
	cout << "//////////////////////////////////////////////////////\n";
	tree.displayTree();
	cout << "//////////////////////////////////////////////////////\n";
	 
	cout << "\nDelete Lista elevi from CTI engleza\n";
	tree.deleteNode(tree.findElement("CTI", "Limba", "Engleza")->getChild(0));

	cout << "The DOM after the operation:\n\n";
	cout << "//////////////////////////////////////////////////////\n";
	tree.displayTree();
	tree.printTree(g);
	cout << "//////////////////////////////////////////////////////\n";

	g.close();
	return 0;
}