//
// Created by Janam Zaveri on 01/02/2023.
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "basic_block.h"
using namespace std;

// vector<basic_block> instructions;

map<string, int> get_node;
map<int, string> get_var;
string tac_stmts[30];

string vars[30];

int node = 0;
basic_block blocks[30];

int fg[30][30];

int ctr = 0;

void read_stmts(string file_name)
{

    ifstream ipstream(file_name);

    string line;

    while (getline(ipstream, line))
    {

        tac_stmts[ctr++] = line;
    }
}

bool check_if_operator(char var)
{

    string operators = "+=-/*><";

    if (operators.find(var) != std::string::npos)
    {

        return true;
    }

    return false;
}



char extract_operator(string tac_stmt){


    for(int i=0;i<=tac_stmt.length();i++){



        if (check_if_operator(tac_stmt[i]) && tac_stmt[i]!='='){


            return tac_stmt[i];


        }
    }


    return 'M';






}
// Assigns each variable an node from the three address statement in our interference graph and defines a basic b
string *extract_vars(string tac_stmt)
{

    string *vars = new string[3];

    int idx = 0;

    for (int i = 0; i < 3; i++)
    {

        vars[i] = "";
    }

    string foo = "";

    for (int i = 0; i <= tac_stmt.length(); i++)
    {

        if (i == tac_stmt.length())
        {

            vars[idx++] = foo;

            continue;
        }
        // vars[idx] = "";

        if (tac_stmt[i] == ' ' || check_if_operator(tac_stmt[i]))
        {



            if (foo == "goto")
            {

                break;
            }

            if (foo != "" && foo != "if")
            {

                vars[idx++] = foo;
            }

            foo = "";
            continue;
        }

        else
        {
            foo += tac_stmt[i];
        }
    }

    return vars;
}

// Treats each instruction as a basic block. Identifies use and def for each instruction
/*void create_basic_blocks()
{

    for (int i = 0; i < ctr; i++)
    {

        blocks[i] = new basic_block(tac_stmts[ctr]);
    }
}*/

//

//  Chekcs if it is a jmp stmt by locating the word 'goto'
bool check_goto_stmt(string stmt)
{

    if (stmt.find("goto") != std::string::npos)
    {
        return true;
    }

    return false;
}

int extract_tgt(string stmt)
{

    if (check_goto_stmt(stmt))
    {

        // Extract the last word from the string as it will be a number

        int i = stmt.length() - 1; // last character
        while (i != 0 && !isspace(stmt[i]))
        {
            --i;
        }
        string lastword = stmt.substr(i + 1); // +1 to skip leading space

        return stoi(lastword);
    }

    return -1;
}

void create_flow_graph()
{

    for (int i = 0; i < ctr; i++)
    {

        // check if goto stmt

        if (check_goto_stmt(tac_stmts[i]))
        {

            // Extract target statement's line number.

            int tgt_stmt = extract_tgt(tac_stmts[i]);

            fg[i][tgt_stmt-1] = 1;
        }

        if (i < ctr - 1)
        {

            fg[i][i + 1] = 1;
        }
    }
}

// Populate the hashmap such that every varaible is assigned some number and create basic blocks
void encode_vars_to_vertex()
{

    for (int i = 0; i < ctr; i++)
    {

        string *vars = extract_vars(tac_stmts[i]);

        for (int idx = 0; idx < 3; idx++)
        {

            // Check for blank string or number

            if (vars[idx] != "" && !((int)vars[idx][0] >= 48 && (int)vars[idx][0] <= 57))
            {

                if (get_node.find(vars[idx]) == get_node.end())
                {

                    get_node[vars[idx]] = node++;

                    get_var[node - 1] = vars[idx];
                }
            }

            else
            {

                get_node[vars[idx]] = -1;
                get_var[-1] = "";
            }
        }
    }
}

void create_basic_blocks()
{
    for (int i = 0; i < ctr; i++)
    {

        string *vars = extract_vars(tac_stmts[i]);

        if (check_goto_stmt(tac_stmts[i]))
        {

            blocks[i] = basic_block(-1, get_node[vars[0]], get_node[vars[1]],'N');
        }
 
        else
        {

            char op=extract_operator(tac_stmts[i]);

            blocks[i] = basic_block(get_node[vars[0]], get_node[vars[1]], get_node[vars[2]],op);


        }
    }
}

void print_assignment()
{
    map<string, int>::iterator it;
    for (it = get_node.begin(); it != get_node.end(); it++)
    {
        cout << it->first << ':' << it->second << endl;
    }
}

void disp_blcoks()
{

    for (int i = 0; i < ctr; i++)
    {
        blocks[i].disp_info();
    }
}

// print flowgraph adjecency matrix
void disp_fg()
{

    for (int i = 0; i < ctr; i++)

    {

        for (int j = 0; j < ctr; j++)
        {

            cout << fg[i][j];
        }

        cout << endl;
    }
}
/*int main()
{

    read_stms("tac_1.tac");

    encode_vars_to_vertex();

    print_assignment();

    create_basic_blocks();

    create_flow_graph();

    disp_fg();

    disp_blcoks();
}*/