#include "lexer.hpp"
#include <iostream>

lexer::lexer() {
    tokens = std::vector< std::unique_ptr<tokens::token> >();
    patterns = std::map<std::string,lexical_pattern>();
    patterns.emplace("identifier",lexical_pattern(std::regex("[a-zA-Z][a-zA-Z0-9]*"),0,tokens::token_type::Identifier));
    patterns.emplace("whitespace",lexical_pattern(std::regex("[ \t\n]+"),0,tokens::token_type::Whitespace));
}

lexer::lexer(std::string& str) : lexer() {
    input = std::stringstream(str);
}

std::string lexer::lookahead(int length) {
    std::stringstream ss{};
    std::streampos pos{input.tellg()};
    for (int i = 0; i < length && !input.eof(); i++) {
	ss << (char)input.get();
    }
    input.seekg(pos);
    return ss.str();
}

bool lexer::matches_pattern(std::string str, lexical_pattern& pattern_matched) {
    for (auto& pattern_pair : patterns) {
	if(regex_match(str,pattern_pair.second.re)) {
	    std::cout << "matched: " << pattern_pair.first << std::endl;
	    if (pattern_pair.second.lookahead > 0) {
		std::string lookahead_str = lookahead(pattern_pair.second.lookahead);
		lexical_pattern matched{};
		if (matches_pattern(lookahead_str,matched)) {
		    pattern_matched = matched;
		    return true;
		}
	    }
	    pattern_matched = pattern_pair.second;
	    return true;
	}
    }
    return false;
}

std::unique_ptr<tokens::token> lexer::parse_token(std::string str, tokens::token_type type) {
    if (type == tokens::token_type::Identifier) {
	return std::unique_ptr<tokens::token>(new tokens::identifier(str));
    }
    return std::unique_ptr<tokens::token>(new tokens::token(tokens::token_type::None));
}

void lexer::next() {
    std::stringstream current{};

    while (!input.eof()) {
	char c = (char)input.get();
	current << c;
	lexical_pattern pattern{};
	if (matches_pattern(current.str(),pattern) && !matches_pattern(current.str() + (char)input.peek(),pattern)) {
	    tokens.push_back(parse_token(current.str(),pattern.token_t));
	    current.str(std::string());
	}
    }
}

