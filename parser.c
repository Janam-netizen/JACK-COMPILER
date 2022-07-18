#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lexer.h"
#include "parser.h"

// you can declare prototypes of parser functions below

Token t;

int parse_exp(ParserInfo *pi);

int parse_lexp(ParserInfo *pi);

int parse_aexp(ParserInfo *pi);

int parse_term(ParserInfo *pi);

int parse_factor(ParserInfo *pi);

int parse_operand(ParserInfo *pi);

int parse_return_stmt(ParserInfo *pi);

int parse_sub_routine_call(ParserInfo *pi);

int parse_do_stmt(ParserInfo *pi);

int parse_while_stmt(ParserInfo *pi);

int parse_if_stmt(ParserInfo *pi);

int parse_let_stmt(ParserInfo *pi);

int parse_var_dec_stmt(ParserInfo *pi);

int parse_body(ParserInfo *pi);

int parse_stmt(ParserInfo *pi);

int parse_ids(ParserInfo *pi);

int parse_class(ParserInfo *pi);

int parse_member_dec(ParserInfo *pi);

int parse_class_var_dec(ParserInfo *pi);

int parse_lparam(ParserInfo *pi);

int parse_subroutine_dec(ParserInfo *pi);

int parse_type(ParserInfo *pi);

int parse_class(ParserInfo *pi)
{

	t = GetNextToken();

	if (strcmp(t.lx, "class") == 0 && t.tp == RESWORD)
	{

		t = GetNextToken();
	}

	else
	{

		pi->er = classExpected;

		pi->tk = t;

		return -1;
	}

	if (t.tp == ID)
	{

		t = GetNextToken();
	}
	else
	{

		pi->er = idExpected;

		pi->tk = t;

		return -1;
	}

	if (t.tp == SYMBOL && strcmp(t.lx, "{") == 0)
	{

		t = PeekNextToken();

		if (strcmp(t.lx, "}") == 0 && t.tp == SYMBOL)
		{

			t=GetNextToken();
			pi->tk = t;

			return 1;
		}

		if (parse_member_dec(pi) == -1)
		{

			return -1;
		}

		t = GetNextToken();

		if (strcmp(t.lx, "}") != 0 || t.tp != SYMBOL)
		{

			pi->tk = t;

			return -1;
		}
	}


	else
	{

		pi->er = openBraceExpected;

		pi->tk = t;

		return -1;
	}

	pi->tk = t;

	return 1;
}
int parse_member_dec(ParserInfo *pi)
{
check:
	t = PeekNextToken();

	if (t.tp == RESWORD)
	{

		if (strcmp(t.lx, "static") == 0 || strcmp(t.lx, "field") == 0)
		{ t=GetNextToken();

			if (parse_class_var_dec(pi) == -1)
			{

				return -1;
			}

			goto check;
		}

		else if (strcmp(t.lx, "constructor") == 0 || strcmp(t.lx, "function") == 0 || strcmp(t.lx, "method") == 0)
		{t=GetNextToken();

			if (parse_subroutine_dec(pi) == -1)
			{

				return -1;
			}

			goto check;
		}

		
	}



	return 1;
}

int parse_class_var_dec(ParserInfo *pi)
{

	if (parse_type(pi) == -1)
	{

		return -1;
	}

	

	if (parse_ids(pi) == -1)
	{

		return -1;
	}
	t=GetNextToken();

	if(strcmp(t.lx,";")==0 && t.tp==SYMBOL){


		return 1;
	}
	return -1;
}

int parse_lparam(ParserInfo *pi)
{

check:
	if (parse_type(pi) == -1)

	{
		pi->tk = t;

		pi->er = illegalType;

		return -1;
	}

	t = GetNextToken();
	if (t.tp != ID)
	{

		pi->er = idExpected;

		pi->tk = t;

		return -1;
	}

	t = PeekNextToken();

	if (strcmp(t.lx, ",") == 0)
	{

		GetNextToken();

		goto check;
	}

	pi->tk = t;
	return 1;
}

