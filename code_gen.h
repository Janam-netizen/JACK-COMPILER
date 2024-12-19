#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>

#include "basic_block.h"

#include <fstream>

#include <string>

// Variable -> register(essentially coloring )
extern map<int, int> var_desc;

// Register -> variable
extern int *reg_desc;

extern ofstream tgt_code;




void init_codegen(string file_name ,map<int,int>color,int num_vars);

void emit_tgt_instr(basic_block block);

void gen_naive_code(basic_block block);


#endif