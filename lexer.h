#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<vector>

#include"token.h"

#define NULL_STR ""

class Lexer
{
public:
	Lexer(std::string code);
	~Lexer();

	std::vector<Token*>* GetTokens();

	void SkinWhiteSpace();
	char ReadChar();
	void NextChar();
	bool HasNext();
	void ReadToken();
private:
	bool IsDigit(char c);
	bool IsAlpha(char c);

	void DoLexer();
	void AddToken(Token* token);

	std::vector<Token*>* tokens;
	std::string code;
	int index = 0;
};

#endif
