#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "lexer.h"
// define your own types and function prototypes for the symbol table(s) module below



 struct id_node
{
    char name[128];

    struct id_node *next;

    char type[128];

    struct class_table * ct;

    char class_name[128];

    Token tK;

    char access;

    int idx;


};

 struct ll_id
{

     int a_ctr;

     int l_ctr;

     int f_ctr;



     int ctr;

     struct id_node *head;

    struct id_node *tail;

};


/*typedef struct{

    ll id_list;

    struct method_table * method;

    struct stmt_table * next;







}stmt_table;

typedef struct{

    stmt_table *head;

    stmt_table *tail;



}ll_stmt;*/

 struct method_table
{

    char name[128];

    //return type
    char r_type[128];

    //function,method or constructor

    char m_type;

    char class_name[128];


    struct ll_id *id_list;

     struct class_table *class;

     Token tK;

     int idx;



    struct method_table *next;

};

 struct ll_method
{int ctr;
    struct method_table *head;

    struct method_table *tail;

};

 struct class_table
{

    char name [128];

    Token tk;

    struct class_table* next;

    struct ll_id* id_list;

    struct ll_method* method_list;

    int idx;

    struct program_scope * program;

};

 struct ll_class{


     struct class_table*head;

     struct class_table*tail;

     int ctr;
 };

 struct program_scope{
     //linked list to store all classes
     struct  ll_class *class_list;
     //linked list to store undeclared methods
     struct ll_method* umethods;
     //linked list to store  undeclared identifiers
     struct ll_id* uid;

     //linked list to store undeclared classes

     struct ll_class* uclass;

 };



void add_id_list(struct ll_id *,struct  id_node *);

void add_method_list(struct ll_method* l,struct method_table*t);

int search_id_method(struct method_table *t ,char name[128]);

int search_id_class(struct class_table *t,char name[128]);

int add_id_class(struct class_table *t,struct id_node*n);

int add_id_method(struct method_table *t,struct id_node*n);

int add_method_class(struct class_table *t,struct method_table*m);
//returns 1 if class else 0 for object
int class_or_obj(struct method_table *ct,char name[128]);

struct id_node* create_node(char access,char type[128],char name[128]);

struct method_table* create_method_table(char m_type,char r_type[128],char name[128]);

struct class_table  * create_class_table(char name[128]);

struct program_scope * create_program_scope();

int add_class_program(struct program_scope *,struct class_table*);

void add_class_list(struct ll_class*,struct class_table*);

int search_class_list(struct ll_class*,char name[128]);

int search_method_class(struct class_table *t, char name[128]);

struct id_node* get_node_by_name_in_method(struct method_table*mt,char name[128]);

struct id_node* get_node_by_name_in_class(struct class_table*mt,char name[128]);

struct class_table * get_class_by_name(struct ll_class *l,char name[128]);

int search_method_list(struct ll_method *l,char name[128]);

void free_node_list(struct  ll_id* l);

void free_method_list(struct ll_method *l);

void free_class_list(struct ll_class *l);

void display_class(struct class_table *);

struct ll_id *create_id_list(int);

#endif
