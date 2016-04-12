//Steven Savold
//CS 220 (Prof. Confer)
//version 0.4.1

#include <iostream>
#include <fstream>
#include <string>

#define STATES  10
#define ALPHA   17
#define START    0
#define FINAL    8

int alpha_index(const char* c); //returns the index of the char in the alpha array (returns -1 if fails)
const char* one(const char*);
const char* two(const char*);
const char* four(const char*);
const char* five(const char*);
const char* six(const char*);
const char* seven(const char*);
const char* eight(const char*);
const char* nine(const char*);


const char* (*acts[STATES])(const char*) = {NULL, one, two, NULL, four, five, six, seven, eight, nine};
char alpha[ALPHA] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '/', '*', '\n', '\0' };
int trans[STATES][ALPHA] = {
	         /*0   1   2   3   4   5   6   7   8   9   +   -   /   *   s  \n  \0*/
	/* 0*/	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1, -1, -1, -1, -1, -1 },
	/* 1*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1, -1, -1, -1, -1, -1 },
	/* 2*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1,  6, -1, -1, -1, -1 },
	/* 3*/  {  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  4,  4,  4,  4, -1, -1, -1 },
	/* 4*/  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1 },
	/* 5*/  {  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, -1, -1,  6, -1, -1, -1, -1 },
	/* 6*/  {  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, -1, -1, -1, -1, -1, -1, -1 },
	/* 7*/  {  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, -1, -1, -1, -1,  9,  8,  8 },
	/* 8*/  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	/* 9*/  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  4,  4,  4, -1, -1, -1 },
};

struct frac {
	int whole;
	int numerator;
	int denominator;
	bool sign; //+ is true
	
	frac() {
		whole = 0;
		numerator = 0;
		denominator = 0;
		sign = true;
	}
	
};

frac a;
frac b;


int main(int argc, char* argv[]) {

	std::fstream *file = new std::fstream("test.txt"); //<-- make sure this is changed before you hand it in//
	if (file->is_open()) {
		std::string s;
		int current;
		bool quit;
		do {
			std::getline(*file, s);
			const char* c = s.c_str();
			current = START;
			quit = false;
			do {
				(acts[current]) && (c = acts[current](c));
				if (current != FINAL) {
					current = trans[current][alpha_index(c)];
				}
				else {
					quit = true;
				}
			} while (!quit);
		} while (!file->eof());
	}
	else {
		std::cerr << "ERROR: FILE NOT FOUND" << std::endl;
	}

	system("PAUSE");
	return 0;

}

int alpha_index(const char* c) {
	return -1;
}

const char* one(const char* c) {
	//this should be a [+/-]
	a.sign = (*c == '+') ? true : false;
	return c;//what do I return?
}

const char* two(const char* c) {
	std::cout << "two" << std::endl;
	return c;
}

const char* four(const char* c) {
	std::cout << "four" << std::endl;
	return c;
}

const char* five(const char* c) {
	std::cout << "five" << std::endl;
	return c;
}

const char* six(const char* c) {
	std::cout << "six" << std::endl;
	return c;
}

const char* seven(const char* c) {
	std::cout << "seven" << std::endl;
	return c;
}

const char* eight(const char* c) {
	std::cout << "eight" << std::endl;
	return c;
}

const char* nine(const char* c) {
	std::cout << "nine" << std::endl;
	return c;
}

