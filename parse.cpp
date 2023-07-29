#include "parse.h"

Parser::Parser(Lexer& lexer) :tokens(lexer.GetTokens()) { ast = Parse(); tokens = nullptr; }

Parser::~Parser()
{
	if (ast != nullptr)
	{
		delete ast;
		ast = nullptr;
	}
}

JObject* Parser::GetAST()
{
	JObject* ret = ast;
	ast = nullptr;
	return ret;
}

JObject* Parser::Parse()
{
	return ParseExpr();
}

JObject* Parser::ParseExpr()
{
	switch (GetToken()->GetType())
	{
	case TokenType::NUMBER:
		return ParseNumber();
	case TokenType::STRING:
		return ParseString();
	case TokenType::IDENTIFIER:
		return ParseString();
	case TokenType::LBRACK:
		return ParseArray();
	case TokenType::LBRACE:
		return ParseMap();
	case TokenType::TRUE:
	case TokenType::FALSE:
		return ParseBool();
	}
}

JObject* Parser::ParseBool()
{
	if (EatToken()->GetType() == TokenType::TRUE)
	{
		return new JBool(true);
	}
	else
	{
		return new JBool(false);
	}
}

JObject* Parser::ParseMap()
{
	EatToken();

	JMap* ret = new JMap();

	while (NotEof() && GetToken()->GetType() != TokenType::RBRACE)
	{
		JString* name = (JString*)ParseString();
		InspectToken(TokenType::COLON, "È±ÉÙ':'");
		ret->GetValue()[name->GetValue()] = ParseExpr();
		delete name;

		if (GetToken()->GetType() == TokenType::COMMA)
		{
			EatToken();
		}
	}
	InspectToken(TokenType::RBRACE, "È±ÉÙ'}'");

	return ret;
}

JObject* Parser::ParseNumber()
{
	JNumber* ret;
	std::string num = EatToken()->GetData();
	if (num.back() == 'f')
	{
		num.pop_back();
		ret = new JNumber(std::stof(num));
	}
	else if (num.find('.') != -1)
	{
		ret = new JNumber(std::stod(num));
	}
	else
	{
		ret = new JNumber(std::stoi(num));
	}
	return ret;
}

JObject* Parser::ParseString()
{
	return new JString(EatToken()->GetData());
}

JObject* Parser::ParseArray()
{
	EatToken();

	JArray* ret = new JArray();

	while (NotEof() && GetToken()->GetType() != TokenType::RBRACK)
	{
		ret->GetValue().push_back(ParseExpr());
		if (GetToken()->GetType() == TokenType::COMMA)
		{
			EatToken();
		}
	}
	InspectToken(TokenType::RBRACK, "È±ÉÙ']'");

	return ret;
}

Token* Parser::GetToken()
{
	return (*tokens)[index];
}

Token* Parser::EatToken()
{
	return (*tokens)[index++];
}

Token* Parser::InspectToken(TokenType type, std::string err)
{
	if (GetToken()->GetType() != type)
	{
		throw std::exception(err.c_str());
	}
	return EatToken();
}

bool Parser::NotEof()
{
	return GetToken()->GetType() != TokenType::TEOF;
}
