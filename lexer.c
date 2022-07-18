/************************************************************************
University of Leeds
School of Computing
COMP2932- Compiler Design and Construction
Lexer Module

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name:Janam Zaveri
Student ID:201391181
Email:sc20jjz@leeds.ac.uk
Date Work Commenced:16-2-2022
*************************************************************************/
#define NumberTestFiles 15
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// YOU CAN ADD YOUR OWN FUNCTIONS, DECLARATIONS AND VARIABLES HERE


int max_size=10;

FILE *fp;

char *buff;

int l_0 = 1;

int l_1 = 1;

int idx = -1;

char symbols[] = "{}()[],;=.+-*/&|~<>";

char reswords[21][128] = {"class", "constructor", "method", "function", "int", "boolean", "char", "void", "var", "static", "field", "let", "do", "if", "else", "while", "return", "true", "false", "null", "this"};

char fl[32];
int check_if_resword(char lx[128])
{

  for (int i = 0; i < 21; i++)
  {

    if (strcmp(lx, reswords[i]) == 0)
    {

      return 1;
    }
  }

  return 0;
}

int check_if_symbol(char x)
{

  for (int i = 0; i < strlen(symbols); i++)
  {

    if (symbols[i] == x)
    {

      return 1;
    }
  }

  return 0;
}
int extract_id(char lexeme[128], int idx)
{

  int ctr = 0;

  while (isalnum(buff[idx + 1]) || buff[idx + 1] == '_')
  {

    lexeme[ctr] = buff[idx + 1];

    idx += 1;

    ctr += 1;
  }

  lexeme[ctr] = '\0';

  return idx;
}

int extract_int(char lexeme[128], int idx)
{

  int ctr = 0;
  while (isdigit(buff[idx + 1]))
  {

    lexeme[ctr] = buff[idx + 1];

    idx += 1;

    ctr += 1;
  }

  lexeme[ctr] = '\0';

  return idx;
}

int extract_string(char lexeme[128], int idx)
{

  int ctr = 0;

  char start_quote = buff[idx + 1];
  idx += 1;

  while (buff[idx + 1] != start_quote && !(buff[idx + 1] == '\0' || buff[idx + 1] == '\n'))
  {

    lexeme[ctr] = buff[idx + 1];

    idx += 1;

    ctr += 1;
  }

  if (buff[idx + 1] == '\0')
  {


    strcpy(lexeme,"Eofdetected");
    return -2;
  }
  else if (buff[idx + 1] == '\n')
  {

    strcpy(lexeme,"Eoldetected");
    return -1;
  }

  lexeme[ctr] = '\0';

  idx += 1;
  return idx;
}

void print_chars()
{

  while (buff[idx + 1] != '\0')
  {

    printf("%d", buff[idx + 1]);

    idx += 1;
  }
}
//PLEASE REFERENCE THE BELOW METHOD
void write_buff(FILE *fp)
{

  size_t n = 0;
  int c;

  while ((c = fgetc(fp)) != EOF)
  {
    buff[n++] = (char)c;

    if (n%10==9)
    {max_size+=10;

      buff=realloc(buff,max_size );
    }
  }

  buff[n] = '\0';
}

int skip_single_line_comments(int idx)
{

  idx += 2;

  while (buff[idx + 1] != '\n')
  {
    if (buff[idx] == EOF)
    {

      return 0;
    }

    idx += 1;
  }

  return idx;
}

int skip_multi_line_comments(int idx, int peekorget)
{

  idx += 2;

  while (!(buff[idx + 1] == '*' && buff[idx + 2] == '/'))
  {

    if (buff[idx+1] == '\0')
    {

      return 0;
    }

    if (buff[idx+1]=='\n')
    {
      if (peekorget == 0)
      {

        l_0 += 1;
      }

      else
      {

        l_1 += 1;
      }
    }

    idx += 1;
  }

  idx += 2;

  return idx;
}

int skip_space(int idx)
{

  while (buff[idx + 1] == ' ')
  {

    idx += 1;
  }

  return idx;
}

// IMPLEMENT THE FOLLOWING functions
//***********************************

