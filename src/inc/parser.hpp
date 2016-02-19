// parser.hpp
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef PARSER_H
#define PARSER_H 1

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "token.hpp"

namespace grammar {
    struct grammar_error : std::exception {
	std::string error;
	grammar_error(std::string error) : error(error) {}
	virtual const char* what() const throw() {
	    return error.c_str();
	};
    };
    
    struct grammar_elem {
	virtual std::string to_string() { return "ELEM"; }
	virtual bool isterminal() const { return false; }

	virtual ~grammar_elem() {}
    };

    struct terminal : grammar_elem {
	std::string name;
	terminal(std::string name) : name(name) {}
	std::string to_string() override { return this->name; }
	virtual bool isterminal() const override { return true; }
    };

    struct nonterminal : grammar_elem {
	std::unique_ptr<tokens::token> match;

	nonterminal(std::unique_ptr<tokens::token>&& match) {
	    this->match = std::move(match);
	}

	virtual ~nonterminal() {
	}
	
	std::string to_string() override {
	    return match->to_string();
	}
    };

    struct nonterminal_type : grammar_elem {
	tokens::token_type type;

	nonterminal_type(tokens::token_type type) : type(type) {}

	std::string to_string() override {
	    return tokens::token::type_string(type);
	}
    };

    struct production {
	terminal* from;
	std::vector<grammar_elem*> to;
	production(terminal* from, std::vector<grammar_elem*> to) : from(from), to(to) {}
    };

    struct language {
	// std::vector<std::unique_ptr<grammar_elem> > elements{};
	std::map<std::string,std::unique_ptr<grammar::grammar_elem> > elements;
	std::vector<production> productions;
	
	language() {
	    elements = std::map<std::string,std::unique_ptr<grammar::grammar_elem> >();
	}

	bool elem_exists(std::string);

	void add_terminal(std::string);

	void add_nonterminal(std::string,tokens::token* match);

	void add_nontypeterminal(std::string,tokens::token_type type);

	production create_production(std::string,std::initializer_list<std::string>);
	production create_production(std::string,std::vector<std::string>);

	std::vector<production> get_productions(std::string key);

	void print_productions() const;
	void print_elements() const;
    };

    struct item {
	production prod;
	int pos;
    };

    struct machine_state {
	std::vector<item> items;
    };
}

/*

  Example grammar:
  E -> T + E | T
  T -> T * E | (E) | ident

  Handles:
  E -> .T + E | .T
  T -> .T * E | .(E) | .ident

  id * id + id
  T * T + T
  T * E + T
  T + E
  E

  production(terminal(E),{terminal(T),nonterminal(+),terminal(E)})
  production(terminal(E),{terminal(T)})
  production(terminal(T),{terminal(T),nonterminal(*),terminal(E)})
  production(terminal(T),{nonterminal((),terminal(E),nonterminal())})
  production(terminal(T),{nonterminal(ident)})

 */

struct parser {
    std::vector<grammar::machine_state> states;

    std::shared_ptr<grammar::language> lang;
    

    parser(std::shared_ptr<grammar::language>);
};

#endif // PARSER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
