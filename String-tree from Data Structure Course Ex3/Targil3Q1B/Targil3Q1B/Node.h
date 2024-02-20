#pragma once
#include<list>
#include <map>
using namespace std;
class Node
{
public:
	bool endString;
	list<int> places; //Places in book
	map<char, Node*> chars;
	Node* parent;
	Node() : endString(false), parent(nullptr) {}
};

