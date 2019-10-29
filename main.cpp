#include<iostream>
#include<sstream>

#include"DeskCalc.h"

Lexer::Token_stream ts{ &cin };

void Driver::calculate() {
	for (;;) {
		ts.get();
		if (ts.current().kind == Lexer::Kind::end)break;
		if (ts.current().kind == Lexer::Kind::print)continue;
		cout << Parser::expr(false) << '\n';
	}
};

int main(int argc, char* argv[]) {
	istream* input;
	switch (argc) {
	case 1:
		input = &cin;
		break;
	case 2:
		ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		Error::error("too many arguments");
		return 1;
	}

	Table::table["pi"] = 3.1415926535897932385;
	Table::table["e"] = 2.7182818284590452354;

	Driver::calculate();
	return Error::no_of_errors;
}