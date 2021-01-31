#ifndef FUNKTIONEN_H_INCLUDED
#define FUNKTIONEN_H_INCLUDED


#include "benutzereingaben.h"
#define DEAD 46
#define ALIVE 42

int ** gen_berechnen(int **m);
char * read_string();
int zaehlen(int **m, int r, int c);
int ** int_init(void);
char ** char_init(void);
void print(int **m);
void destroy_char(char **m);
void destroy(int **m);
void flush(void);
int flush_buff(void);

#endif
