#include "benutzereingaben.h"

int user_defined(int ***m)
{
        int i, j, n;
        char *input;
        char c;
        char **transition = char_init();
        int **matrix = int_init();

        /*Speicherfehrler abfangen*/
        if (transition == NULL || matrix == NULL) {
                printf("Speicherfehler\n");
                return 0;
        }

        /*Anleitung fuer Nutzer*/
        printf("\nGebe %d Zeichenketten mit jeweils %d Zeichen an.\n", ROW, COL);
        printf("Die Zeichenketten sollen durch ',' getrennt sein.\n");
        printf("Andere Zeichen sind nicht erlaubt.\n");
        printf("Beispiel:\n");
        for (j = 0; j < 2; j++) {
                for (i = 0; i < COL; ++i) {
                        if ((rand() % 3) == 0) {
                                printf("%c", ALIVE);
                        } else {
                                printf("%c", DEAD);
                        }
                }
                if (j == 0) {
                        printf(",");
                }
        }
        printf("\n\n");

        /*dynamisch Speicher reservieren*/
        input = malloc((ROW * COL + ROW) * sizeof(int));
        if (input == NULL) {
                printf("Speicherfehler\n");
                return 0;
        }

        /*Nutzerdefinierte Matrix einlesen*/
        i = 0;
        c = getchar();
        while (c != '\n') {
                *(input + i) = c;
                c = getchar();
                ++i;
        }
        *(input + i) = '\0';

        if (i != (ROW * COL + ROW - 1)) {
                printf("Fehlerhafte Eingabe!\n");
                return 0;
        }

        /*in Zwischenmatrix speichern*/
        i = 0;
        transition[i] = strtok(input, ",");
        for (i = 1; i < ROW; i++) {
                transition[i] = strtok(NULL, ",");
        }
        if (strtok(NULL, ",") != NULL) {
                printf("Formatfehler\n");
                return 0;
        }

        /*Zwischenmatrix an Endmatrix übergeben*/
        for (j = 0; j < ROW; ++j) {
                for (n = 0; n < COL; ++n) {
                        if (transition[j][n] == ALIVE) {
                                matrix[j][n] = ALIVE;
                        } else if (transition[j][n] == DEAD) {
                                matrix[j][n] = DEAD;
                        } else {
                                printf("Fehlerhafte Eingabe!\n");
                                return 0;
                        }
                }
        }
        printf("\n");
        *m = matrix;
        return 1;
}

int main_instruction(void)
{
        char c;

        /*Anleitung fuer Nutzer*/
        printf("\n");
        printf("Das Spielfeld besteht aus %d Zeilen und %d Reihen\n", ROW, COL);
        printf("%c steht fuer lebendige Zellen.\n", ALIVE);
        printf("%c steht fuer tote Zellen.\n", DEAD);
        printf("Wollen Sie die Anfangsgeneration selbst definieren? Geben Sie 'y' fuer ja, 'n' fuer nein ein.\n");
        printf("Um das Programm abzubrechen, geben Sie x ein\n");
        printf("Druecken Sie 2x Enter.\n");

        /*Auswertung der Nutzereingabe*/
        c = getchar();

        if (getchar() != '\n') {
                flush();
                main_instruction();
        }

        if (c == 'y') {
                flush();
                return 1;
        } else if (c == 'n') {
                flush();
                return 0;
        } else if (c == 'x') {
                flush();
                return -1;
        }

        flush();
        return main_instruction();

}
