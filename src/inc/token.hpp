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
		ArithOp,
		CompOp,
		UnaryOp,
		String,
		Char,
		Bang,
		None    
    };
    
    struct token {
	token_type type;
	
	token(token_type type) : type(type) {}

	virtual std::string to_string() { return "TOKEN("+std::to_string((int)type)+")"; }

	static std::string type_string(token_type type) {
	    switch (type) {
	    case token_type::Identifier:
		return "identifier";
	    case token_type::Keyword:
		return "keyword";
	    case token_type::Whitespace:
		return "whitespace";
	    case token_type::Number:
		return "number";
	    default:
		return "token";
	    }
	}
    };

    struct identifier : public token {
	std::string name;
	identifier(std::string name) : token(token_type::Identifier),name(name) {}

	std::string to_string() { return name; }
    };

    struct keyword : public token {
	std::string word;
	keyword(std::string word) : token(token_type::Keyword),word(word) {}

	std::string to_string() { return word; }
    };

    struct whitespace : public token {
	whitespace() : token(token_type::Whitespace) {}
    };
    
    struct number : public token {
	double value;
	number(double value) : token(token_type::Number),value(value) {}
	std::string to_string() { return std::to_string(value); }
    };

    struct string : public token {
	std::string value;
	string(std::string value) : token(token_type::String),value(value) {}
	std::string to_string() { return value; }
    };

    struct char_lit : public token {
	char value;
	char_lit(char value) : token(token_type::Char),value(value) {}
	std::string to_string() { return std::to_string(value); }
    };
	
    struct arithop : public token {
	std::string symbol;
	arithop(std::string symbol) : token(token_type::ArithOp),symbol(symbol) {}
	std::string to_string() { return symbol; }
    };

    struct compop : public token {
	std::string symbol;
	compop(std::string symbol) : token(token_type::CompOp),symbol(symbol) {}
	std::string to_string() { return symbol; }
    };

    struct unaryop : public token {
	std::string symbol;
	unaryop(std::string symbol) : token(token_type::ArithOp),symbol(symbol) {}
	std::string to_string() { return symbol; }
    };
	
    struct assign : public token {
	assign() : token(token_type::Assignment) {}
	std::string to_string() { return "="; }
    };
    
    struct open_paren : public token {
	open_paren() : token(token_type::Open_Paren) {}
	std::string to_string() { return "("; }
    };
    
    struct close_paren : public token {
	close_paren() : token(token_type::Close_Paren) {}
	std::string to_string() { return ")"; }
    };
    
    struct open_block : public token {
	open_block() : token(token_type::Open_Block) {}
	std::string to_string() { return "{"; }
    };
    
    struct close_block : public token {
	close_block() : token(token_type::Close_Block) {}
	std::string to_string() { return "}"; }
    };
    
    struct bang : public token {
	bang() : token(token_type::Bang) {}
	std::string to_string() { return "!"; }
    };
}

#endif