// Initialise the lexer to read from source file
// file_name is the name of the source file
// This requires opening the file and making any necessary initialisations of the lexer
// If an error occurs, the function should return 0
// if everything goes well the function should return 1
int InitLexer(char *file_name)
{ idx=-1;

l_0=1;
l_1=1;
  strcpy(fl,file_name);
  fp = fopen(file_name, "r");

  buff = malloc(10*sizeof(char));

  if (fp == NULL)
  {
    
    return 0;
  }

  write_buff(fp);

  return 1;
}
//0->peek
//1->get
int extract_token(Token *t, int idx, int peekorget)
{
check:

  if (buff[idx + 1] == '\0')
  {

    t->tp = EOFile;
  }

  else if (isalpha(buff[idx + 1]) || buff[idx + 1] == '_')
  {

    idx = extract_id(t->lx, idx);

    if (check_if_resword(t->lx) == 1)
    {

      t->tp = RESWORD;
    }
    else
    {

      t->tp = ID;
    }
  }
  else if (isdigit(buff[idx + 1]))
  {

    idx = extract_int(t->lx, idx);

    t->tp = INT;
  }

  else if (buff[idx + 1] == '/' && buff[idx + 2] == '/')
  {
    if ((idx = skip_single_line_comments(idx)) == 0)
    {

      t->tp = ERR;

      t->ec =0;

      return -1;
    }

    goto check;
  }

  else if (buff[idx + 1] == '/' && buff[idx + 2] == '*')
  {

    if ((idx = skip_multi_line_comments(idx,peekorget)) == 0)
    {

      t->tp = ERR;

      t->ec = 0;

      return -1;
    }

    goto check;
  }

  else if (buff[idx + 1] == ' ')
  {

    idx = skip_space(idx);

    goto check;
  }

  else if (buff[idx + 1]=='\n')
  {

    idx += 1;
    if (peekorget == 0)
      {

        l_0 += 1;
      }

      else
      {

        l_1 += 1;
      }

    

    goto check;
  }

  else if (buff[idx + 1] == '"')


  {


   
    if ((idx = extract_string(t->lx, idx)) < 0)
    {

      t->tp = ERR;

      t->ec = abs(idx);

      return -1;
    }

    t->tp = STRING;
  }

  else if (check_if_symbol(buff[idx + 1]))
  {

    t->tp = SYMBOL;
    t->lx[0] = buff[idx + 1];

    t->lx[1] = '\0';

    idx += 1;
  }

  else if((int)buff[idx+1]==13||(int)buff[idx+1]==9)
  {


    idx += 1;

    goto check;
  }

  else{




    t->tp=ERR;

    t->ec=3;
  

    return -1;


  }



  return idx;
}
//typedef enum {EofInCom , NewLnInStr , EofInStr , IllSym} LexErrCodes;
// Get the next token from the source file
Token GetNextToken()
{



  Token t;

  int new_idx = extract_token(&t, idx,1);

  if (new_idx > 0 || new_idx == 0)
  {

    idx = new_idx;
  }

  else{

    if(t.ec==0){

      strcpy(t.lx,"Error: unexpected eof in comment");
      
      }

    else if(t.ec==1){


      strcpy(t.lx,"Error: new line in string constant");
    }

    else if(t.ec==2){

        strcpy(t.lx,"Error: unexpected eof in string constant");



    }

    else if(t.ec==3){

      strcpy(t.lx,"Error: illegal symbol in source file");


    }



  }
  strcpy(t.fl,fl);

t.ln=l_1;

  return t;
}
// peek (look) at the next token in the source file without removing it from the stream
Token PeekNextToken()
{
  Token t;

  int idx_two = idx;

  idx_two = extract_token(&t, idx_two,0);

  if(idx_two<0){


    if(t.ec==0){

      strcpy(t.lx,"Error: unexpected eof in comment");
      
      }

    else if(t.ec==1){


      strcpy(t.lx,"Error: new line in string constant");
    }

    else if(t.ec==2){

        strcpy(t.lx,"Error: unexpected eof in string constant");



    }

    else if(t.ec==3){

      strcpy(t.lx,"Error: illegal symbol in source file");


    }








  }
    
    strcpy(t.fl,fl);

  t.ln=l_0;

  return t;
}

// clean out at end, e.g. close files, free memory, ... etc
int StopLexer()


{


  fclose(fp);

  free(buff);


  return 0;
}

// do not remove the next line
#ifndef TEST



/*int main()
{
  // implement your main function here
  // NOTE: the autograder will not use your main function

  char *file_name = "IllegalSymbol.jack";

  InitLexer(file_name);

  Token t;

  while (PeekNextToken().tp != EOFile)
  {

    t = GetNextToken();

    

    if (t.tp == ERR)
    {

      


      PrintToken(t);

      return -1;
    }


  }

  return 0;
}*/
// do not remove the next line
#endif