int parse_subroutine_dec(ParserInfo *pi)
{

	if (parse_type(pi) == 1 || (strcmp(t.lx, "void")==0 && t.tp == RESWORD))
	{

		t = GetNextToken();
	}

	else
	{

		pi->er = syntaxError;

		pi->tk = t;

		return -1;
	}
	if(t.tp==ID){

		t=GetNextToken();






	}

	else{


		pi->er=idExpected;

		pi->tk=t;

		return -1;
	}
	if (strcmp(t.lx, "(") == 0 && t.tp == SYMBOL)
	{

		t=PeekNextToken();

		if (strcmp(t.lx, ")") == 0 && t.tp == SYMBOL)
		{
			t=GetNextToken();

			goto END;

			

			
		}

		if (parse_lparam(pi) == -1)
		{

			pi->tk = t;

			return -1;
		}


		t=GetNextToken();

		if (strcmp(t.lx, ")") == 0 && t.tp == SYMBOL)
		{

			goto END;
			
		}

		else
		{

			pi->er = closeParenExpected;

			pi->tk = t;

			return -1;
		}
	}
	else{

			pi->er = openParenExpected;

			pi->tk = t;

			return -1;


	}

END:
	return parse_body(pi);
}

int parse_type(ParserInfo *pi)
{

	t = GetNextToken();

	printf("%s\n", t.lx);

	if ((strcmp(t.lx, "int") == 0 || strcmp(t.lx, "char") == 0 || strcmp(t.lx, "boolean") == 0) && t.tp == RESWORD)
	{

		return 1;
	}

	else if (t.tp == ID)
	{

		return 1;
	}
	else
	{

		pi->er = illegalType;

		pi->tk = t;
	}

	return -1;
}

int parse_return_stmt(ParserInfo *pi)

{

	t = PeekNextToken();

	if (strcmp(t.lx, ";") == 0 && t.tp == SYMBOL)
	{

		t = GetNextToken();

		return 1;
	}

	if (parse_exp(pi) == -1)
	{

		return -1;
	}
	else
	{

		t = GetNextToken();
	}

	if (t.tp == SYMBOL && strcmp(t.lx, ";") == 0)
	{

		pi->er = none;

		pi->tk = t;
	}

	else
	{

		pi->er = semicolonExpected;

		pi->tk = t;

		return -1;
	}

	return 1;
}

int parse_sub_routine_call(ParserInfo *pi)
{

	t = GetNextToken();

	if (t.tp == ID)
	{

		t = PeekNextToken();

		if (strcmp(t.lx, ".") == 0 && t.tp == SYMBOL)
		{

			t = GetNextToken();
			t = GetNextToken();

			if (t.tp != ID)
			{
				pi->er = idExpected;

				pi->tk = t;

				return -1;
			}
		}
	}
	else
	{

		pi->er = idExpected;

		pi->tk = t;

		return -1;
	}
	t = GetNextToken();

	if (strcmp(t.lx, "(") == 0 && t.tp == SYMBOL)
	{

		t = PeekNextToken();

		if (strcmp(t.lx, ")") == 0 && t.tp == SYMBOL)
		{

			t = GetNextToken();

			printf("reached here\n");

			return 1;
		}
	}

	else
	{
		pi->er = openParenExpected;
		pi->tk = t;

		return -1;
	}

	if (parse_lexp(pi) == -1)
	{

		return -1;
	}

	t = GetNextToken();

	if (strcmp(t.lx, ")") == 0 && t.tp == SYMBOL)
	{

		pi->tk = t;

		pi->er = none;

		return 1;
	}

	else
	{

		pi->er = closeParenExpected;

		pi->tk = t;
	}

	return -1;
}

int parse_do_stmt(ParserInfo *pi)
{

	if (parse_sub_routine_call(pi) == -1)
	{

		return -1;
	}

	t = GetNextToken();

	if (strcmp(t.lx, ";") == 0 && t.tp == SYMBOL)
	{

		pi->er = none;

		pi->tk = t;

		return 1;
	}

	pi->er = semicolonExpected;

	pi->tk = t;
	return -1;
}

