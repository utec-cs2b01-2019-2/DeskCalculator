#include "DeskCalc.h"

double Parser::prim(bool get) {
	if (get) ts.get();

	switch (ts.current().kind) {
	case Lexer::Kind::number:
	{
		double v = ts.current().number_value;
		ts.get();
		return v;
	}
	case Lexer::Kind::name:
	{
		double& v = Table::table[ts.current().string_value];
		if (ts.get().kind == Lexer::Kind::assign) v = expr(true);
		return v;
	}
	case Lexer::Kind::minus:
		return -prim(true);
	case Lexer::Kind::lp:
	{
		auto e = expr(true);
		if (ts.current().kind != Lexer::Kind::rp) return Error::error("')' expected");
		ts.get();
		return e;
	}
	default:
		return Error::error("primary expected");
	}
}

double Parser::term(bool get) {
	double left = prim(get);

	for (;;) {
		switch (ts.current().kind) {
		case Lexer::Kind::mul:
			left *= prim(true);
			break;
		case Lexer::Kind::div:
			if (auto d = prim(true)) {
				left /= d;
				break;
			}
			return Error::error("divide by 0");
		default:
			return left;
		}
	}

}

double Parser::expr(bool get) {
	double left = term(get);
	for (;;) {
		switch (ts.current().kind) {
		case Lexer::Kind::plus:
			left += term(true);
			break;
		case Lexer::Kind::minus:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}

