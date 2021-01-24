#include "funktionen.h"
/*
Algorithmus:
        1. Matrize mit 42 als lebendige Zelle; 45 als tote Zelle
        2. Zelle [j][i]
                counter = 0;
                für jeden lebendigen Nachbarn ++counter

                [j-1]:  [i-1][i][i+1]
                [j]:    [i-1][i+1]
                [j+1]:  [i-1][i][i+1]
        3. Fallunterscheidung für jede Zelle:
                - lebendige Zelle(*):
                < 2 * = tot!
                2 - 3 * = lebendig
                > 3 = tot!

                - tote Zelle(-):
                != 3 * = tot
                = 3 * = lebendig

                char raster[10][10] = {"*-------**","***----**-"};
                printf("%i\n", '-');
                for (i = 0; i < 2; ++i) {
                        for (j = 0; j < 10; ++j) {
                                printf("%c", raster[i][j]);
                        }
                        printf("\n");
                }

*/

int ** gen_berechnen(int **matrix)
{
        int i, j, counter;
        int **m;
        /*Werte an Zwischenzeiger übergeben*/
        m = int_init();

        for (i = 0; i < ROW; i++) {
                for (j = 0; j < COL; j++) {
                        m[i][j] = matrix[i][j];
                        /*printf("%c", m[i][j]);*/
                }
                /*printf("\n");*/
        }

        /*Folgegeneration berechnen */
        for (i = 1; i < ROW - 1; ++i) {
                for (j = 1; j < COL - 1; ++j) {
                        counter = zaehlen(m, i, j);
                        /*bei toter Zelle*/
                        if (m[i][j] == 45) {
                                if (counter == 3) {
                                        /*Zelle wird geboren*/
                                        m[i][j] = 42;
                                }
                        /*bei lebendiger Zelle*/
                        } else if (m[i][j] == 42){
                                if (counter < 2 || counter > 3) {
                                        /*Zelle stirbt*/
                                        m[i][j] = 45;
                                }
                        } else {
                                return NULL;
                        }
                printf("%c", m[i][j]);
                }
                printf("\n");
        }
        return m;
}
/*
int rand_zaehlen(int **m, int r, int c) {
        bei row = 0:

}
*/
int zaehlen(int **m, int r, int c)
{
        int counter = 0, i, j;
        for (i = r - 1; i <= r + 1; i++) {
                for (j = c - 1; j <= c + 1; j++) {
                        /*Auslassen der mittleren Zelle*/
                        if (i == r && j == c) {
                                continue;
                        }
                        /*Zaehlen der lebendigen Zellen um die gesuchte Zelle herum*/
                        if (m[i][j] == 42) {
                                ++counter;
                        }
                }
        }
        return counter;
}

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
