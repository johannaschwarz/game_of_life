#include "benutzereingaben.h"
#include "generationen.h"

int programm_defined(int **m)
{
        int c;
        printf("\nFuer eine zufaellig generierte Anfangsgeneration, geben Sie 1 ein."
        "\nFuer eine interessante, vordefinierte Anfangsgeneration, geben Sie\n2 (toad)\noder "
        "3 (pulsar)\noder 4 (spaceship)\noder 5 (glidergun)\noder 6 (explosion)\noder 7 (f-Pentomino) ein.\n");
        printf("Geben Sie x ein, um abzubrechen.\n");
        c = getchar();
        if ((getchar() != '\n')|| c > '8' || c < '1') {
                if (c == 'x') {
                        printf("Programm wird abgebrochen.\n");
                        flush_buff();
                        destroy(m);
                        return 0;
                }
                flush();
                printf("\nEs sind ganze Zahlen zwischen 1 und 7 als Eingabe erlaubt.\n");
                return 2;
        }

        if (c == '1') {
                random_generation(m);
                return 1;
        } else if (c == '2') {
                generation_toad(m);
                return 1;
        } else if (c == '3') {
                generation_pulsar(m);
                return 1;
        } else if (c == '4') {
                generation_spaceship(m);
                return 1;
        } else if (c == '5') {
                generation_glidergun(m);
                return 1;
        } else if (c == '6') {
                generation_explosion(m);
                return 1;
        } else if (c == '7') {
                generation_fPentomino(m);
                return 1;
        }
        return 2;
}

int text_defined(int ***m)
{
        FILE *text;
        char input[ROW * COL + ROW] = "\0";
        char *name;
        char **transition = char_init();
        int **matrix = int_init();
        int i, j , n;

        /*Einlesen des Namens der Datei*/
        printf("Geben Sie den Namen der Textdatei ein.\n");
        name = read_string();

        /*Bei Fehler*/
        if (name == NULL) {
                printf("Name konnte nicht gelesen werden.\n");
                free(name);
                destroy_char(transition);
                destroy(matrix);
                flush();
                return 0;
        }
        printf("Eingelesener Name: %s\n", name);

        /*Strom aus Datei lesen*/
        text = fopen(name, "r");

        /*Bei Fehler*/
        if (text == NULL) {
                printf("Datei konnte nicht geöffnet werden.\n");
                free(name);
                destroy_char(transition);
                destroy(matrix);
                flush_buff();
                return 0;
        }

        /*Speichern der Datei in Zwischenmatrix*/
        for (j = 0; j < ROW; ++j) {

                i = fscanf(text,"%s", transition[j]);

                /*Bei Fehler*/
                if (i == EOF) {
                        printf("Fehler beim Auslesen der Datei\n");
                        flush_buff();
                        free(name);
                        destroy_char(transition);
                        destroy(matrix);
                        return 0;
                }

                /*printf("%s\n", transition[j]);*/
        }

        /*Überprüfen, ob text leer ist*/
        i = fscanf(text, "%s", input);

        /*printf("input: %s\n", input);*/

        /*Falls Datei länger als Matrixgröße:*/
        if (i != EOF || *input != '\0') {
                printf("zu lange Eingabe!\n");
                free(name);
                destroy_char(transition);
                flush_buff();
                destroy(matrix);
                return 0;
        }

        /*Falls Datei fehlerhaft ist*/
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        if (transition[i][j] == ALIVE || transition[i][j] == DEAD) {
                                continue;
                        } else {
                                printf("Fehlerhafte Datei!\n");
                                free(name);
                                flush_buff();
                                destroy_char(transition);
                                destroy(matrix);
                                return 0;
                        }
                }
        }

        fclose(text);

        /*Zwischenmatrix an Endmatrix übergeben*/
        for (j = 0; j < ROW; ++j) {
                for (n = 0; n < COL; ++n) {
                        if (transition[j][n] == ALIVE) {
                                matrix[j][n] = ALIVE;
                        } else if (transition[j][n] == DEAD) {
                                matrix[j][n] = DEAD;
                        } else {
                                printf("Uebertragung in int-Matrix funktioniert nicht!\n");
                                free(name);
                                destroy_char(transition);
                                destroy(matrix);
                                return 0;
                        }
                }
        }
        printf("\n");

        *m = matrix;
        free(name);
        destroy_char(transition);
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

        if (flush() == 1) {
                printf("Falsche Eingabe!\n");
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

        printf("\nFalsche Eingabe!\n");
        flush();
        return main_instruction();

}
int user_defined(int ***m)
{
        int i, j, n;
        char input[ROW * COL + ROW];
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

        /*Nutzerdefinierte Matrix einlesen*/
        i = 0;
        c = getchar();
        while (c != '\n') {
                input[i] = c;
                c = getchar();
                ++i;
        }
        input[i] = '\0';

        if (i != (ROW * COL + ROW - 1)) {
                printf("Zeichenkette: Fehlerhafte Eingabe!\n");
                return 0;
        }

        /*in Zwischenmatrix speichern*/
        i = 0;
        transition[i] = strtok(input, ",");
        printf("%s\n", transition[i]);
        for (i = 1; i < ROW; i++) {
                transition[i] = strtok(NULL, ",");
                printf("%s\n", transition[i]);
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
                                printf("Uebertragung in int-Matrix funktioniert nicht!\n");
                                return 0;
                        }
                }
        }
        printf("\n");
        *m = matrix;
        return 1;
}