int parse_let_stmt(ParserInfo *pi)
{

	t = GetNextToken();

	if (t.tp == ID)
	{

		t = GetNextToken();
	}

	else
	{

		return -1;
	}

	if (t.tp == SYMBOL && strcmp(t.lx, "[") == 0)
	{

		if (parse_exp(pi) == -1)
		{

			return -1;
		}

		t = GetNextToken();

		if (t.tp == SYMBOL && strcmp(t.lx, "]") == 0)
		{
			t = GetNextToken();
		}

		else
		{

			pi->tk = t;
			pi->er = closeBracketExpected;
			return -1;
		}
	}

	if (strcmp(t.lx, "=") == 0 && t.tp == SYMBOL)
	{

		printf("Gog\n");

		if (parse_exp(pi) != 1)
		{

			return -1;
		}

		t = GetNextToken();

		pi->tk = t;

		if (strcmp(t.lx, ";") != 0 || t.tp != SYMBOL)
		{

			pi->er = semicolonExpected;

			return -1;
		}
	}

	else
	{

		pi->er = equalExpected;

		pi->tk = t;

		return -1;
	}

	pi->er = none;

	return 1;
}

int parse_while_stmt(ParserInfo *pi)
{

	t = GetNextToken();

	if (strcmp(t.lx, "(") == 0 && t.tp == SYMBOL)
	{

		if (parse_exp(pi) != 1)
		{

			return -1;
		}

		t = GetNextToken();

		if (strcmp(t.lx, ")") != 0 || t.tp != SYMBOL)
		{

			pi->er = closeParenExpected;

			pi->tk = t;

			return -1;
		}

		return parse_body(pi);
	}

	else
	{

		pi->er = openParenExpected;

		pi->tk = t;
	}

	return -1;
}

int parse_body(ParserInfo *pi)
{

	t = GetNextToken();

	if (strcmp(t.lx, "{") == 0 && t.tp == SYMBOL)

	{

		if (PeekNextToken().tp == SYMBOL && strcmp(PeekNextToken().lx, "}") == 0)
		{
			t=GetNextToken();
			
			return 1;
		}

		if (parse_stmt(pi) == -1)
		{

			return -1;
		}

		t = GetNextToken();
		pi->tk = t;

		if (strcmp(t.lx, "}") != 0)

		{

			pi->er = closeBraceExpected;

			return -1;
		}

		pi->er = none;

		return 1;
	}
	else
	{

		pi->er = openBraceExpected;

		pi->tk = t;
	}

	return -1;
}

int parse_else_stmt(ParserInfo *pi)
{

	return parse_body(pi);
}

int parse_if_stmt(ParserInfo *pi)
{

	if (parse_while_stmt(pi) == -1)
	{

		return -1;
	}

	t = PeekNextToken();

	if (strcmp(t.lx, "else") == 0 && t.tp == RESWORD)
	{

		t = GetNextToken();
		if (parse_else_stmt(pi) == -1)
		{

			return -1;
		}
	}

	return 1;
}

int parse_ids(ParserInfo *pi)
{

check:
	t = GetNextToken();

	if (t.tp != ID)
	{

		pi->er = idExpected;

		pi->tk = t;

		return -1;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && strcmp(t.lx, ",") == 0)
	{

		t = GetNextToken();

		goto check;
	}

	pi->er = none;

	pi->tk = t;

	return 1;
}

int parse_var_dec_stmt(ParserInfo *pi)
{

	if (parse_type(pi) == -1)
	{

		pi->er = illegalType;
		pi->tk = t;
		return -1;
	}

	if (parse_ids(pi) == -1)
	{

		return -1;
	}
	t=GetNextToken();

	if(strcmp(t.lx,";")==0 && t.tp==SYMBOL ){

		pi->tk=t;

		return 1;
	}

	else{

		pi->er=semicolonExpected;

		pi->tk=t;


	}

	return 1;
}

