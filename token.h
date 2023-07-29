#ifndef  TOKEN_H
#define TOKEN_H

#include <iostream>
#include <unordered_map>

enum class TokenType
{
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	LBRACK,
	RBRACK,

	NUMBER,
	IDENTIFIER,
	STRING,
	TRUE,
	FALSE,

	COLON,
	COMMA,

	TEOF
};

class Token
{
public:
	Token(TokenType type, std::string data);
	~Token();

	TokenType GetType();
	std::string GetData();

	static std::unordered_map<std::string, Token> tokenMap;
private:
	TokenType type;
	std::string data;
};

#endif // ! TOKEN_H
