#include"DeskCalc.h"


int Error::no_of_errors;
double Error::error(const string& s) {
	no_of_errors++;
	cerr << "error: " << s << '\n';
	return 1;
}