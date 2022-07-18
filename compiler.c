/************************************************************************
University of Leeds
School of Computing
COMP2932- Compiler Design and Construction
The Compiler Module

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name:
Student ID:
Email:
Date Work Commenced:
*************************************************************************/

#include "compiler.h"

#include <dirent.h>
#include<unistd.h>

/*char* TokenTypeString (TokenType t)
{
    switch (t)
    {
        case RESWORD: return "RESWORD";
        case ID: return "ID";
        case INT: return "INT";
        case SYMBOL: return "SYMBOL";
        case STRING: return "STRING";
        case EOFile: return "EOFile";
        case ERR: return "ERR";
        default: return "Not a recognised token type";
    }

}


void PrintToken (Token t)
{
    printf ("<%s, %i, %s, %s>\n", t.fl, t.ln , t.lx, TokenTypeString (t.tp));
}

void display_method(struct method_table *t) {


    printf("%c  %s  %s\n",  t->m_type, t->r_type, t->name);


}


void display_methods(struct ll_method *l) {
    if(l->ctr>0) {

        struct method_table *v = l->head;

        while (v != 0) {

            PrintToken(v->tK);
            printf("CLASS:%s\n",v->class_name);

            v = v->next;


        }
    }
}

void display_class_list(struct ll_class *l){

    if(l->ctr>0) {


        struct class_table *v = l->head;

        while (v != 0) {

            PrintToken(v->tk);

            v = v->next;

        }

    }


}
void display_var(struct id_node *v) {

    printf("%s     %s\n", v->name, v->type);


}


void display_ids(struct ll_id *l){


    if(l->ctr>0) {

        struct id_node *v = l->head;

        while (v != 0) {

            PrintToken(v->tK);

            v = v->next;

        }

    }

}

void display_class(struct class_table *t) {


    printf("CLASS NAME: %s\n",t->name);

    printf("METHODS:\n");


    display_methods(t->method_list);

    printf("VARS:\n");

    display_ids(t->id_list);










}

void display_ids_in_method(struct method_table *t){

    printf("METHOD_NAME:%s\n",t->name);

    printf("VARS:\n");


    display_ids(t->id_list);


}*/

struct program_scope *p;


int st;
int InitCompiler ()


{

    p=create_program_scope();


    st=0;





    return 1;
}

ParserInfo check_uclass(){

    ParserInfo pi;


    struct class_table *v=p->uclass->head;

    pi.er=none;



    while(v!=0){

        if(search_class_list(p->class_list,v->name)==-1){

            pi.er=undecIdentifier;

            pi.tk=v->tk;

            return pi;


        }

        v=v->next;
    }

    return pi;

}

ParserInfo check_umethods(){



    struct method_table *v=p->umethods->head;

    ParserInfo pi;


    pi.er=none;


    while(v!=0){

        struct class_table *c;

        c= get_class_by_name(p->class_list,v->class_name);

        /*if(c==0){


            pi.er=none;

            pi.tk=v->class.;

            return pi;
        }*/

        if(search_method_list(c->method_list,v->name)==-1){

            pi.er=undecIdentifier;

            pi.tk=v->tK;

            return pi;
        }

        v=v->next;
    }

    return pi;

}

ParserInfo check_uid(){


    ParserInfo pi;


    struct id_node *v=p->uid->head;

    pi.er=none;





    while(v!=0){

        struct id_node *v1= get_node_by_name_in_class(get_class_by_name(p->class_list,v->class_name),v->name);

        if(v1!=0){

            if(v->access!=v1->access){

                pi.er=undecIdentifier;

                pi.tk=v->tK;

                return pi;

            }

        }

        v=v->next;
    }

    return pi;
}



