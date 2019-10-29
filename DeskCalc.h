#include<iostream>
#include<string>
#include<map>



using namespace std;


namespace Parser {
	double expr(bool);
	double term(bool);
	double prim(bool);
}

namespace Lexer{
	enum class Kind :char {
		name, number, end, plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
	};

	struct Token {
		Kind kind;
		string string_value;
		double number_value;
	};

	class Token_stream {
	public:
		//Token_stream() {};
		Token_stream(istream& s) : ip{ &s }, owns(false), ct{ Kind::end }{
		};
		Token_stream(istream* p) : ip{ p }, owns(true), ct{ Kind::end }{
		};
		~Token_stream(){
			close();
		};
		Token get();
		Token& current();

		void set_input(istream& s) { close(); ip = &s; owns = false; }
		void set_input(istream* p) { close(); ip = p; owns = true; }

	private:
		void close() { if (owns) delete ip; }
		
		istream* ip;
		bool owns;
		Token ct{ Kind::end };			
	};
	
}
extern Lexer::Token_stream ts;

namespace Table {
	extern map<string, double> table;
}

namespace Error {
	extern int no_of_errors;
	double error(const string& s);
}

namespace Driver {
	void calculate();
}
