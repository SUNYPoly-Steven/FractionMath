//Steven Savold
//CS 220 (Prof. Confer)
//version 0.4.1

#include <iostream>
#include <fstream>
#include <string>

#define debug_lines 0

#define STATES  10
#define ALPHA   17
#define START    0
#define FINAL    8

int alpha_index(const char* c); //returns the index of the char in the alpha array (returns -1 if fails)
int to_digit(const char& c);
int to_int(const std::string& str);
const char* state_zero(const char*);
const char* state_one(const char*);
const char* state_two(const char*);
const char* state_three(const char*);
const char* state_four(const char*);
const char* state_five(const char*);
const char* state_six(const char*);
const char* state_seven(const char*);
const char* state_eight(const char*);
const char* state_nine(const char*);


const char* (*acts[STATES])(const char*) = { state_zero, state_one, state_two, state_three, state_four, state_five, state_six, state_seven, state_eight, state_nine };
char alpha[ALPHA] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '/', '*', ' ', '\n', '\0' };
int trans[STATES][ALPHA] = {
	         /*0   1   2   3   4   5   6   7   8   9   +   -   /   *   s  \n  \0*/
	/* 0*/	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1, -1, -1, -1, -1, -1 },
	/* 1*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1, -1, -1, -1, -1, -1 },
	/* 2*/  {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -1, -1,  6, -1,  3,  8,  8 },
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
	bool sign;

	frac() {
		whole = 0;
		numerator = 0;
		denominator = 1;
		sign = true;
	}

	frac(int n, int d) {
		whole = 0;
		numerator = n;
		denominator = d;
		sign = true;
	}

	bool is_zero() {
		if (numerator == 0 && whole == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	frac add(const frac& f) {
		return simplify(((numerator * f.denominator) + (f.numerator * denominator)), (denominator*f.denominator));
	}

	frac sub(const frac& f) {
		return simplify(((numerator * f.denominator) + ((-1*f.numerator) * denominator)), (denominator * f.denominator));
	}

	frac multiply(const frac& f) {
		return simplify(numerator * f.numerator, denominator * f.denominator);
	}

	frac divide(const frac& f) {
		return simplify(numerator * f.denominator, f.numerator * denominator);
	}

	frac simplify(int n, int d) {
		frac out;
		//return frac(n, d);
		if (n % d == 0) {
			out.numerator = n / d;
			out.denominator = 1;
		}
		else {
			int gcf = this->gcf(n, d);
			out.numerator = n / gcf;
			out.denominator = d / gcf;
		}
		
		return out;
	}

	frac convert() {
		frac out;
		whole = (sign) ? whole : whole*-1;
		out.numerator = (whole * denominator) + numerator;
		out.denominator = denominator;
		return out;
	}

	int gcf(int n, int d) {
		if (d == 0) {
			return n;
		}
		else {
			return gcf(d, n % d);
		}
	}
};

frac a;
frac total;
std::string temp;//for storing the numbers read, to compile into a part of the fraction
char op = ' ';
bool isWhole = false;


int main(int argc, char* argv[]) {

	std::fstream *file = new std::fstream("small_test.txt"); //<-- make sure this is changed before you hand it in//
	if (file->is_open()) {
		std::string s;
		int current;
		bool quit;
		do {
			std::getline(*file, s);
			const char* c = s.c_str();
			if (s[0] == '#' || s[0] == '\0') {
				continue;
			}
			current = START;
			quit = false;
			do {
				(acts[current]) && (c = acts[current](c));//work on the current character
				if (current != FINAL) {
#if debug_lines
std::cout << "PRE-CURRENT(" << *c << "): " << current << ' ';
#endif
					current = trans[current][alpha_index(c)];//make the trasition between states
#if debug_lines
std::cout << " POST-CURRENT(" << *c << "): " << current << ' ';
#endif
					if (current == -1) {
						quit = true;
						std::cerr << "Current is -1, character given was: " << *c << std::endl;
					}
				}
				else {
					quit = true;
				}
			} while (!quit);
			std::cout << total.numerator << '/' << total.denominator << std::endl;
			total.sign = true;
			total.whole = 0;
			total.numerator = 0;
			total.denominator = 1;
		} while (!file->eof());
	}
	else {
		std::cerr << "ERROR: FILE NOT FOUND" << std::endl;
	}

	system("PAUSE");
	return 0;

}

int alpha_index(const char* c) {
	for (int i = 0; i < ALPHA; ++i) {
		if (alpha[i] == *c) {
			return i;
		}
	}
	//if char not found
	return -1;
}

int to_int(const std::string& str) {
	int total = 0;
	for (int i = 0, j = str.length() - 1; j > -1; ++i, --j) {
		total += to_digit(str[j]) * pow(10, i);
	}
	return total;
}

int to_digit(const char& c) {
	if (c == '0') {
		return 0;
	}
	else if (c == '1') {
		return 1;
	}
	else if (c == '2') {
		return 2;
	}
	else if (c == '3') {
		return 3;
	}
	else if (c == '4') {
		return 4;
	}
	else if (c == '5') {
		return 5;
	}
	else if (c == '6') {
		return 6;
	}
	else if (c == '7') {
		return 7;
	}
	else if (c == '8') {
		return 8;
	}
	else if (c == '9') {
		return 9;
	}
	else {
		return -1;
	}
}

const char* state_zero(const char* c) {
	//comes from start or from state 4
#if debug_lines
std::cout << "function 0" << std::endl;
#endif
	if (*c == ' ') {
		return c + 1;
	}
	else {
		return c;
	}
}

const char* state_one(const char* c) {
	//this should be a [+/-]
	a.sign = (*c == '+') ? true : false;
#if debug_lines
std::cout << "function 1" << std::endl;
#endif
	return c + 1;//returns the next character 
}

const char* state_two(const char* c) {
	//should be a #, and the next char will be a [space] or a [/] or a [#]
	//should be storing the current number char somewhere to put into either whole or numberator
	temp.push_back(*c);//make a copy of the char in the string
	if (*(c+1) == '\0' || *(c+1) == '\n') {
		isWhole = true;
	}
#if debug_lines
std::cout << "function 2" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_three(const char* c) {
	//should be a [space] and the next char will be either a [+,-,/,*] or a [#]
	//should compile and store the number
	a.whole = to_int(temp);
	temp = "";
#if debug_lines
std::cout << "function 3" << std::endl;
#endif
	return c + 1;
}

const char* state_four(const char* c) {
	//should be the [+,-,/,*] trasitioning into the next fraction
	//should complete the operation and reset any nessessary variables
	if (!total.is_zero()) {
		if (op == '+') {
			total = total.add(a.convert());
		}
		else if (op == '-') {
			total = total.sub(a.convert());
		}
		else if (op == '*') {
			total = total.multiply(a.convert());
		}
		else if (op == '/') {
			total = total.divide(a.convert());
		}
	}
	else {
		total = total.add(a.convert());
	}

	op = *c;
	a.sign = true;
	a.whole = 0;
	a.numerator = 0;
	a.denominator = 1;

#if debug_lines
std::cout << "function 4" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_five(const char* c) {
	//should be a #, and the next char will be a [/] or a [#]
	//calcs the numerator of a mixed number
	temp.push_back(*c);
#if debug_lines
std::cout << "function 5" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_six(const char* c) {
	//should be a [/] and we should crunch all the chars we just read into the appropriate number in the fraction
	a.numerator = to_int(temp); //store the number
	temp = ""; //flush temp
#if debug_lines
std::cout << "function 6" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_seven(const char* c) {
	//should be a #, and the next char will be a [space] or a [\n] or a [\0] or a [#]
	temp.push_back(*c);
#if debug_lines
std::cout << "function 7" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_eight(const char* c) {
	//FINAL STATE: crunch the denomenator and prep for next line
	if (isWhole) {
		a.whole = to_int(temp);
		isWhole = false;
	}
	else {
		a.denominator = to_int(temp);
	}
	temp = "";

	if (!total.is_zero()) {
		if (op == '+') {
			total = total.add(a.convert());
		}
		else if (op == '-') {
			total = total.sub(a.convert());
		}
		else if (op == '*') {
			total = total.multiply(a.convert());
		}
		else if (op == '/') {
			total = total.divide(a.convert());
		}
	}
	else {
		total = total.add(a.convert());

	}

	a.sign = true;
	a.whole = 0;
	a.numerator = 0;
	a.denominator = 1;

#if debug_lines
std::cout << "function 8" << std::endl;
#endif
	return c + 1;//returns the next character
}

const char* state_nine(const char* c) {
	//should be a [space], next is the operator 

	a.denominator = to_int(temp);
	temp = "";

#if debug_lines
std::cout << "function 9" << std::endl;
#endif
	return c + 1;//returns the next character
}

