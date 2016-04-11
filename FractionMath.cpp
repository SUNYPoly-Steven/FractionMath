//Steven Savold
//Program #3
//CS 220 (Prof. Confer)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string* fragment(const string& line); //splits the string into substrings of fractions and operators


int main(int argc, char *argv[]) {

	fstream file("input.txt");
	string s;
	if (!file.is_open()) {
		cerr << "ERROR: FILE NOT FOUND" << endl;
		return 1;
	}

	getline(file, s);
	fragment(s);

	file.close();

	system("PAUSE");
	return 0;
}

string* fragment(const string& line) { 

}
