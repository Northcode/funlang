#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <memory>

#include "token.hpp"

struct lexical_pattern {
    std::regex re;
    int lookahead;
    int internal_lookahead;

    tokens::token_type token_t;
    
    lexical_pattern() {};
    lexical_pattern(std::regex re, int lookahead, int internal_lookahead,tokens::token_type type) : re(re),lookahead(lookahead),internal_lookahead(internal_lookahead),token_t(type) {}
};

struct lexer {

    std::stringstream input;
    std::vector< std::unique_ptr<tokens::token> > tokens;

    std::vector<lexical_pattern> patterns;

    lexer();
    lexer(std::string&);

    bool matches_pattern(std::string,lexical_pattern&,std::string&,int&);

    void next();

    std::string lookahead(int);

    std::unique_ptr<tokens::token> parse_token(std::string,tokens::token_type);
};

#endif
