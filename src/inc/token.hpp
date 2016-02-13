#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <regex>
#include <map>

namespace tokens {

    enum class token_type {
		Identifier,
		Keyword,
		Whitespace,
		Number,
		Open_Paren,
		Close_Paren,
		Open_Block,
		Close_Block,
		Assignment,
		Operator,
		String,
		Char,
		Bang,
		None    
    };
    
    struct token {
	token_type type;
	
	token(token_type type) : type(type) {}
    };

    struct identifier : public token {
	std::string name;
	identifier(std::string name) : token(token_type::Identifier),name(name) {}
    };

    struct keyword : public token {
	std::string word;
	keyword(std::string word) : token(token_type::Keyword),word(word) {}
    };

    struct whitespace : public token {
	whitespace() : token(token_type::Whitespace) {}
    };
    
    struct number : public token {
	double value;
	number(double value) : token(token_type::Number),value(value) {}
    };

    struct string : public token {
	std::string value;
	string(std::string value) : token(token_type::String),value(value) {}
    };

    struct char_lit : public token {
	char value;
	char_lit(char value) : token(token_type::Char),value(value) {}
    };
	
    struct oper : public token {
	std::string symbol;
	oper(std::string symbol) : token(token_type::Operator),symbol(symbol) {}
    };

    struct assign : public token {
	assign() : token(token_type::Assignment) {}
    };
    
    struct open_paren : public token {
	open_paren() : token(token_type::Open_Paren) {}
    };
    
    struct close_paren : public token {
	close_paren() : token(token_type::Close_Paren) {}
    };
    
    struct open_block : public token {
	open_block() : token(token_type::Open_Block) {}
    };
    
    struct close_block : public token {
	close_block() : token(token_type::Close_Block) {}
    };
    
    struct bang : public token {
	bang() : token(token_type::Bang) {}
    };
}

#endif
