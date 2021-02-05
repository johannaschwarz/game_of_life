#include "benutzereingaben.h"
#include "funktionen.h"
#include "generationen.h"



/*eventuell in benutzereingaben user_defined löschen*/

int main (void)
{
        /*Variablen anlegen*/
        int **matrix;
        int nutzer_def, x, i = 0, c, survivors = 0;
        srand(time(NULL));

        /*Speicher fuer die Matrix reservieren*/
        matrix = int_init();

        if (matrix == NULL) {
                printf("\nSpeicherfehler\n");
                main_instruction();
        }

        /*Nutzerabfragen und Anleitung*/
        nutzer_def = main_instruction();

        if (nutzer_def == -1) {
                printf("Programm wird abgebrochen.\n");
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
                        return 0;
                }

        }

        /*Nutzerdefinierte Matrix*/
        while (nutzer_def == 1) {
                printf("Definition der Matrix per Textdatei:\n");
                x = text_defined(&matrix);
                /*printf("Fuer Definition der Matrix per manueller Eingabe, geben Sie 2x Enter ein.\n");*/
                /*c = getchar();
                if (c == 't') {
                        flush();
                        x = text_defined(&matrix);
                } else {
                        flush();
                        x = user_defined(&matrix);
                }*/
                /*falls Definition durch Nutzer fehlschlaegt*/
                nutzer_def = 3;
                if (x == 0) {
                        flush();
                        nutzer_def = main_instruction();
                }
        }

        /*Abbruch des Programms*/
        if (nutzer_def == -1) {
                printf("Programm wird abgebrochen.\n");
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
                } else if (c == 'x'){
                        flush();
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