int parse_stmt(ParserInfo *pi)
{

check:
	t = PeekNextToken();

	if (strcmp(t.lx, "let") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();

		if (parse_let_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}

	else if (strcmp(t.lx, "var") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();

		if (parse_var_dec_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}
	else if (strcmp(t.lx, "if") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();
		if (parse_if_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}

	else if (strcmp(t.lx, "while") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();
		if (parse_while_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}

	else if (strcmp(t.lx, "return") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();
		if (parse_return_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}

	else if (strcmp(t.lx, "do") == 0 && t.tp == RESWORD)
	{
		t = GetNextToken();

		if (parse_do_stmt(pi) == -1)
		{

			return -1;
		}

		goto check;
	}

	pi->tk = t;

	pi->er = none;

	return 1;
}
int parse_statements(ParserInfo *pi)
{
	int i;

	while (1)
	{

		i = parse_stmt(pi);

		if (i == -1)
		{

			return -1;
		}

		else if (i == 0)
		{

			return 1;
		}
	}
}
/*char *TokenTypeString(TokenType t)
{
	switch (t)
	{
	case RESWORD:
		return "RESWORD";
	case ID:
		return "ID";
	case INT:
		return "INT";
	case SYMBOL:
		return "SYMBOL";
	case STRING:
		return "STRING";
	case EOFile:
		return "EOFile";
	case ERR:
		return "ERR";
	default:
		return "Not a recognised token type";
	}
}
void PrintToken(Token t)
{
	printf("<%s, %i, %s, %s>\n", t.fl, t.ln, t.lx, TokenTypeString(t.tp));
}*/

int InitParser(char *file_name)
{

	printf("Initialising lexer\n");
	InitLexer(file_name);

	return 0;
}

int parse_operand(ParserInfo *pi)
{

	t = GetNextToken();

	pi->er = none;
	pi->tk = t;

	printf("%s\n", t.lx);

	if (t.tp == INT)

	{

		return 1;
	}

	else if (t.tp == ID)
	{

		t = PeekNextToken();

		if (strcmp(t.lx, ".") == 0 && t.tp == SYMBOL)
		{

			t = GetNextToken();

			t = GetNextToken();

			if (t.tp != ID)
			{

				pi->er = idExpected;
				pi->tk = t;

				return -1;
			}
		}

		t = PeekNextToken();

		if (t.tp == SYMBOL && strcmp(t.lx, "(") == 0)
		{
			t = GetNextToken();
			t = PeekNextToken();

			if (strcmp(t.lx, ")") == 0 && t.tp == SYMBOL)
			{

				t = GetNextToken();

				return 1;
			}

			int c = parse_lexp(pi);

			if (c == -1)
			{

				return -1;
			}

			t = GetNextToken();

			if (strcmp(t.lx, ")") == 0)
			{

				return 1;
			}

			else
			{

				pi->er = closeParenExpected;

				pi->tk = t;
			}

			return -1;
		}
		else if (t.tp == SYMBOL && strcmp(t.lx, "[") == 0)
		{

			t = GetNextToken();

			int p = parse_exp(pi);

			t = GetNextToken();
			if (p == 1 && strcmp(t.lx, "]") == 0)
			{

				return 1;
			}

			else if (p == 1)
			{
				pi->er = closeBracketExpected;

				pi->tk = t;
			}

			return -1;
		}
	}

	else if (t.tp == STRING)
	{

		return 1;
	}

	else if (t.tp == SYMBOL && strcmp(t.lx, "(") == 0)
	{
		printf("parsing exp\n");

		int c = parse_exp(pi);

		t = GetNextToken();

		if (c == 1 && strcmp(t.lx, ")") == 0)
		{

			printf("finnished parsing\n");

			return 1;
		}

		else if (c == 1)
		{

			pi->er = closeParenExpected;

			pi->tk = t;
		}

		return -1;
	}

	else if (t.tp == RESWORD && (strcmp(t.lx, "true") == 0 || strcmp(t.lx, "false") == 0 || strcmp(t.lx, "null") == 0 || strcmp(t.lx, "this") == 0))
	{
		return 1;
	}

	else
	{
		pi->er = syntaxError;

		pi->tk = t;

		return -1;
	}

	return 1;
}

int parse_factor(ParserInfo *pi)
{

	t = PeekNextToken();

	if ((strcmp(t.lx, "-") == 0 || strcmp(t.lx, "~") == 0) && t.tp == SYMBOL)
	{

		t = GetNextToken();
	}

	return parse_operand(pi);
}

int parse_term(ParserInfo *pi)

{
	int x;
check:

	x = parse_factor(pi);

	if (x != 1)
	{

		return x;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && (strcmp(t.lx, "*") == 0 || strcmp(t.lx, "/") == 0))
	{

		t = GetNextToken();

		goto check;
	}

	pi->er = none;

	pi->tk = t;

	return 1;
}

int parse_aexp(ParserInfo *pi)
{
	int x;

check:

	x = parse_term(pi);

	if (x != 1)
	{

		return x;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && (strcmp(t.lx, "+") == 0 || strcmp(t.lx, "-") == 0))
	{
		t = GetNextToken();

		goto check;
	}

	pi->tk = t;

	return 1;
}

int parse_rexp(ParserInfo *pi)
{
	int x;
check:
	x = parse_aexp(pi);

	if (x != 1)
	{

		return x;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && (strcmp(t.lx, ">") == 0 || strcmp(t.lx, "<") == 0 || strcmp(t.lx, "=") == 0))
	{
		t = GetNextToken();

		goto check;
	}

	pi->tk = t;
	return 1;
}

int parse_exp(ParserInfo *pi)
{
	int m, r;
check_one:

	r = parse_rexp(pi);

	if (r != 1)
	{

		return -1;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && (strcmp(t.lx, "&") == 0 || strcmp(t.lx, "|") == 0) && r == 1)
	{
		t = GetNextToken();

		goto check_one;
	}

	pi->tk = t;

	return 1;
}

int parse_lexp(ParserInfo *pi)
{
	int m, r;
check:

	r = parse_exp(pi);

	if (r == -1)
	{

		return r;
	}

	t = PeekNextToken();

	if (t.tp == SYMBOL && (strcmp(t.lx, ",") == 0))
	{
		t = GetNextToken();

		goto check;
	}

	pi->tk = t;
	return 1;
}

ParserInfo Parse()

{

	ParserInfo pi;

	// implement the function





	pi.er = none;


	parse_class(&pi);

	pi.tk=t;
	return pi;
}

int StopParser()

{
	StopLexer();
	return 1;
}

/*char *ErrorString(SyntaxErrors e)
{

	switch (e)
	{
	case none:
		return "no errors";
	case lexerErr:
		return "lexer error";
	case classExpected:
		return "keyword class expected";
	case idExpected:
		return "identifier expected";
	case openBraceExpected:
		return "{ expected";
	case closeBraceExpected:
		return "} expected";
	case memberDeclarErr:
		return "class member declaration must begin with static, field, constructor , function , or method";
	case classVarErr:
		return "class variables must begin with field or static";
	case illegalType:
		return "a type must be int, char, boolean, or identifier";
	case semicolonExpected:
		return "; expected";
	case subroutineDeclarErr:
		return "subrouting declaration must begin with constructor, function, or method";
	case openParenExpected:
		return "( expected";
	case closeParenExpected:
		return ") expected";
	case closeBracketExpected:
		return "] expected";
	case equalExpected:
		return "= expected";
	case syntaxError:
		return "syntax error";
	default:
		return "not a valid error code";
	}
}

void ShowInfo(ParserInfo pn)
{
	if (pn.er == none)
		printf("none\n");
	else
		printf("error type: %s, line: %i,token: %s \n", ErrorString(pn.er), pn.tk.ln, pn.tk.lx);
}*/

#ifndef TEST_PARSER
int main()
{
	InitParser("List.jack");

	ParserInfo pi;

	printf("%d\n",parse_class(&pi));

}
#endif
