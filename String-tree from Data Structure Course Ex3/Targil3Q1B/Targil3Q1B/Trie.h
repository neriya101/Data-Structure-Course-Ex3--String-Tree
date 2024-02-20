#pragma once
#include "Node.h"
#include <string>
#include <iostream>
using namespace std;
class Trie
{
private:
	Node* root;
	void deleteNode(Node* n);//help function to delete the tree.
	Node* nodeSearch(string str, int& count); //Help function to find node by string and count the number of nodes that visited.
	list<int> scan(Node* n, int& conuter, list<int>& pl); //Help function to find 3 first places by string and count the number of nodes that visited. 
public:
	Trie()
	{
		root = new Node();
		root->parent = nullptr;
	}
	~Trie();
	void insert(string str, int place);
	list<int> search(string str);
	void deleteString(string str);
};

