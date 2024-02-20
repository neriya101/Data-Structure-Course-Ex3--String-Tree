#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Trie.h"
using namespace std;

class Book {
private:
	string content;
	Trie subStrings;
	void processContent();
	int calcStartPos(int& leftover, bool& end, int location); //Calculating the starting position to print
	int calcEndPos(int leftover, bool& end, int location); //Calculating the ending position to print

public:
	Book(const string& filepath);
	string extractSentence(int location); //Take the sentence that we want to print
	void searchAndPrint(const string& query); //Search the sentence to print
	void censorQuery(const string& query); //Censor
};