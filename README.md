# JACK-COMPILER

A genral purpose compiler for JACK proghramming language designied for HACK architecture inspired from NandToTetris course. It consists of the following modules

1) Lexer: Responsible for capturing tokens from the source file.

2) Parser: Checks if the program syntactically makes sense and adheres to the grammar of JACK programming language . Otherwise will raise a syntax error .

3) Symbol table: Ensures that the source file semantically makes sense. Otherwise will raise semantic error .

4) Code generation: Generates virtual machine code for stack based virtual machine .  
