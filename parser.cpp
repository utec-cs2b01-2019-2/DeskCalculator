#include "DeskCalc.h"

double Parser::prim(bool get) {
	if (get) Lexer::ts.get();

	switch (Lexer::ts.current().kind) {
	case Lexer::Kind::number:
	{
		double v = Lexer::ts.current().number_value;
		Lexer::ts.get();
		return v;
	}
	case Lexer::Kind::name:
	{
		double& v = Table::table[Lexer::ts.current().string_value];
		if (Lexer::ts.get().kind == Lexer::Kind::assign) v = expr(true);
		return v;
	}
	case Lexer::Kind::minus:
		return -prim(true);
	case Lexer::Kind::lp:
	{
		auto e = expr(true);
		if (Lexer::ts.current().kind != Lexer::Kind::rp) return Error::error("')' expected");
		Lexer::ts.get();
		return e;
	}
	default:
		return Error::error("primary expected");
	}
}

double Parser::term(bool get) {
	double left = prim(get);

	for (;;) {
		switch (Lexer::ts.current().kind) {
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
		switch (Lexer::ts.current().kind) {
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

