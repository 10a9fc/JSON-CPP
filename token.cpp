#include "token.h"

Token::Token(TokenType type, std::string data) :type(type), data(data) {}

Token::~Token() {}

TokenType Token::GetType()
{
	return type;
}

std::string Token::GetData()
{
	return data.c_str();
}
