#include "Book.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>

using namespace std;

Book::Book(const string& filepath) {
	// Open the file at the specified filepath
	ifstream file(filepath);

	// Check if the file is successfully opened
	if (file.is_open()) {
		// Read the entire content of the file into a stringstream
		stringstream buffer;
		buffer << file.rdbuf();
		content = buffer.str();
		file.close();

		// Transform the content to lowercase
		transform(content.begin(), content.end(), content.begin(), ::tolower);

		// Replace consecutive whitespaces with a single space using regular expressions
		regex pattern("\\s+"); // Matches one or more whitespace characters
		content = regex_replace(content, pattern, " ");

		// Insert content into the trie
		processContent();
	}
	else {
		// If the file fails to open, throw an exception
		throw invalid_argument("Unable to open file");
	}
}

void Book::processContent()
{
	istringstream stream(content);
	bool flag = true;
	// TODO: Go over the book content and add any triplet of consecutive words to the trie.
	// Assume the words are separated by spaces.
	string str;
	int nextWord;//saves the position of the next word after the first space.
	int stringStart = 0;
	for (int i = 0; i < content.length(); i++)
	{
		stringStart = i;//saves the start of the sub string.
		int spaceCount = 0; //counts the amount of spaces.
		while (spaceCount < 3) //Stop when we have triplet
		{
			if (content[i] == ' ')
			{
				if (spaceCount == 0) //After reaching the first word, the next word will be from here.
					nextWord = i;
				spaceCount++;
			}
			if (spaceCount != 3) //This is to not add space at theend of the string
			{
				str += content[i];
				i++;
			}
			if (i == content.length()) //If we reached to the end then stop
			{
				flag = false;
				break;
			}
		}
		this->subStrings.insert(str, stringStart);
		str = "";
		if (flag)
			i = nextWord; //Go backwards to the next word in the triplet
	}
}

int Book::calcStartPos(int& leftover, bool& start, int location)
{
	string str = "";
	int spaceCount = 0;
	while (spaceCount < 6) //To reach only 5 words
	{
		if (location == 0) //If we at the start
		{
			start = true; //This is the start of new sentence
			leftover = 6 - spaceCount; //Set the number of words that left
			return 0;
		}
		if (content[location] == ' ')
		{
			spaceCount++;
			str += content[location];
		}
		else if (content[location] == '.')
		{
			start = true;
			break;
		}
		location--;
	}
	leftover = 6 - spaceCount; //Set the number of words that left
	return location + 2; //+2 because I don't want the sentence to start with 'space' and '.'.

}

int Book::calcEndPos(int leftover, bool& end, int location)
{
	int spaceCount = 0;
	bool flag = false;
	while (spaceCount < 5 + leftover) //We need to go minimum of 5 words + what is left (up to 10 in sum).
	{
		if (location == this->content.size() - 1)  //If we at the end of the file
		{
			end = true; //Do not print "..." at the end
			return location;
		}
		if (content[location] == ' ')
			spaceCount++;
		else if (content[location] == '.')
		{
			end = true;
			flag = true; //To note that we stopped because "." is found.
			break;
		}
		location++;
	}
	return	flag ? location : location - 2; //If we stopped because end of word, print it, but else, return location-2 which is to take only the last full word
}


void Book::searchAndPrint(const string& query) 
{
	list<int> locations = this->subStrings.search(query); //Search for the node by his string
	if (locations.empty()) {
		cout << "No results" << endl;
		return;
	}
	cout << "Sentences matching the prefix:" << endl;
	while (!locations.empty())
	{
		int place = locations.front(); //saves the first locaiton on the list.
		string str = extractSentence(place);
		cout << str << endl;
		locations.pop_front();
	}
}

string Book::extractSentence(int location) 
{
	bool frontEnd = false;//checks if end sentence.
	bool backEnd = false;//checks if starts sentence.	
	int leftover = 0; //Save the number of words that is left after calcuting the starting position.

	int startPos = calcStartPos(leftover, backEnd, location); //calculating the start position
	int	endPos = calcEndPos(leftover, frontEnd, location); //calculating the end position.

	string str;
	if (!backEnd) //If don't start new sentence
		str = "...";
	for (int i = startPos; i < location; i++) //Print until the original location
		str += content[i];
	str += "*"; //Print "*" where we start
	for (int i = location; i <= endPos; i++) //Print the rest
		str += content[i];
	if (!frontEnd) //If this is not the end of the sentnce
		str += ("...");
	return str;
}

void Book::censorQuery(const string& query)
{
	this->subStrings.deleteString(query);
}
