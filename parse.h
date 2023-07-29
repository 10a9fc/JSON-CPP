#ifndef PARSE_H
#define PARSE_H

#include"lexer.h"
#include"jobject.h"
#include<string>

class Parser
{
public:
	Parser(Lexer& lexer);
	~Parser();

	JObject* GetAST();
	
private:
	JObject* Parse();
	JObject* ParseExpr();
	JObject* ParseBool();
	JObject* ParseNumber();
	JObject* ParseString();
	JObject* ParseArray();
	JObject* ParseMap();

	Token* GetToken();
	Token* EatToken();
	Token* InspectToken(TokenType type, std::string err);
	bool NotEof();

	std::vector<Token*>* tokens;
	JObject* ast = nullptr;

	int index = 0;
};

#endif