ParserInfo compile (char* dir_name)
{   ParserInfo pi;

    char * fi=" ";

    char *file_name=" ";

    pi.er = none;

    char bin_files[8][128]={"Math.jack","Memory.jack","Output.jack","String.jack","Screen.jack","Array.jack","Keyboard.jack","Sys.jack"};

    for(int i=0;i<8;i++){


        struct class_table *ct = create_class_table(" ");

        add_class_list(p->class_list, ct);

        ct->program = p;

        InitParser(bin_files[i]);

        pi = Parse();

        if (pi.er!=none){

            StopParser();

            return pi;
        }

        StopParser();



    }



    if(strstr(dir_name,".jack")){

        struct class_table *ct= create_class_table(" ");

        add_class_list(p->class_list,ct);

        ct->program=p;

        InitParser(dir_name);

        pi =Parse();

        StopParser();






    }

    else {

        chdir(dir_name);

        DIR *d;
        struct dirent *dir;


        d = opendir(".");

        while ((dir = readdir(d)) != NULL) {

                if (strstr(dir->d_name, ".jack")) {
                    struct class_table *ct = create_class_table(" ");

                    add_class_list(p->class_list, ct);

                    ct->program = p;

                    InitParser(dir->d_name);

                    pi = Parse(ct);


                    if(pi.er!=none){

                        StopParser();

                        chdir("..");


                        return pi;



                    }
                    StopParser();




                }


            }


        }





        chdir("..");


        /*if (pi.er == none) {

            pi = check_uclass();

            if (pi.er != none) {

                return pi;

            }

            pi = check_umethods();


            if (pi.er != none) {

                return pi;

            }

            pi = check_uid();


            return pi;


        }*/










	// write your code below

	/*printf("---IDS--\n");

    display_ids(p->uid);

	printf("---UMETHODS---\n");

    display_methods(p->umethods);

    printf("--UCLASSES--\n");

    display_class_list(p->uclass);

    printf("--CLASSES--\n");

    display_class_list(p->class_list);*/


   ParserInfo pi_one;

    pi_one = check_uclass();

    if(pi_one.er!=none){

        return pi_one;
    }






    /*ParserInfo pi_two;

    pi_two = check_uid();*/


    ParserInfo pi_three;

    pi_three = check_umethods();

	/*ParserInfo l[3]={pi_one,pi_three};


	for(int i=0;i<2;i++){


	    if(l[i].er!=none){

	        return l[i];
	    }
	}*/

	if(pi_three.er!=none){


	    return pi_three;
	}




	return pi;
}

int StopCompiler ()
{
    /*free_method_list(p->umethods);

    free_class_list(p->class_list);

    free_node_list(p->uid);

    free(p);*/


	return 1;
}

/*char* ErrorString (SyntaxErrors e)
{

    switch (e)
    {
        case none: return "no errors";
        case lexerErr: return "lexer error";
        case classExpected: return "keyword class expected";
        case idExpected: return "identifier expected";
        case openBraceExpected:	return "{ expected";
        case closeBraceExpected: return "} expected";
        case memberDeclarErr: return "class member declaration must begin with static, field, constructor , function , or method";
        case classVarErr: return "class variables must begin with field or static";
        case illegalType: return "a type must be int, char, boolean, or identifier";
        case semicolonExpected: return "; expected";
        case subroutineDeclarErr: return "subrouting declaration must begin with constructor, function, or method";
        case openParenExpected: return "( expected";
        case closeParenExpected: return ") expected";
        case closeBracketExpected: return "] expected";
        case equalExpected: return "= expected";
        case syntaxError: return "syntax error";
            // semantic errors
        case undecIdentifier: return "undeclared identifier";
        case redecIdentifier: return "redeclaration of identifier";
        default: return "not a valid error code";
    }
}

void ShowInfo (ParserInfo pn)
{
    if (pn.er == none)
        printf ("none\n");
    else
        printf ("error type: %s, line: %i,token: %s, \n" , ErrorString(pn.er),  pn.tk.ln , pn.tk.lx  );
}

int main ()
{
	InitCompiler ();

	ParserInfo pi = compile ("Average");

    ShowInfo(pi);

	StopCompiler ();


	return 1;
}*/
#ifndef TEST_COMPILER
#endif
