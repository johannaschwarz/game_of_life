#include "funktionen.h"
/*
Algorithmus:
        1. Matrize mit ALIVE als lebendige Zelle; DEAD als tote Zelle
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
        int i, j, counter, survivors = 0;
        int **m, **n;
        /*Werte an Zwischenzeiger übergeben*/
        m = int_init();
        n = int_init();

        for (i = 0; i < ROW; i++) {
                for (j = 0; j < COL; j++) {
                        m[i][j] = matrix[i][j];
                        if (m[i][j] == ALIVE) {
                                ++survivors;
                        }
                        /*printf("%c", m[i][j]);*/
                }
                /*printf("\n");*/
        }

        for (i = 0; i < ROW; i++) {
                for (j = 0; j < COL; j++) {
                        n[i][j] = matrix[i][j];
                        if (n[i][j] == ALIVE) {
                                ++survivors;
                        }
                        /*printf("%c", m[i][j]);*/
                }
                /*printf("\n");*/
        }

        if (survivors == 0) {
                printf("Alle Zellen sind tot.\n");
                return NULL;
        }

        /*Folgegeneration berechnen */
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        counter = zaehlen(m, i, j);
                        /*bei toter Zelle*/
                        if (m[i][j] == DEAD) {
                                if (counter == 3) {
                                        /*Zelle wird geboren*/
                                        n[i][j] = ALIVE;
                                }
                        /*bei lebendiger Zelle*/
                        } else if (m[i][j] == ALIVE){
                                if (counter < 2 || counter > 3) {
                                        /*Zelle stirbt*/
                                        n[i][j] = DEAD;
                                }
                        } else {
                                printf("Fehler beim Generieren der Folgegeneration\n");
                                return NULL;
                        }
                }
        }
        return n;
}
/*
int rand_zaehlen(int **m, int r, int c) {
        bei row = 0:

}
*/
char * read_string() {
        char c = getchar();
        int i = 0;
        char *string = malloc((i + 1) * sizeof(char));
        if (string == NULL) {
                flush();
                return NULL;
        }
        while (c != '\n') {
                string[i] = c;
                c = getchar();
                ++i;
                string = realloc(string, (i + 1) * sizeof(char));
                if (string == NULL) {
                        flush();
                        return NULL;
                }
        }
        string[i] = '\0';
        flush();
        return string;
}

int zaehlen(int **m, int r, int c)
{
        int counter = 0, i, j;
        for (i = r - 1; i <= r + 1; i++) {
                for (j = c - 1; j <= c + 1; j++) {
                        /*Auslassen der mittleren Zelle*/
                        if (i == r && j == c) {
                                continue;
                        }
                        /*printf("Mod i:%i\n Mod j: %i\n", (ROW + i) % ROW, (COL + j) % COL);*/
                        /*Zaehlen der lebendigen Zellen um die gesuchte Zelle herum*/
                        if (m[(ROW +i) % ROW][(COL + j) % COL] == ALIVE) {
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

void print(int **m)
{
        int i, j;
        for (i = 0; i < ROW; i++) {
                for (j = 0; j < COL; j++) {
                        printf("%c  ", m[i][j]);
                }
                printf("\n");
        }
}

void destroy_char(char **m)
{
        int i;
        for (i = 0; i < ROW; i++) {
                free(m[i]);
        }
        free(m);
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

int flush_buff(void)
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return c != EOF;
}
