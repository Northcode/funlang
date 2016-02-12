#include <iostream>
#include <cassert>

#include "token.hpp"
#include "lexer.hpp"

using namespace std;

int main() {
    string str;

    cin >> str;
    
    lexer l{str};

    l.next();

    for (auto& tok : l.tokens) {
	if (tok->type == tokens::token_type::Identifier) {
	    cout << ((tokens::identifier*)tok.get())->name << endl;
	}
    }
    cout << endl;
    return 0;
}
