#include "funktionen.h"


int ** int_init(void)
{
        int i, j;
        int **m = calloc(ROW, sizeof(int*));
        if (m == NULL) {
                return NULL;
        }
        for (i = 0; i < COL; i++) {
                m[i] = calloc(COL, sizeof(int));
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

char ** char_init(void)
{
        int i, j;
        char **m = malloc(ROW * sizeof(char*));
        if (m == NULL) {
                return NULL;
        }
        for (i = 0; i < COL; i++) {
                m[i] = malloc(COL * sizeof(char));
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
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        if ((rand() % 2) == 0) {
                                m[i][j] = '*';
                        } else {
                                m[i][j] = '-';
                        }
                }
        }
}

void print(int **m)
{
        int i, j;
        for (i = 0; i < ROW; i++) {
                for (j = 0; j < COL; j++) {
                        printf("%c", m[i][j]);
                }
                printf("\n");
        }
}

void destroy(int **m)
{
        int i;
        for (i = 0; i < ROW; i++) {
                free(m[i]);
        }
        free(m);
}

void flush(void)
{
        while (getchar() != '\n'){

        }
}
