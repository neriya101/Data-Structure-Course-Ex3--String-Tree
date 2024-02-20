//Neriya Horenczyk 208729327
//Ziv Hoter 213241243

#include <iostream>
#include "Book.h"
#include "Trie.h"
using namespace std;

int main() {

    string prefix, command, path;
    cout << "Enter the book's path: ";
    getline(cin, path); // Read entire line as input
    Book book(path);

    while (true) {
        cout << "Enter 's' to search, 'c' to censor or 'e' to quit: ";
        getline(cin, command); // Read entire line as input

        if (command == "e") {
            break;
        }
        if (command == "s") {
            cout << "Enter prefix:" << endl;
            getline(cin, prefix); // Read entire line as input
            book.searchAndPrint(prefix);
        }
        if (command == "c") {
            cout << "Enter search term to censor:" << endl;
            getline(cin, prefix); // Read entire line as input
            book.censorQuery(prefix);
        }
    }

    return 0;
}