//
// Created by Janam Zaveri on 25/11/2022.
//

#include "tac_converter.h"

#include <iostream>
extern "C"
{
#include "lexer.h"
}

using namespace std;
#define MAX 4
int num_tokens = 0;

void start_parser(char *file_name)
{

    InitLexer(file_name);
}

char *gen_new_temp()
{

    num_tokens += 1;

    char *num;

    char *temp = (char *)malloc(sizeof(char) * MAX);

    if (asprintf(&num, "%d", num_tokens) == -1)
    {
        perror("asprintf");
    }
    else
    {
        strcat(strcpy(temp, "t_"), num);
        return temp;
    }

    return 0;
}

char *parse_exp()
{

    char *temp_one;

    char *temp_two;

    temp_one = parse_rexp();

    Token op;

check:

    op = PeekNextToken();

    if (strcmp(op.lx, ")") == 0)
    {

        op = GetNextToken();

        return temp_one;
    }

    if (strcmp(op.lx, "|") && strcmp(op.lx, "&"))
    {

        return temp_one;
    }

    temp_two = parse_rexp();

    char *temp = gen_new_temp();

    printf("%s = %s %s %s\n", temp, temp_one, op.lx, temp_two);

    temp_one = temp;

    goto check;
}

char *parse_rexp()
{

    char *temp_one = parse_aexp();

    Token op;

check:
    op = PeekNextToken();

    if (strcmp(op.lx, ">") && strcmp(op.lx, "<") && strcmp(op.lx, "="))
    {

        return temp_one;
    }

    op = GetNextToken();

    char *temp_two = parse_aexp();

    char *temp = gen_new_temp();

    printf("%s = %s %s %s\n", temp, temp_one, op.lx, temp_two);

    temp_one = temp;
    goto check;
}

char *parse_aexp()
{

    char *temp_one = parse_term();

    Token op;

check:
    op = PeekNextToken();

    if (strcmp(op.lx, "+") && strcmp(op.lx, "-"))
    {

        printf("%s\n", op.lx);

        printf("REACHED HERE\n");

        return temp_one;
    }

    op = GetNextToken();

    char *temp_two = parse_term();

    char *temp = gen_new_temp();

    printf("%s = %s %s %s\n", temp, temp_one, op.lx, temp_two);

    temp_one = temp;

    goto check;
}

char *parse_term()
{

    char *temp_one;

    Token op;

    temp_one = parse_factor();

check:

    op = PeekNextToken();

    if (strcmp(op.lx, "*") && strcmp(op.lx, "/"))
    {

        return temp_one;
    }
    op = GetNextToken();

    char *temp_two = parse_factor();

    char *temp = gen_new_temp();

    printf("%s = %s %s %s\n", temp, temp_one, op.lx, temp_two);

    temp_one = temp;

    goto check;
}

char *parse_factor()
{

    Token tk = PeekNextToken();

    if (strcmp(tk.lx, "-") == 0)
    {

        tk = GetNextToken();
    }

    char *tmp = gen_new_temp();

    printf("%s=%s\n", tmp, parse_operand());

    return tmp;
}

char *parse_operand()
{

    Token tk = GetNextToken();

    char *temp = gen_new_temp();

    if (tk.tp == INT || tk.tp == ID)
    {
        char *id = (char *)malloc(sizeof(tk.lx));

        strcpy(id, tk.lx);

        return id;
    }

    else if (strcmp(tk.lx, "(") == 0)
    {

        char *temp = parse_exp();

        return temp;
    }

    return 0;
}

int main()
{

    start_parser("exp_4.jack");

    parse_exp();
}