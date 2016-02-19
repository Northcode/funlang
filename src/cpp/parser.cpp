#include "parser.hpp"

#include <iostream>
#include <exception>

using namespace std;

bool grammar::language::elem_exists(string key) {
    auto itr = elements.find(key);
    return itr != elements.end();
}

void grammar::language::add_terminal(string name) {
    if (elem_exists(name)) {
	throw grammar::grammar_error("An element '" + name + "' already exists");
    }
    unique_ptr<grammar_elem> term = unique_ptr<terminal>(new grammar::terminal(name));
    elements.emplace(name,move(term));
}

void grammar::language::add_nonterminal(std::string name,tokens::token* match) {
    unique_ptr<tokens::token> tok = unique_ptr<tokens::token>(match);
    unique_ptr<grammar_elem> nonterm =
	unique_ptr<nonterminal>(new grammar::nonterminal(move(tok)));
    if(elem_exists(name)) {
	throw grammar::grammar_error("An element '" + name + "' already exists");
    }
    elements.emplace(name,move(nonterm));
}

void grammar::language::add_nontypeterminal(string name, tokens::token_type type) {
    if(elem_exists(name)) {
	throw grammar::grammar_error("An element '" + name + "' already exists");
    }
    unique_ptr<grammar_elem> nontterm = unique_ptr<nonterminal_type>(new grammar::nonterminal_type(type));
    elements.emplace(name,move(nontterm));
}

grammar::production grammar::language::create_production(std::string terminal,std::initializer_list<std::string> items) {
    auto it = elements.find(terminal);
    if (it == elements.end()) {
	throw std::range_error("no element named '" + terminal + "' found");
    } else if (!it->second->isterminal()) {
	throw grammar::grammar_error("element '" + terminal + "' is not a terminal");
    }

    grammar::production production{(grammar::terminal*)it->second.get(),std::vector<grammar::grammar_elem*>()};

    for (auto str : items) {
	auto itr = elements.find(str);
	if (itr == elements.end()) {
	    throw std::range_error("no element '" + str + "' in language");
	}
	production.to.push_back(itr->second.get());
    }

    productions.push_back(production);

    return production;
}

grammar::production grammar::language::create_production(std::string terminal,std::vector<std::string> items) {
    auto it = elements.find(terminal);
    if (it == elements.end()) {
	throw std::range_error("no element named '" + terminal + "' found");
    } else if (!it->second->isterminal()) {
	throw grammar::grammar_error("element '" + terminal + "' is not a terminal");
    }

    grammar::production production{(grammar::terminal*)it->second.get(),std::vector<grammar::grammar_elem*>()};

    for (auto str : items) {
	auto itr = elements.find(str);
	if (itr == elements.end()) {
	    throw std::range_error("no element '" + str + "' in language");
	}
	production.to.push_back(itr->second.get());
    }

    productions.push_back(production);

    return production;
}


std::vector<grammar::production> grammar::language::get_productions(std::string key) {
    auto it = elements.find(key);
    if (it == elements.end()) {
	throw std::range_error("no element named '" + key + "' found");
    } else if (!it->second->isterminal()) {
	throw grammar::grammar_error("element '" + key + "' is not a terminal");
    }

    std::vector<grammar::production> selection{};
    
    copy_if(productions.begin(),productions.end(), selection.begin(), [key,it](grammar::production e) { return e.from == ((grammar::terminal*)it->second.get()); });
    return selection;
}

parser::parser(std::shared_ptr<grammar::language> lang) : lang(lang) {
	states = std::vector<grammar::machine_state>();
}

void grammar::language::print_productions() const {
    cout << "Productions:" << endl;
    for (auto& prod : productions) {
	cout << prod.from->name << " -> ";
	for (auto& elem : prod.to) {
	    cout << elem->to_string() << " ";
	}
	cout << endl;
    }
}

void grammar::language::print_elements() const {
    cout << "Elements:" << endl;
    for (auto& elem : elements) {
	cout << elem.first << ",";
    }
    cout << endl;
}
