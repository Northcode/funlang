#include <iostream>
#include <cassert>

#include "token.hpp"
#include "lexer.hpp"

using namespace std;

int main() {
    string str;

    getline(cin,str);

    lexer l{str};

    l.next();

    for (auto& tok : l.tokens) {
	if (tok->type == tokens::token_type::Identifier) {
	    cout << "ident: " << ((tokens::identifier*)tok.get())->name << endl;
	} else if (tok->type == tokens::token_type::Keyword) {
	    cout << "keyword: " << ((tokens::keyword*)tok.get())->word << endl;
	} else if (tok->type == tokens::token_type::Number) {
	    cout << "number: " << ((tokens::number*)tok.get())->value << endl;
	} else if (tok->type == tokens::token_type::String) {
	    cout << "string: " << ((tokens::string*)tok.get())->value << endl;
	} else if (tok->type == tokens::token_type::Char) {
	    cout << "char: " << ((tokens::char_lit*)tok.get())->value << endl;
	}
    }
    cout << endl;
    return 0;
}
