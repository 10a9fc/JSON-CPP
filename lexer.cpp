#include "lexer.h"

Lexer::Lexer(std::string code) :code(code), tokens(new std::vector<Token*>() ) { DoLexer(); }

Lexer::~Lexer()
{
	for (auto it : *tokens)
	{
		delete it;
	}
	delete tokens;
	tokens = nullptr;
}

char Lexer::ReadChar()
{
	return code[index];
}

void Lexer::NextChar()
{
	++index;
}

bool Lexer::HasNext()
{
	return index < code.length();
}

std::vector<Token*>* Lexer::GetTokens()
{
	return tokens;
}

void Lexer::AddToken(Token* token)
{
	tokens->push_back(token);
}

void Lexer::SkinWhiteSpace()
{
	while (ReadChar() == '\n' || ReadChar() == '\t' || ReadChar() == ' ')
	{
		NextChar();
	}
}

void Lexer::ReadToken()
{
	if (IsDigit(ReadChar()))
	{
		int start = index;
		int len = 0;
		while (HasNext() && (IsDigit(ReadChar()) || ReadChar() == '.' || ReadChar() == 'f' || ReadChar() == '-'))
		{
			++len;
			NextChar();
		}

		std::string num = code.substr(start, len);

		AddToken(new Token(TokenType::NUMBER, num));
	}
	else if (IsAlpha(ReadChar()))
	{
		int start = index;
		int len = 0;
		while (HasNext() && (IsAlpha(ReadChar()) || IsDigit(ReadChar())))
		{
			++len;
			NextChar();
		}

		std::string str = code.substr(start, len);

		if (str == "true")
		{
			AddToken(new Token(TokenType::TRUE, str));
		}
		else if (str == "false")
		{
			AddToken(new Token(TokenType::FALSE, str));
		}
		else
		{
			AddToken(new Token(TokenType::IDENTIFIER, str));
		}
	}
	else
	{

	}
}

bool Lexer::IsDigit(char c)
{
	return '0' <= c && c <= '9';
}

bool Lexer::IsAlpha(char c)
{
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

void Lexer::DoLexer()
{
	while (HasNext())
	{
		SkinWhiteSpace();

		if (ReadChar() == '"')
		{
			NextChar();
			int start = index;
			int len = 0;

			while (ReadChar() != '"')
			{
				++len;
				NextChar();
			}
			NextChar();

			std::string str = code.substr(start, len);
			str.push_back('\0');

			AddToken(new Token(TokenType::STRING, str));

			continue;
		}

		switch (ReadChar())
		{
		case '(':
			AddToken(new Token(TokenType::LPAREN, NULL_STR)); NextChar();
			continue;
		case ')':
			AddToken(new Token(TokenType::RPAREN, NULL_STR)); NextChar();
			continue;
		case '[':
			AddToken(new Token(TokenType::LBRACK, NULL_STR)); NextChar();
			continue;
		case ']':
			AddToken(new Token(TokenType::RBRACK, NULL_STR)); NextChar();
			continue;
		case '{':
			AddToken(new Token(TokenType::LBRACE, NULL_STR)); NextChar();
			continue;
		case '}':
			AddToken(new Token(TokenType::RBRACE, NULL_STR)); NextChar();
			continue;
		case ':':
			AddToken(new Token(TokenType::COLON, NULL_STR)); NextChar();
			continue;
		case ',':
			AddToken(new Token(TokenType::COMMA, NULL_STR)); NextChar();
			continue;
		}

		ReadToken();
	}

	AddToken(new Token(TokenType::TEOF, ""));
}
