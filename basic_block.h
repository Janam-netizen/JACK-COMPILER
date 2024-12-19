//
// Created by Janam Zaveri on 31/01/2023.
//

#ifndef FYP_SRC_BASIC_BLOCK_H
#define FYP_SRC_BASIC_BLOCK_H

#include <vector>

#include <string>

#include <set>
#include <iostream>

using namespace std;

class basic_block
{

public:
    set<int> live_in;

    set<int> live_out;

    int use_one;

    int use_two;

    char op;

    int def;

    // default constructor

    basic_block(){

    };

    basic_block(int def, int use_one, int use_two, char op)
    {

        this->op = op;

        if (this->def != -1)
        {
            this->def = def;
        }

        this->use_one = use_one;

        if (use_one != -1)
        {

            this->live_in.insert(use_one);
        }

        if (use_two != -1)
        {

            this->live_in.insert(use_two);
        }

        this->use_two = use_two;
    };

    void disp_info()
    {

        cout << "live_in:" << endl;

        for (auto &x : this->live_in)
        {

            cout << x << " ";
        }
        cout << endl;

        cout << "live_out:" << endl;

        for (auto &x : this->live_out)
        {

            cout << x << " ";
        }

        cout << endl;
    }
};

#endif // FYP_SRC_BASIC_BLOCK_H
