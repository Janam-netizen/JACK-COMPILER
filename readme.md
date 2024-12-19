# Register allocation library for JACK compiler



## Running instructions

To create the compiler executable,make sure you are in top level of the project directory  run the following commands

<ol>

<li><code>cmake .. </code></li>
<li><code>make</code> </li>

In line 198 of liveness.cpp , enter the input program file path.
and then enter

<li> <code>./reg_alloc_cpp</code> </li>
You should then see the target code 

being produced in file named tgt1.asm.