#include "benutzereingaben.h"

int programm_defined(int **m)
{
        int c;
        printf("\nFuer eine zufaellig generierte Anfangsgeneration, geben Sie 1 ein."
        "\nFuer eine interessante, vordefinierte Anfangsgeneration, geben Sie\n2 (toad)\noder "
        "3 (pulsar)\noder 4 (spaceship)\noder 5 (glidergun)\noder 6 (explosion)\noder 7 (f-Pentomino)"
        "\noder 8 (mulitple spaceships)\noder 9 (static) ein.\n");
        printf("Geben Sie x ein, um abzubrechen.\n");
        printf("Druecken Sie anschliessend Enter.\n");
        printf("Eingabe: ");
        c = getchar();
        if ((getchar() != '\n')|| c > '9' || c < '1') {
                if (c == 'x') {
                        return 0;
                }
                flush();
                printf("\nEs sind ganze Zahlen zwischen 1 und 9 (jeweils inklusive) als Eingabe erlaubt. Druecken Sie Enter, um fortzufahren.\n");
                flush();
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
        } else if (c == '8') {
                generation_multiple_spaceships(m);
                return 1;
        } else if (c == '9') {
                generation_static(m);
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
        printf("Geben Sie den Namen der Textdatei ein und druecken Sie anschliessend Enter\n");
        printf("Name: ");
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
        printf("\nEingelesener Name: %s\n", name);

        /*Strom aus Datei lesen*/
        text = fopen(name, "r");

        /*Bei Fehler*/
        if (text == NULL) {
                printf("Datei konnte nicht geoeffnet werden. Druecken Sie Enter, um fortzufahren.\n");
                free(name);
                destroy_char(transition);
                destroy(matrix);
                return 0;
        }



        /*Speichern der Datei in Zwischenmatrix*/
        for (j = 0; j < ROW; ++j) {

                if (fgets(transition[j], COL + 1, text) == NULL) {
                        printf("Fehler beim Auslesen der Datei!. Druecken Sie Enter, um fortzufahren.\n");
                        free(name);
                        destroy_char(transition);
                        destroy(matrix);
                        return 0;
                }
                if (strlen(transition[j]) != COL) {
                        printf("Fehlerhafte Eingabe. Druecken Sie Enter, um fortzufahren.\n");
                        free(name);
                        destroy_char(transition);
                        destroy(matrix);
                        return 0;
                }
                i = fgetc(text);
                if (i == EOF || (i != '\n' && i != 13)) {
                        printf("Fehlerhafte Eingabe. Druecken Sie Enter, um fortzufahren.\n");
                        free(name);
                        destroy_char(transition);
                        destroy(matrix);
                        return 0;
                }

                i = fgetc(text);
                if (i != '\n' && i != 13) {
                        printf("Zu lange Eingabe! Druecken Sie Enter, um fortzufahren.\n");
                        free(name);
                        destroy_char(transition);
                        destroy(matrix);
                        return 0;
                }
        }

        /*Überprüfen, ob text leer ist*/
        i = fscanf(text, "%s", input);

        /*Falls Datei länger als Matrixgröße:*/
        if (i != EOF) {
                printf("Zu lange Eingabe! Druecken Sie Enter, um fortzufahren.\n");
                free(name);
                destroy_char(transition);
                destroy(matrix);
                return 0;
        }

        /*Falls Datei fehlerhaft ist*/
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        if (transition[i][j] == ALIVE || transition[i][j] == DEAD) {
                                continue;
                        } else {
                                printf("Fehlerhafte Datei! Druecken Sie Enter, um fortzufahren.\n");
                                free(name);
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
                                printf("Uebertragung in int-Matrix funktioniert nicht! Druecken Sie Enter, um fortzufahren.\n");
                                free(name);
                                destroy_char(transition);
                                destroy(matrix);
                                return 0;
                        }
                }
        }
        printf("\n");
        printf("Druecken Sie Enter.\n");

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
        printf("Das Spielfeld besteht aus %d Zeilen und %d Reihen.\n", ROW, COL);
        printf("%c steht fuer lebendige Zellen.\n", ALIVE);
        printf("%c steht fuer tote Zellen.\n", DEAD);
        printf("Wollen Sie die Anfangsgeneration selbst definieren? Geben Sie 'y' fuer ja, 'n' fuer nein ein.\n");
        printf("Um das Programm abzubrechen, geben Sie x ein.\n");
        printf("Druecken Sie anschliessend Enter.\n");

        /*Auswertung der Nutzereingabe*/
        printf("Eingabe: ");
        c = getchar();

        printf("\n");

        if (c == 'y' && !flush()) {
                return 1;
        } else if (c == 'n' && !flush()) {
                return 0;
        } else if (c == 'x' && !flush()) {
                return -1;
        }

        printf("\nFehlerhafte Eingabe!\n");
        flush();
        return main_instruction();

}
int user_defined(int ***m, char *input)
{
        int i;
        int zeile, spalte;
        char transition[2][6];
        int **matrix;
        int t01, t00, t10, t11;
        char *token;
        matrix = *m;


        if ((strlen(input) != 5 || flush()) && input[0] != 'f' && input[0] != 'x'){
                printf("Fehlerhafte Eingabe!\n");
                printf("\nBitte nur Zahlen zwischen 1 und %i fuer Zeilen und 1 und %i fuer Spalten, in der Form Zeilen,Spalten eingeben und bei einstelligen Zahlen eine 0 voranstellen!\n", ROW, COL);
                printf("Oder geben Sie f oder x ein, um die Eingabe zu beenden oder das Programm abzubrechen\n");
                printf("Druecken Sie anschliessend Enter, um fortzufahren.\n");
                return -1;
        }
        /*Ueberpruefung auf Speicherfehler*/
        if (matrix == NULL) {
                printf("Speicherfehler!\n");
                return 0;
        }


        /*Zellenangabe einlesen*/
        token = strtok(input, ",");
        i = 0;
        while (token[i] != '\0') {
                transition[0][i] = token[i];
                i++;
        }
        transition[0][i] = '\0';

        token = strtok(NULL, ",");
        i = 0;
        if (transition[0][0] == 'f' && transition[0][1] == '\0' && token == NULL) {
                return 2;
        } else if (transition[0][0] == 'x' && transition[0][1] == '\0' && token == NULL) {
                return 3;
        } else if (token == NULL) {
                printf("Fehlerhafte Eingabe\n");
                printf("\nBitte nur Zahlen zwischen 1 und %i fuer Zeilen und 1 und %i fuer Spalten, in der Form Zeilen,Spalten eingeben und bei einstelligen Zahlen eine 0 vorananstellen!\n", ROW, COL);
                printf("Oder geben Sie f oder x ein, um die Eingabe zu beenden oder das Programm abzubrechen\n");
                printf("Druecken Sie nach jeder neuen Eingabe Enter.\n");
                return -1;
        }

        while (token[i] != '\0') {
                transition[1][i] = token[i];
                i++;
        }
        transition[1][i] = '\0';

        /*Eingabe auf Richtigkeit ueberpruefen*/
        if (strtok(NULL, ",") != NULL) {
                printf("Fehlerhafte Eingabe!\nBitte wiederholen!\n");
                printf("\nBitte nur Zahlen zwischen 1 und %i fuer Zeilen und 1 und %i fuer Spalten, in der Form Zeilen,Spalten eingeben und bei einstelligen Zahlen eine 0 voanranstellen!\n", ROW, COL);
                printf("Oder geben Sie f oder x ein, um die Eingabe zu beenden oder das Programm abzubrechen\n");
                printf("Druecken Sie nach jeder neuen Eingabe Enter.\n");
                return -1;
        } else if (!isdigit(transition[0][0]) || !isdigit(transition[0][1]) || !isdigit(transition[1][0]) || !isdigit(transition[1][1])) {
                printf("\nBitte nur Zahlen zwischen 1 und %i fuer Zeilen und 1 und %i fuer Spalten, in der Form Zeilen,Spalten eingeben und bei einstelligen Zahlen eine 0 vorananstellen!\n", ROW, COL);
                return -1;
        }
        t00 = transition[0][0] - '0';
        t01 = transition[0][1] - '0';
        t10 = transition[1][0] - '0';
        t11 = transition[1][1] - '0';

        zeile = t00 * 10 + t01;
        spalte = t10 * 10 + t11;

        if (zeile > 50 || spalte > 50) {
                printf("Fehlerhafte Eingabe!\nBitte wiederholen!\n");
                printf("\nBitte nur Zahlen zwischen 1 und %i fuer Zeilen und 1 und %i fuer Spalten, in der Form Zeilen,Spalten eingeben und bei einstelligen Zahlen eine 0 voanranstellen!\n", ROW, COL);
                printf("Oder geben Sie f oder x ein, um die Eingabe zu beenden oder das Programm abzubrechen\n");
                printf("Druecken Sie nach jeder neuen Eingabe Enter.\n");
                return -1;
        }

        /*lebende Zelle an Zwischenmatrix uebergeben*/
        matrix[(zeile - 1)][(spalte - 1)] = ALIVE;

        *m = matrix;

        return 1;
}
