#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

#include "token.hpp"

struct lexical_pattern {
    std::regex re;
    int lookahead;
    lexical_pattern() {};
    lexical_pattern(std::regex re, int lookahead) : re(re),lookahead(lookahead) {}
};

struct lexer {

    std::stringstream input;
    std::vector<tokens::token> tokens;

    std::map<std::string,lexical_pattern> patterns;

    lexer();
    lexer(std::string&);

    bool matches_pattern(std::string,lexical_pattern&);

    void next();

    std::string lookahead(int);
};

#endif
