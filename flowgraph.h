#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "basic_block.h"


//Encoding of variables to integer numbers
extern map<string, int> get_node;

extern map<int, string> get_var;

// String array of three address code statements
extern string tac_stmts[30];

extern string vars[30];
// number of variables
extern int node ;

// Array of basic blocks/tac instructions
extern basic_block blocks[30];
// Flowgraph represented as adjecency matrix
extern int fg[30][30];
// Number of instructions/basic blocks
extern int ctr;
//
void read_stmts(string stmt);

void encode_vars_to_vertex();

void create_basic_blocks();

void create_flow_graph();

void disp_fg();

void disp_blcoks();

void print_assignment();

