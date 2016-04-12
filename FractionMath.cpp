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
const char* state_one(const char*);
const char* state_two(const char*);
const char* state_four(const char*);
const char* state_five(const char*);
const char* state_six(const char*);
const char* state_seven(const char*);
const char* state_eight(const char*);
const char* state_nine(const char*);


const char* (*acts[STATES])(const char*) = {NULL, state_one, state_two, NULL, state_four, state_five, state_six, state_seven, state_eight, state_nine};
char alpha[ALPHA] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '/', '*', '\n', '\0' };
int trans[STATES][ALPHA] = {
	         /*0   1   2   3   4   5   6   7   8   9   +   -   /   *   s  \n  \0*/
	/* 0*/	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1, -1, -1, -1, -1, -1 },
	/* 1*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1, -1, -1, -1, -1, -1 },
	/* 2*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1,  6, -1,  3, -1, -1 },
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
const std::string temp;//for storing the numbers


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
				(acts[current]) && (c = acts[current](c));//work on the current character
				if (current != FINAL) {
					current = trans[current][alpha_index(c)];//make the trasition between states
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

const char* state_one(const char* c) {
	//this should be a [+/-]
	a.sign = (*c == '+') ? true : false;
	return c + 1;//returns the next character 
}

const char* state_two(const char* c) {
	//should be a #, and the next char will be a [space] or a [/] or a [#]
	//should be storing the current number char somewhere to put into either whole or numberator
	
	return c + 1;//returns the next character
}

const char* state_four(const char* c) {
	//should be the operator trasitioning into a new fraction

	return c + 1;//returns the next character
}

const char* state_five(const char* c) {
	//should be a #, and the next char will be a [/] or a [#]

	return c + 1;//returns the next character
}

const char* state_six(const char* c) {
	//should be a [/] and we should crunch all the chars we just read into the appropriate number in the fraction

	return c + 1;//returns the next character
}

const char* state_seven(const char* c) {
	//should be a #, and the next char will be a [space] or a [\n] or a [\0] or a [#]

	return c + 1;//returns the next character
}

const char* state_eight(const char* c) {
	//FINAL STATE: crunch the denomenator and prep for next line

	return c + 1;//returns the next character
}

const char* state_nine(const char* c) {
	//should be a [space], next is the operator 

	return c + 1;//returns the next character
}

