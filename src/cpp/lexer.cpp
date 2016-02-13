#include "lexer.hpp"
#include <iostream>

lexer::lexer() {
    tokens = std::vector< std::unique_ptr<tokens::token> >();
    patterns = std::vector<lexical_pattern>();
    patterns.emplace_back(lexical_pattern(std::regex("(for|in|if|else|while|fn|return|class)"),tokens::token_type::Keyword));
    patterns.emplace_back(lexical_pattern(std::regex("([a-zA-Z][a-zA-Z0-9]*)"),tokens::token_type::Identifier));
    patterns.emplace_back(lexical_pattern(std::regex("([ \t\n]+)"),tokens::token_type::Whitespace));
    patterns.emplace_back(lexical_pattern(std::regex("([0-9]+(?:\\.[0-9]+)?)"),tokens::token_type::Number));
    patterns.emplace_back(lexical_pattern(std::regex("\\'(.)"),tokens::token_type::Char));
    patterns.emplace_back(lexical_pattern(std::regex("\\\"((?:[^\"]|\\\")*)\\\""),tokens::token_type::String));
    patterns.emplace_back(lexical_pattern(std::regex("([+*]|-|\\/)"),tokens::token_type::ArithOp));
    patterns.emplace_back(lexical_pattern(std::regex("(=)"),tokens::token_type::Assignment));
    patterns.emplace_back(lexical_pattern(std::regex("([<>.|&]|==|<=|>=|!=|->|<<|>>|\\|\\||&&)"),tokens::token_type::CompOp));
    patterns.emplace_back(lexical_pattern(std::regex("([(])"),tokens::token_type::Open_Paren));
    patterns.emplace_back(lexical_pattern(std::regex("([)])"),tokens::token_type::Close_Paren));
    patterns.emplace_back(lexical_pattern(std::regex("([{])"),tokens::token_type::Open_Block));
    patterns.emplace_back(lexical_pattern(std::regex("([}])"),tokens::token_type::Close_Block));
    patterns.emplace_back(lexical_pattern(std::regex("(!)"),tokens::token_type::Bang));
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

bool lexer::matches_pattern(std::string str, lexical_pattern& pattern_matched,std::string& matched_str,int& mlength) {
    for (auto& pattern: patterns) {
	std::smatch matches;
	if(regex_search(str,matches,pattern.re,std::regex_constants::match_continuous)) {
	    matched_str = matches[1];
	    pattern_matched = pattern;
	    mlength = matches[0].length();
	    return true;
	}
    }
    return false;
}

std::unique_ptr<tokens::token> lexer::parse_token(std::string str, tokens::token_type type) {
    if (type == tokens::token_type::Identifier) {
	return std::unique_ptr<tokens::token>(new tokens::identifier(str));
    } else if (type == tokens::token_type::Keyword) {
	return std::unique_ptr<tokens::token>(new tokens::keyword(str));
    } else if (type == tokens::token_type::Number) {
	return std::unique_ptr<tokens::token>(new tokens::number(stod(str)));
    } else if (type == tokens::token_type::String) {
	return std::unique_ptr<tokens::token>(new tokens::string(str));
    } else if (type == tokens::token_type::Char) {
	return std::unique_ptr<tokens::token>(new tokens::char_lit(str[0]));
    } else if (type == tokens::token_type::ArithOp) {
	return std::unique_ptr<tokens::token>(new tokens::arithop(str));
    } else if (type == tokens::token_type::CompOp) {
	return std::unique_ptr<tokens::token>(new tokens::compop(str));
    } else if (type == tokens::token_type::UnaryOp) {
	return std::unique_ptr<tokens::token>(new tokens::unaryop(str));
    } else if (type == tokens::token_type::Open_Paren) {
	return std::unique_ptr<tokens::token>(new tokens::open_paren());
    } else if (type == tokens::token_type::Close_Paren) {
	return std::unique_ptr<tokens::token>(new tokens::close_paren());
    } else if (type == tokens::token_type::Open_Block) {
	return std::unique_ptr<tokens::token>(new tokens::open_block());
    } else if (type == tokens::token_type::Close_Block) {
	return std::unique_ptr<tokens::token>(new tokens::close_block());
    } else if (type == tokens::token_type::Assignment) {
	return std::unique_ptr<tokens::token>(new tokens::assign());
    } else if (type == tokens::token_type::Bang) {
	return std::unique_ptr<tokens::token>(new tokens::bang());
    } else if (type == tokens::token_type::Assignment) {
	return std::unique_ptr<tokens::token>(new tokens::assign());
    }
    return std::unique_ptr<tokens::token>(new tokens::token(tokens::token_type::None));
}

void lexer::next() {
    std::string line;
    
    while (getline(input,line)) {

	while (line != "") {
	    lexical_pattern pattern{};
	    std::string match_str;
	    int mlength;
	    
	    if (matches_pattern(line,pattern,match_str,mlength)) {
		tokens.push_back(parse_token(match_str,pattern.token_t));
		line = line.substr(mlength);
	    }
	}
    }
}

