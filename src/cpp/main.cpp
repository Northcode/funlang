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
	} else if (tok->type == tokens::token_type::Assignment) {
	    cout << "assignment" << endl;
	} else if (tok->type == tokens::token_type::ArithOp) {
	    cout << "arithop: " << ((tokens::arithop*)tok.get())->symbol << endl;
	} else if (tok->type == tokens::token_type::CompOp) {
	    cout << "compop: " << ((tokens::compop*)tok.get())->symbol << endl;
	} else if (tok->type == tokens::token_type::UnaryOp) {
	    cout << "unaryop: " << ((tokens::unaryop*)tok.get())->symbol << endl;
	} else if (tok->type == tokens::token_type::Open_Paren) {
	    cout << "open paren" << endl;
	} else if (tok->type == tokens::token_type::Close_Paren) {
	    cout << "close paren" << endl;
	} else if (tok->type == tokens::token_type::Open_Block) {
	    cout << "open block" << endl;
	} else if (tok->type == tokens::token_type::Close_Block) {
	    cout << "close block" << endl;
	} else if (tok->type == tokens::token_type::Bang) {
	    cout << "bang" << endl;
	}
    }
    cout << endl;
    return 0;
}
