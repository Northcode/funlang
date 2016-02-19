#include <iostream>
#include <cassert>

#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"

using namespace std;

int main() {
    // string str;

    // getline(cin,str);

    // lexer l{str};

    // l.next();

    // for (auto& tok : l.tokens) {
    // 	if (tok->type == tokens::token_type::Identifier) {
    // 	    cout << "ident: " << ((tokens::identifier*)tok.get())->name << endl;
    // 	} else if (tok->type == tokens::token_type::Keyword) {
    // 	    cout << "keyword: " << ((tokens::keyword*)tok.get())->word << endl;
    // 	} else if (tok->type == tokens::token_type::Number) {
    // 	    cout << "number: " << ((tokens::number*)tok.get())->value << endl;
    // 	} else if (tok->type == tokens::token_type::String) {
    // 	    cout << "string: " << ((tokens::string*)tok.get())->value << endl;
    // 	} else if (tok->type == tokens::token_type::Char) {
    // 	    cout << "char: " << ((tokens::char_lit*)tok.get())->value << endl;
    // 	} else if (tok->type == tokens::token_type::Assignment) {
    // 	    cout << "assignment" << endl;
    // 	} else if (tok->type == tokens::token_type::ArithOp) {
    // 	    cout << "arithop: " << ((tokens::arithop*)tok.get())->symbol << endl;
    // 	} else if (tok->type == tokens::token_type::CompOp) {
    // 	    cout << "compop: " << ((tokens::compop*)tok.get())->symbol << endl;
    // 	} else if (tok->type == tokens::token_type::UnaryOp) {
    // 	    cout << "unaryop: " << ((tokens::unaryop*)tok.get())->symbol << endl;
    // 	} else if (tok->type == tokens::token_type::Open_Paren) {
    // 	    cout << "open paren" << endl;
    // 	} else if (tok->type == tokens::token_type::Close_Paren) {
    // 	    cout << "close paren" << endl;
    // 	} else if (tok->type == tokens::token_type::Open_Block) {
    // 	    cout << "open block" << endl;
    // 	} else if (tok->type == tokens::token_type::Close_Block) {
    // 	    cout << "close block" << endl;
    // 	} else if (tok->type == tokens::token_type::Bang) {
    // 	    cout << "bang" << endl;
    // 	}
    // }
    // cout << endl;
    
    shared_ptr<grammar::language> lang1 = make_shared<grammar::language>();
    lang1->add_terminal("E");
    lang1->add_terminal("T");
    lang1->add_nontypeterminal("ident",tokens::token_type::Identifier);
    lang1->add_nonterminal("+",new tokens::arithop("+"));
    lang1->add_nonterminal("(",new tokens::open_paren());
    lang1->add_nonterminal(")",new tokens::close_paren());

    string str = "";
    vector<string> prodbuilder{};
    while (str != "$") {
		lang1->print_elements();
		string name;
		cout << "Production name: ";
		cin >> name;
		if (name == "$")
			break;
		getline(cin,str);
		cout << "Production parts:";
		getline(cin,str);
		istringstream iss{str};
		prodbuilder=vector<string>(istream_iterator<string>{iss},istream_iterator<string>{});
		lang1->create_production(name,prodbuilder);
		prodbuilder.clear();
    }
    
    lang1->create_production("E",{"E","+","T"});
    lang1->create_production("E",{"T"});
    lang1->create_production("T",{"T","+","E"});

    lang1->print_productions();

    return 0;
}
