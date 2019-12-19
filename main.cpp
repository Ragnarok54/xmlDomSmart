#include "tree.h"
#include <iostream>

using namespace std;

ofstream g("out.xml");

int main()
{
	Tree tree;
	Node* p, * x, * y, * z, * newElement, * source, * destination;
	int input, option, nodeOption, noAttributes, nodeLocation, answer;
	string name, content, value, attribute;
	ofstream g;

	//Menu
	cout << "Select one of the following:\n1. Demonstration\n2. Input by hand\n3. Exit\n";
	cin >> input;
	switch (input) {
		//Demonstration mode
	case 1: {
		cout << "The following DOM is the starting point.\n\n";
		p = new Node("Sectie");
		tree.addElement(p);
		x = new Node("CTI");
		x->addAttribute("An", "2010");
		x->addAttribute("Limba", "Romana");
		y = new Node("Lista elevi");
		p->addChild(*x);
		x->addChild(*y);

		z = new Node("Elev");
		z->addAttribute("Id", "52");
		z->addAttribute("Nume", "Popescu");
		z->addAttribute("Prenume", "Andreea");
		z->addAttribute("Studii", "Buget");
		y->addChild(*z);
		x = new Node("Sex", "F");
		z->addChild(*x);
		x = new Node("AnulNasterii", "1992");
		z->addChild(*x);

		z = new Node("Elev");
		z->addAttribute("Id", "53");
		z->addAttribute("Nume", "Popa");
		z->addAttribute("Prenume", "Andrei");
		z->addAttribute("Studii", "Taxa");
		y->addChild(*z);
		x = new Node("Sex", "M");
		z->addChild(*x);
		x = new Node("AnulNasterii", "1991");
		z->addChild(*x);

		x = new Node("CTI");
		x->addAttribute("An", "2010");
		x->addAttribute("Limba", "Engleza");
		p->addChild(*x);

		y = new Node("Lista elevi");
		x->addChild(*y);

		cout << "//////////////////////////////////////////////////////\n";
		tree.displayTree();
		cout << "/////////////////////////////////////////////////////\n";

		cout << "\nMove Popa Andrei from CTI romana to CTI engleza\n\n";
		//getChild is only used here to move the element under "Lista elevi"
		tree.moveElement(tree.findElement("Elev", "Nume", "Popa"), tree.findElement("CTI", "Limba", "Engleza").getChild(0));
		cout << "The DOM after the move:\n\n";
		cout << "//////////////////////////////////////////////////////\n";
		tree.displayTree();
		cout << "//////////////////////////////////////////////////////\n";

		cout << "\nEdit Popescu Andreea's studii from buget to taxa\n";
		tree.findElement("Elev", "Nume", "Popescu").removeAttribute("Studii", "Buget");
		tree.findElement("Elev", "Nume", "Popescu").addAttribute("Studii", "Taxa");

		cout << "The DOM after the operation:\n\n";
		cout << "//////////////////////////////////////////////////////\n";
		tree.displayTree();
		cout << "//////////////////////////////////////////////////////\n";

		cout << "\nDelete Lista elevi from CTI engleza\n";
		tree.deleteElement(&tree.findElement("CTI", "Limba", "Engleza").getChild(0));

		cout << "The DOM after the operation:\n\n";
		cout << "//////////////////////////////////////////////////////\n";
		tree.displayTree();
		g.open("out.xml");
		tree.printTree(g);
		g.close();
		cout << "//////////////////////////////////////////////////////\n";
		// Comment this line for normal functions. 
		// Or keep it to have fun with the DOM
		cout << "Do you want to go to modify this DOM now?\n1.Yes\n2.No\n";
		cin >> answer;
		if (answer == 1) {
			goto Interaction;
		}
		else {
			return 0;
		}
	}

		  //Interaction mode
	case 2:
	Interaction:

		while (1) {
			cout << "\n1.Add element to DOM\n2.Delete element\n3.Move element\n4.Delete attribute from element\n5.Display DOM\n6.Print DOM\n7.Exit\n";
			cin >> option;

			switch (option) {
				//Add and element
			case 1:
				cout << "1.Simple element\n2.Element with content\n3.Element with attributes\n4.Element with content and attributes\n";
				cin >> nodeOption;
				switch (nodeOption) {

					//Add simple element to DOM
				case 1:
					cout << "Input node name: ";
					cin >> name;
					newElement = new Node(name);
					cout << '\n';
					break;

					//Add element with content to DOM
				case 2:
					cout << "Input node name and content: ";
					cin >> name >> content;
					cout << '\n';
					newElement = new Node(name, content);
					break;

					//Add element with attributes to DOM
				case 3:
					cout << "Input node name: ";
					cin >> name;
					cout << '\n';
					newElement = new Node(name);
					//Get attributes;
					cout << "Input number of attributes: ";
					cin >> noAttributes;
					cout << '\n';
					while (noAttributes) {
						cout << "Input attribute name and value: ";
						cin >> attribute >> value;
						cout << '\n';
						newElement->addAttribute(attribute, value);
						noAttributes--;
					}
					break;

					//Add element with content and attributes to DOM
				case 4:
					cout << "Input node name and content: ";
					cin >> name >> content;
					cout << '\n';
					newElement = new Node(name, content);
					//Get attributes
					cout << "Input number of attributes: ";
					cin >> noAttributes;
					cout << '\n';
					while (noAttributes) {
						cout << "Input attribute name and value: ";
						cin >> attribute >> value;
						cout << '\n';
						newElement->addAttribute(attribute, value);
						noAttributes--;
					}
					break;

					//Unacceptable input
				default:
					cout << "\nIncorrect option. Program will exit.\n";
					return 0;
				}

				//Where to add the new element
				cout << "\nChose one of the following:\n1.Add the element to root\n2.Add the element as a child to another element\n";
				cin >> nodeLocation;
				if (nodeLocation == 1) {
					tree.addElement(newElement);
				}
				else {
					cout << "\n1.Input element by name and content\n2.Input element by attribute name and value\n";
					cin >> nodeLocation;
					if (nodeLocation == 1) {
						cout << "Input element name and content: ";
						cin >> name >> content;
						cout << '\n';
						tree.findElement(name, content).addChild(*newElement);
					}
					else {
						cout << "Input element name, attribute and attribute value: ";
						cin >> name >> attribute >> value;
						cout << '\n';
						tree.findElement(name, attribute, value).addChild(*newElement);
					}
				}
				cout << "\nYou have added ";
				newElement->displayNode();
				cout << " to the DOM\n\n";
				break;

				//Delete an element
			case 2:
				cout << "1.Delete element by name and content\n2.Delete element by name and attribute\n";
				cin >> nodeOption;
				switch (nodeOption) {
					//Delete by name and content
				case 1:
					cout << "Input element name and content: ";
					cin >> name >> content;
					cout << "\n";
					tree.deleteElement(&tree.findElement(name, content));
					break;

					//Delete by name and attribute
				case 2:
					cout << "Input element name: ";
					cin >> name;
					cout << "\n";
					cout << "Input element attribute name and value: ";
					cin >> attribute >> value;
					tree.deleteElement(&tree.findElement(name, attribute, value));
					break;

					//Unacceptable input
				default:
					cout << "Incorrect option. Program will exit.\n";
					return 0;
				}
				break;

				//Move an element to another parent
			case 3:
				//Find the element that needs to be moved
				cout << "1.Move element by name and content\n2.Move element by attribute and value\n";
				cin >> nodeLocation;
				cout << '\n';
				if (nodeLocation == 1) {
					cout << "Input the name and content of the element you want moved: ";
					cin >> name >> content;
					cout << '\n';
					source = &tree.findElement(name, content);
				}
				else {
					cout << "Input the name, attribute and value of the element you want moved: ";
					cin >> name >> attribute >> value;
					cout << '\n';
					source = &tree.findElement(name, attribute, value);
				}
				//Find the destination of the move operation
				cout << "1.Input destination by name and content\n2.Input destination by attribute and value\n";
				cin >> nodeLocation;
				cout << '\n';
				if (nodeLocation == 1) {
					cout << "Input the name and content of the destination element: ";
					cin >> name >> content;
					cout << '\n';
					destination = &tree.findElement(name, content);
				}
				else {
					cout << "Input the name, attribute and value of the destination element: ";
					cin >> name >> attribute >> value;
					cout << '\n';
					destination = &tree.findElement(name, attribute, value);
				}
				tree.moveElement(*source, *destination);
				break;

				//Delete attribute from element
			case 4:
				cout << "Input element name: ";
				cin >> name;
				cout << "\n";
				cout << "Input element attribute name and value: ";
				cin >> attribute >> value;
				tree.findElement(name, attribute, value).removeAttribute(attribute, value);
				break;

				//Display DOM to console
			case 5:
				tree.displayTree();
				break;

				//Print DOM to file
			case 6:
				g.open("out.xml");
				tree.printTree(g);
				cout << "You can find the DOM in the out.xml file\n";
				g.close();
				break;

				//Exit
			case 7:
				return 0;

				//Unacceptable input
			default:
				cout << "Incorrect option. Program will exit.\n";
				return 0;
			}
		}
		//Exit
	case 3:
		return 0;

		//Unacceptable input
	default:
		cout << "Incorrect option. Program will exit.\n";
		return 0;
	}
	
	return 0;
}
