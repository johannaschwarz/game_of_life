#include "funktionen.h"


int ** init(void)
{
        int i, j;
        int **m = malloc(MAXROW * sizeof(int*));
        if (m == NULL) {
                return NULL;
        }
        for (i = 0; i < MAXCOL; i++) {
                m[i] = malloc(MAXCOL * sizeof(int));
                if (m[i] == NULL) {
                        for (j = 0; j < i; j++) {
                                free(m[j]);
                        }
                        free(m);
                        return NULL;
                }
        }
        return m;
}

void random_generation(int **m)
{
        int i, j;
        for (i = 0; i < MAXROW; ++i) {
                for (j = 0; j < MAXCOL; ++j) {
                        if ((rand() % 2) == 0) {
                                m[i][j] = '*';
                        } else {
                                m[i][j] = '-';
                        }
                }
        }
}

void print(int **m) {
        int i, j;
        for (i = 0; i < MAXROW; i++) {
                for (j = 0; j < MAXCOL; j++) {
                        printf("%c", m[i][j]);
                }
                printf("\n");
        }
}

void destroy(int **m) {
        int i;
        for (i = 0; i < MAXROW; i++) {
                free(m[i]);
        }
        free(m);
}
