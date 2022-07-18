
/************************************************************************
University of Leeds
School of Computing
COMP2932- Compiler Design and Construction
The Symbol Tables Module

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name:
Student ID:
Email:
Date Work Commenced:
*************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "symbols.h"

extern int st;

int equals_id(struct id_node x, struct id_node y) {

    return !strcmp(x.name, y.name);
}

int equals_method(struct method_table t1, struct method_table t2) {


    return !strcmp(t1.name, t2.name);


}

int class_or_obj(struct method_table *mt, char name[128]) {

    if (search_id_method(mt, name) == -1) {


        return 1;
    }

    return 0;


}


int search_id_method(struct method_table *t, char name[128]) {


    struct id_node *x = t->id_list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return 1;
        }
        x = x->next;
    }


    return search_id_class(t->class, name);

}

int search_id_class(struct class_table *t, char name[128]) {

    struct id_node *x = t->id_list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return 1;
        }

        x = x->next;
    }

    return -1;
}

struct id_node *get_node_by_name_in_method(struct method_table *mt, char name[128]) {


    struct id_node *x = mt->id_list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return x;
        }
        x = x->next;
    }


    return get_node_by_name_in_class(mt->class, name);

}

struct id_node *get_node_by_name_in_class(struct class_table *ct, char name[128]) {
    struct id_node *x = ct->id_list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return x;
        }

        x = x->next;
    }

    return 0;


}

int search_method_list(struct ll_method *l, char name[128]) {


    struct method_table *x = l->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return 1;
        }
        x = x->next;
    }

    return -1;


}

int search_method_class(struct class_table *t, char name[128]) {


    struct method_table *x = t->method_list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return 1;
        }
        x = x->next;
    }

    return -1;


}

struct id_node *create_node(char access, char type[128], char name[128]) {

    struct id_node *v = malloc(sizeof(struct id_node));

    strcpy(v->name, name);

    strcpy(v->type, type);

    v->access = access;

    return v;
}

struct class_table *create_class_table(char name[128]) {


    struct class_table *t;


    t = malloc(sizeof(struct class_table));

    strcpy(t->name, name);

    t->id_list = malloc(sizeof(struct ll_id));

    t->method_list = malloc(sizeof(struct ll_method));


    t->id_list=create_id_list(0);

    t->method_list->ctr = 0;

    t->method_list->head = 0;

    t->method_list->tail = 0;


    //t->method_list->ctr=0;

    return t;

}


void add_id_list(struct ll_id *l, struct id_node *v) {

    int n=l->ctr;

    if (n == 0) {

        l->head = v;

        l->tail = v;


    } else {

        l->tail->next = v;

        l->tail = v;


    }
    //arguement
    if(v->access=='a'){

        v->idx=l->a_ctr;

        l->a_ctr++;

    }
    //static variable
    else if(v->access=='s'){

     //increment external static variable

     v->idx=st;
     st++;



    }
    //field variable
    else if (v->access=='f') {

        v->idx=l->f_ctr;

        l->f_ctr++;



    }

    //local variable

    else if(v->access=='l'){

        v->idx=l->l_ctr;

        l->l_ctr++;


    }

    l->ctr++;

    v->next = 0;



}

void add_method_list(struct ll_method *l, struct method_table *t) {

    if (l->ctr == 0) {


        l->head = t;

        l->tail = t;
    } else {

        l->tail->next = t;

        l->tail = t;


    }
    t->next = 0;

    l->ctr += 1;


}


int add_id_class(struct class_table *t, struct id_node *v) {

    if (search_id_class(t, v->name) == -1) {


        add_id_list(t->id_list, v);
        v->ct = t;
        return 1;
    }

    return -1;


}

int add_id_method(struct method_table *t, struct id_node *v) {


    if (search_id_method(t, v->name) == -1) {
        add_id_list(t->id_list, v);

        return 1;
    }

    return -1;


}

struct ll_id *create_id_list(int idc){
    struct ll_id *l=malloc(sizeof (struct ll_id));

    l->l_ctr=0;
    l->a_ctr=0;
    l->head=0;
    l->tail=0;

    l->a_ctr=idc;

    l->f_ctr=0;
    l->ctr=0;

    return l;


}


int add_method_class(struct class_table *c, struct method_table *m) {

    if (search_method_class(c, m->name) == -1) {


        m->class = c;

        add_method_list(c->method_list, m);

        return 1;


    }

    return -1;
}


struct method_table *create_method_table(char m_type, char r_type[128], char name[128]) {

    struct method_table *t = malloc(sizeof(struct method_table));


    if(m_type=='m') {
        t->id_list = create_id_list(1);
    }

    else{

        t->id_list= create_id_list(0);
    }

    strcpy(t->r_type, r_type);

    strcpy(t->name, name);

    t->m_type = m_type;



    return t;

}


struct program_scope *create_program_scope() {


    struct program_scope *p = malloc(sizeof(struct program_scope));

    p->class_list = malloc(sizeof(struct ll_class));

    p->class_list->ctr = 0;


    p->umethods = malloc(sizeof(struct ll_method));

    p->umethods->ctr = 0;

    p->uclass = malloc(sizeof(struct ll_class));

    p->uclass->ctr = 0;

    p->uid=create_id_list(0);

    return p;


}

int search_class_list(struct ll_class *list, char name[128]) {


    struct class_table *x = list->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return 1;
        }
        x = x->next;
    }

    return -1;
}

void add_class_list(struct ll_class *l, struct class_table *ct) {

    if (l->ctr == 0) {


        //printf("FIRST CLASS ADDED\n");

        //printf ("<%s, %i, %s>\n", ct->tk.fl, ct->tk.ln , ct->tk.lx);


        l->head = ct;
        l->tail = ct;
    } else {
        //printf("CLASS ADDED\n");

        //printf ("<%s, %i, %s>\n", ct->tk.fl, ct->tk.ln , ct->tk.lx);

        l->tail->next = ct;

        l->tail = ct;


    }

    l->tail->next = 0;


    l->ctr += 1;


}

struct class_table *get_class_by_name(struct ll_class *l, char name[128]) {

    struct class_table *x = l->head;

    while (x != 0) {

        if (!strcmp(x->name, name)) {

            return x;
        }

        x = x->next;
    }

    return 0;


}

void free_node_list(struct ll_id *l) {


    struct id_node *tmp;
    struct id_node *head = l->head;

    while (l->ctr > 0) {
        tmp = head;

        head = head->next;
        free(tmp);
        l->ctr -= 1;
    }

}

void free_method_list(struct ll_method *l) {

    struct method_table *tmp;

    struct method_table *head = l->head;

    while (l->ctr > 0) {
        tmp = head;
        free_node_list(tmp->id_list);

        head = head->next;

        free(tmp);

        l->ctr -= 1;

    }


}

void free_class_list(struct ll_class *l) {


    struct class_table *tmp;
    struct class_table *head = l->head;

    while (l->ctr > 0) {
        tmp = head;

        free_method_list(tmp->method_list);

        head = head->next;
        free(tmp);
        l->ctr -= 1;

    }


}


/*int main() {

    struct class_table *Ball = create_class_table("Ball");

    struct class_table *ball= create_class_table("ball");



    struct program_scope *p=create_program_scope() ;

    add_class_list(p->class_list,Ball);
    add_class_list(p->class_list,ball);

    printf("%d\n",search_class_list(p->class_list,Ball->name));

    printf("%d\n",search_class_list(p->class_list,ball->name));

    display_class_list(p->class_list);



    struct method_table *m1 = create_methd_table('c', "Ball", "new");

    struct method_table *m2= create_method_table('f', "int","foo");

    struct method_table *m3= create_method_table('m',"char","foo");

    struct method_table *m4= create_method_table('m',"char","new");

    printf("%d\n",add_method_class(Ball,m1));

    printf("%d\n",add_method_class(Ball,m2));

   printf("%d\n",add_method_class(Ball,m3));

    printf("%d\n",add_method_class(Ball,m4));


   add_method_class(Ball,m2);

    struct id_node *v_1= create_node('s',"int ","foo");

    struct id_node *v_2= create_node('s',"int ","def");

    add_id_class(Ball,v_1);

    add_id_class(Ball,v_2);



    struct id_node *v_3= create_node('s',"int ","multi");

    struct id_node *v_4= create_node('s',"int ","add");

    add_id_method(m1,v_3);

    add_id_method(m1,v_4);

    add_id_method(m2,v_3);

    add_id_method(m2,v_4);

   printf("%d\n",add_id_method(m1,v_1));

    printf("%d\n",add_id_method(m1,v_2));

    printf("%d\n",add_id_method(m2,v_1));

    printf("%d\n",add_id_method(m2,v_2));

    printf("%d\n",add_id_class(Ball,v_1));





    display_class(Ball);

    display_ids_in_method(m1);

    display_ids_in_method(m2);



}*/