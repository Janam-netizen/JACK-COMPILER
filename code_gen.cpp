#include <iostream>

#include "flowgraph.h"
#include "basic_block.h"
#include <fstream>
#include "code_gen.h"
#include <string>


// Variable -> register(essentially coloring )
map<int, int> var_desc;

// Register -> variable
int *reg_desc;

ofstream tgt_code;

void init_codegen(string file_name,map<int,int>color,int num_vars)
{

    tgt_code.open(file_name, ios::out);
    
    reg_desc=new int [num_vars];

    var_desc=color;

}

void emit_st_instr(string src, string dst)
{

    string instr = "st " + src + " " + dst + "\n";

    cout << instr;

    tgt_code << instr;
}

void emit_ld_instr(string dst, string src)
{

    // Case 1: If variable to be loaded is a spill variable

    string instr = "ld " + dst + " " + src + "\n";

    cout << instr;
}

void emit_op_instr(string dst, string op_one, string op_two, char op)
{

    string instr;

    // check if op_one is loaded onto a register

    // check if op_two is loaded onto a register

    if (op == '+')
    {

        instr = "add ";
    }
    else if (op == '-')
    {

        instr = "sub ";
    }

    instr += dst + " " + op_one + " " + op_two;

    cout << instr << endl;

    tgt_code << instr;
}

// NOTE: Can be extended for a smarter code generator :)

int get_reg(int var)
{

    // If var is not a spill variable return the register by the graph coloring allocator

    if (var_desc[var] > -1)
    {

        return var_desc[var];
    }

    return -1;
}

void gen_naive_code(basic_block block)
{

    if (block.op != 'M' && block.op != 'N')
    {

        emit_ld_instr("R0", get_var[block.use_one]);

        emit_ld_instr("R1", get_var[block.use_two]);

        emit_op_instr("R0", "R0", "R1", block.op);

        emit_st_instr("R0", get_var[block.def]);
    }
}

void emit_tgt_instr(basic_block block)
{


    if (block.use_two == -1)
    {
      if (block.use_one == -1)
        {

            emit_ld_instr("R"+to_string(var_desc[block.def]),"#");

            reg_desc[var_desc[block.def]]=block.def;


        }

        else
        {

            cout<<"Illegal instruction"<<endl;

        }
    }

    int reg_one = var_desc[block.use_one];

    int reg_two = var_desc[block.use_two];

    int reg_def = var_desc[block.def];

    // Not residing in a register

    // load the variable to reg_one

    if (reg_one == -1)
    {

        emit_st_instr("R0", get_var[reg_desc[0]]);

        reg_one = 0;
    }

    if (reg_two == -1)
    {

        emit_st_instr("R1", get_var[reg_desc[1]]);

        reg_two = 1;
    }

    if (reg_desc[reg_one] != block.use_one)
    {

        emit_ld_instr("R" + to_string(reg_one), get_var[block.use_one]);

        reg_desc[reg_one] = block.use_one;
    }

    if (reg_desc[reg_one] != block.use_two)
    {
        emit_ld_instr("R" + to_string(reg_two), get_var[block.use_two]);

        reg_desc[reg_two] = block.use_two;
    }

    if (reg_def == -1)
    {

        if (var_desc[block.use_one] == -1)
        {

            emit_op_instr("R" + to_string(reg_one), "R" + to_string(reg_one), "R" + to_string(reg_two), block.op);

            emit_st_instr("R" + to_string(reg_one), get_var[block.def]);
        }
        else if (var_desc[block.use_two] == -1)
        {

            emit_op_instr("R" + to_string(reg_two), "R" + to_string(reg_one), "R" + to_string(reg_two), block.op);

            emit_st_instr("R" + to_string(reg_two), get_var[block.def]);
        }

        emit_st_instr("R" + to_string(reg_one), get_var[reg_desc[reg_one]]);

        emit_op_instr("R" + to_string(reg_one), "R" + to_string(reg_one), "R" + to_string(reg_two), block.op);

        emit_st_instr("R" + to_string(reg_one), get_var[block.def]);

        return;
    }

    emit_op_instr("R" + to_string(reg_def), "R" + to_string(reg_one), "R" + to_string(reg_two),block.op);

    reg_desc[reg_def] = block.def;

    return;
}
