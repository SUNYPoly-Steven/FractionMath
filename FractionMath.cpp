//Steven Savold
//CS 220 (Prof. Confer)
//version 0.4.1

#include <iostream>
#include <fstream>
#include <string>

#define debug_lines 1

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
		denominator = 1;
		sign = true;
	}

	frac add(frac& other) {
		frac out;
		whole = (sign) ? whole : whole*(-1);//if a negative sign make whole part negative
		other.whole = (other.sign) ? other.whole : other.whole*-1;
		//add whole parts
		out.whole = whole + other.whole;
		//make sure denomenators are = then add numerators
		if (denominator != other.denominator) {
			out.denominator = denominator * other.denominator;
			numerator *= other.denominator;
			other.numerator *= denominator;
		}
		out.numerator = numerator + other.numerator;
		return out;
	}

	frac sub(frac& other) {
		other.sign = !other.sign; //flip sign
		return add(other);
	}

	frac multiply(frac& other) {
		frac out;
		return out;
	} 

	frac divide(frac& other) {
		//flip the fraction then multiply
		int temp = other.numerator;
		other.numerator = other.denominator;
		other.denominator = temp;
		return multiply(other);
	}

	bool is_zero() const {
		if (whole == 0 && numerator == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void simplify() {
		if (numerator >= denominator) { //if numerator > denominator then add one to whole and reduce fraction
			whole += numerator / denominator;
			numerator %= denominator;
		} 
		else { //else numerator < denominator try to find a number both are divisible by and simplify
			for (int i = 0; i < numerator; ++i) {
				if (numerator % i == 0 && denominator % i == 0) { //both are evenly divisible by i
					numerator /= i;
					denominator /= i;
				}
			}
		}
	}
	
};


frac a;
frac total;
std::string temp;//for storing the numbers read, to compile into a part of the fraction


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
			std::cout << a.whole << ' ' << a.numerator << '/' << a.denominator << std::endl;
		} while (false/*!file->eof()*/);
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
		if (*c == '+') {
			total = total.add(a);
		}
		else if (*c == '-') {
			total = total.sub(a);
		}
		else if (*c == '*') {
			total = total.multiply(a);
		}
		else if (*c == '/') {
			total = total.divide(a);
		}
		else {

		}
	}
	else {
		total = total.add(a);
		
	}
	total.simplify();
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
	a.denominator = to_int(temp);
	temp = "";

	if (!total.is_zero()) {
		if (*c == '+') {
			total = total.add(a);
		}
		else if (*c == '-') {
			total = total.sub(a);
		}
		else if (*c == '*') {
			total = total.multiply(a);
		}
		else if (*c == '/') {
			total = total.divide(a);
		}
		else {

		}
	}
	else {
		total = total.add(a);

	}
	total.simplify();
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

