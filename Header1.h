#include<iostream>
#include<string>
#include<map>
#include<cctype>
#include<sstream>

using namespace std;


Token_stream ts{ cin };

void calculate() {
	for (;;) {
		ts.get();
		if (ts.current().kind == Kind::end)break;
		if (ts.current().kind == Kind::print)continue;
		cout << expr(false) << '\n';
	}
}

int main() {

	switch (argc) {
	case 1:
		break;
	case 2:
		ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		error("too many arguments");
		return 1;
	}

	table["pi"] = 3.1415926535897932385;
	table["e"] = 2.7182818284590452354;

	calculate();
	return no_of_errors;
}

