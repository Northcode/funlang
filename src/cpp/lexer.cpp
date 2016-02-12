#include "lexer.hpp"
#include <iostream>

lexer::lexer() {
    tokens = std::vector<tokens::token>();
    patterns = std::map<std::string,lexical_pattern>();
    patterns.emplace("identifier",lexical_pattern(std::regex("[a-zA-Z][a-zA-Z0-9]*"),0));
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
	}
    }
}

void lexer::next() {
    std::stringstream current{};

    while (!input.eof()) {
	char c = (char)input.get();
	current << c;
	for (auto& pattern_pair : patterns) {
	    if (regex_match(current.str(),pattern_pair.second.re)) {
		std::cout << "matched: " << pattern_pair.first << std::endl;
		if (pattern_pair.second.lookahead > 0) {
		    //preform lookahead
		    std::streampos lookahead_pos = input.tellg();
		    std::stringstream lookahead_stream{current.str()};
		    
		}
	    }
	}
    }
}

