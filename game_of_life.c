#include "benutzereingaben.h"
#include "funktionen.h"
#include "generationen.h"


int main (void)
{
        /*Variablen anlegen*/
        int **matrix;
        int nutzer_def, x = 0, i = 0, c, survivors = 0;
        int u = -1, status;
        char input[10];
        srand(time(NULL));

        printf("\nCONWAY'S GAME OF LIFE:\n\n");
        /*Speicher fuer die Matrix reservieren*/
        matrix = int_init();

        if (matrix == NULL) {
                printf("\nSpeicherfehler\n");
                main_instruction();
        }

        /*Nutzerabfragen und Anleitung*/
        nutzer_def = main_instruction();

        if (nutzer_def == -1) {
                printf("Programm wird beendet.\n");
                flush_buff();
                destroy(matrix);
                return 0;
        }

        /*Programmerstellte Matrix*/
        while (nutzer_def == 0) {
                x = programm_defined(matrix);
                if (x == 2) {
                        continue;
                } else if (x == 1){
                        nutzer_def = 3;
                } else if (x == 0){
                        printf("Programm wird beendet.\n");
                        flush();
                        destroy(matrix);
                        return 0;
                }

        }

        /*Nutzerdefinierte Matrix*/
        while (nutzer_def == 1) {
                /*printf("Definition der Matrix per Textdatei:\n");
                x = text_defined(&matrix);*/
                printf("Fuer Definition der Matrix per Textdatei, geben Sie t ein, fuer Definition durch manuelle Eingabe, geben Sie m ein.\n");
                c = getchar();

                if (c == 't' && !flush()) {
                        x = text_defined(&matrix);
                } else if (c == 'm' && !flush()){
                        printf("\nGeben Sie die Zellen, die Sie beleben moechten in der Form \nZeile,Spalte \nein.\nBeispiel: \t17,12\n"
                        "Achten Sie darauf, dass Sie sich ihre Zahlen fuer die Zeilen zwischen 1 und %i und ihre Zahlen fuer die Spalten zwischen 1 und %i befinden, da es andernfalls nicht so aussieht, wie sie es wollten.\n", ROW, COL);
                        printf("Sollte die Zahl einstellig sein, dann stellen Sie bitte eine 0 voran (z.B.: 01).\n");
                        printf("Geben Sie immer nur eine Zelle auf einmal ein!\n");
                        printf("Um dem Programm zu zeigen, dass sie fertig sind, geben sie f ein.\n");
                        printf("Wenn Sie das Programm komplett beenden moechten, geben Sie x ein.\n");
                        printf("\n\n");
                        while (u == -1 || u == 1) {
                                printf("Neue Eingabe: ");
                                status = scanf("%s", input);
                                if (status == EOF) {
                                        printf("Fehler beim Einlesen\n");
                                        nutzer_def = main_instruction();
                                        continue;
                                }
                                u = user_defined(&matrix, input);

                                if (u == 0) {
                                        flush();
                                        break;
                                } else if (u == 2) {
                                        x = 1;
                                        printf("Eingabe abgeschlossen\n");
                                        flush();
                                        break;
                                } else if (u == 3) {
                                        printf("Programm wird beendet.\n");
                                        destroy(matrix);
                                        return 0;
                                }
                        }
                } else {
                        flush();
                        printf("\nFehlerhafte Eingabe\n");
                }
                nutzer_def = 3;
                /*falls Definition durch Nutzer fehlschlaegt*/
                flush();
                if (x == 0) {
                        nutzer_def = main_instruction();
                }
        }

        /*Abbruch des Programms*/
        if (nutzer_def == -1) {
                printf("Programm wird beendet.\n");
                flush_buff();
                destroy(matrix);
                return 0;
        }

        /*Programmerstellte Matrix*/
        while (nutzer_def == 0) {
                x = programm_defined(matrix);
                if (x == 2) {
                        continue;
                } else if (x == 1){
                        nutzer_def = 3;
                } else if (x == 0){
                        printf("Programm wird beendet\n");
                        flush();
                        destroy(matrix);
                        return 0;
                }
        }

        /*Anfangsgeneration ausgeben*/
        printf("\nAnfangsgeneration:\n\n");
        print(matrix);
        printf("\nGeben Sie Enter ein, um die naechste Generation anzuzeigen.\n");
        printf("Wenn Sie das Programm abbrechen wollen, geben Sie x ein.\n");

        /*Folgegenerationen berechnen und ausgeben*/
        i = 0;
        while (1) {
                c = getchar();
                if (c == '\n'){
                        survivors = gen_berechnen(matrix);
                        /*bei Fehler*/
                        if (survivors == -1) {
                                printf("Programm wird beendet.\n");
                                flush_buff();
                                return 1;
                        } else {
                                printf("\n%i.te Folgegeneration:\n", i + 1);
                                printf("Population: %i\n\n", survivors);
                                print(matrix);
                        }
                        printf("\nGeben Sie Enter ein, um die naechste Generation anzuzeigen.\n");
                        printf("Wenn Sie das Programm abbrechen wollen, geben Sie x ein.\n");
                } else if (c == 'x' && flush() == 0){
                        printf("Programm wird beendet\n");
                        break;
                } else {
                        flush();
                        printf("Falsche Eingabe!\n");
                        printf("\nGeben Sie Enter ein, um die naechste Generation anzuzeigen.\n");
                        printf("Wenn Sie das Programm abbrechen wollen, geben Sie x ein.\n");
                }
                ++i;

        }

        flush_buff();
        destroy(matrix);
        return 0;
}
