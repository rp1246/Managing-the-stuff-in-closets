/*
Name:Raj Phuyal
Compiler Used:GCC
Program Description:In this project, We write a program that implements and manages several user defined BST's where each BST's will represent a container and inventory of item it stores.

*/

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include "BST.h"

using namespace std;

Container containers;

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

void trim(string &str) {
	str = trim((char*)str.c_str());
}

void printInputDescription() {
	cout << ">> Input Command" << endl;
}

void printErrorCommand() {
	cout << ">> Unknown Command ! Please enter command in valid form." << endl;
}

void handleCommand(stringstream &ss, string cmd) {
	
	string file = "", str, type, container, item, tmp, uid, count;
	int countnum = 0;
	
	if (cmd == "exit") {
		// exit program
		exit(0);
	} else if (cmd == "load") {
		// parses the contents of the file
		getline(ss, file, ' ');
		trim(file);

		ifstream fin(file.c_str());
		while (true) { 
			str = "";
			getline(fin, str);
			if (str == "") break;
			stringstream fs(str);
			getline(fs, cmd, ' ');
			trim(cmd);
			/* Call handleCommand function recursively so that
			commands in file including "load" will be executed properly */
			handleCommand(fs, cmd);
			cout << "File Loaded!" << endl;
		}
	} else if (cmd == "display") {
		getline(ss, container, ' ');
		trim(container);
		getline(ss, type, ' ');
		trim(type);
		if (type == "in" || type == "post" || type == "pre") {
			// displays the current contents of specified container in  respective orders.
			containers.display(type, container);
		} else {
			// Input commands may be wrong command then display this message
			printErrorCommand();
		}
	} else if (cmd == "find") {
		// searches the each container for specified item.
		getline(ss, item, ' ');
		trim(item);
		getline(ss, tmp, ' ');
		trim(tmp);
		if (tmp == "") {
			containers.find_item(item);
		} else if (tmp == "in") {
			getline(ss, container, ' ');
			trim(container);
			containers.find_item_in(item, container);
		} else {
			// Input commands may be wrong command then display this message
			printErrorCommand();
			return;
		}
	} else if (cmd == "remove") {
		getline(ss, uid, ' ');
		trim(uid);
		getline(ss, tmp, ' ');
		trim(tmp);
		if (tmp == "") {
			// Removes the specified item from each container.
			containers.remove_item(uid);
			cout << "Remove success!" << endl;
		} else if (tmp == "from"){
			// Removes the specified item from each container.
			getline(ss, container, ' ');
			trim(container);
			containers.remove_item_from(uid, container);
			cout << "Remove success!" << endl;
		} else {
			// Input commands may be wrong command then display this message
			printErrorCommand();
		}
	} else if (cmd == "insert") {
		getline(ss, item, ' ');
		trim(item);
		getline(ss, count, ' ');
		trim(count);
		getline(ss, tmp, ' ');
		trim(tmp);
		if (tmp == "") {
			// Input commands may be wrong command then display this message
			printErrorCommand();
		} else if (tmp == "into"){
			getline(ss, container, ' ');
			trim(container);
			countnum = stoi(count);
			containers.insert_item_into(item, countnum, container);
			cout << "Inserted!" << endl;
			
		} else {
			// Input commands may be wrong command then display this message
			printErrorCommand();
		}
	} else if (cmd == "create") {
		getline(ss, container, ' ');
		trim(container);
		containers.create(container);
		cout << "Created!" << endl;
	} else if (cmd == "destroy") {
		getline(ss, container, ' ');
		trim(container);
		containers.destroy(container);
		cout << "Destroyed!" << endl;
	} else {
		// Input commands may be wrong command then display this message
		printErrorCommand();
	}
}

int main() {
	string str;
	string cmd;
	while (true) {
		// Print Input description
		printInputDescription();
		// Input command line
		getline(cin, str);
		stringstream ss(str);
		//Get command token
		getline(ss, cmd, ' ');
		// Remove unnecessary whitespace
		trim(cmd);
		// Do actions according to command category
		handleCommand(ss, cmd);
	}
	return 0;
}
