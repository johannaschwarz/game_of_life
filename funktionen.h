#ifndef FUNKTIONEN_H_INCLUDED
#define FUNKTIONEN_H_INCLUDED

#include "benutzereingaben.h"

int ** gen_berechnen(int **m);
int zaehlen(int **m, int r, int c);
int ** int_init(void);
char ** char_init(void);
void random_generation(int **m);
void print(int **m);
void destroy(int **m);
void flush(void);

#endif
