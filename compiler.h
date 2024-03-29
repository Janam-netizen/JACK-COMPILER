#ifndef COMPILER_H
#define COMPILER_H

#define TEST_COMPILER    // uncomment to run the compiler autograder

#include "parser.h"
#include "symbols.h"
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int InitCompiler ();
ParserInfo compile (char* dir_name);
int StopCompiler();

#endif
