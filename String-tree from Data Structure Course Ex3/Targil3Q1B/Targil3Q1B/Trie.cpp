#include "Trie.h"
void Trie::deleteNode(Node* n)
{
	if (n) //If Exists
	{
		for (auto& pair : n->chars)
			deleteNode(pair.second); //Go recursively until the end, and then delete from bottom to top.
		delete n;
	}
}

Trie::~Trie()
{
	deleteNode(this->root);
}


void Trie::insert(string str, int place)
{
	Node* p = root;
	Node* temp = p;
	for (int i = 0; i < str.length(); i++)
	{
		if (p->chars[str[i]] == nullptr) //If the node does not exit, create one
			p->chars[str[i]] = new Node;
		temp = p;
		p = p->chars[str[i]]; //go to the next level
		p->parent = temp; //Define the parent
	}
	p->endString = true;
	p->places.push_back(place);
}

list<int> Trie::search(string str)
{
	int counter = 0;
	list<int> plFirstThree;
	list<int> helper;
	Node* temp = nodeSearch(str, counter); //find the node of the last string
	if (!temp) //if the node didnt found, return empty list
	{
		cout << "The search required visiting " << counter << " nodes." << endl;
		return plFirstThree;
	}
	plFirstThree = scan(temp, counter, helper); //take all the places	
	cout << "The search required visiting " << counter << " nodes." << endl;
	return plFirstThree;
}

Node* Trie::nodeSearch(string str, int& count)
{
	Node* temp = this->root;
	count++;
	for (int i = 0; i < str.length(); i++) //Search if the string is exits
	{
		if (temp->chars[str[i]] != nullptr)
		{
			temp = temp->chars[str[i]];
			count++;
		}
		else
		{
			temp = nullptr;
			break;
		}
	}
	return temp;
}

list<int> Trie::scan(Node* n, int& counter, list<int>& pl)
{
	if (pl.size() > 2) //Check if the size is bigger than 2
		return pl;
	for (auto i = n->places.begin(); i != n->places.end(); i++)
	{
		pl.push_back(*i); //Push the place to the collective list of the places
		if (pl.size() > 2)
			return pl;
	}
	for (auto& pair : n->chars)
	{
		if (pair.second) //If exists
		{
			counter++;
			scan(pair.second, counter, pl); //Go recursively by preorder
		}
		if (pl.size() > 2)
			return pl;
	}
	return pl;
}


void Trie::deleteString(string str)
{
	Node* temp = root;
	if (temp)
	{
		for (int i = 0; i < str.length(); i++) //Check if the string is exits
		{
			if (temp->chars[str[i]])
				temp = temp->chars[str[i]];
			else
				return;
		}
		temp->endString = false; //Since it exits, make it non end, and clear it's places.
		temp->places.clear();
		if (!temp->chars.empty())//check if have sons
			return;
		temp = temp->parent; //if not, then we will go to his parent.
		for (int i = str.length() - 1; i > 0; i--)
		{
			if (temp == root) //if we reached the root, delete all the branches by make the father of all null.
			{
				temp->chars.erase(str[i]);
				return;
			}
			for (auto& pair : temp->chars) //check if he have other sons.if yes, the pointer to the string we want to delete will be erased.
				if (temp->chars[str[i]] != pair.second) //Skip the one we want to delete
				{
					temp->chars.erase(str[i]);
					return;
				}
			temp = temp->parent; //Since he dont have sons, go to his parent
		}
	}
}
