#include "benutzereingaben.h"
#include "funktionen.h"
#include "generationen.h"

int main (void)
{
        /*Variablen anlegen*/
        int **matrix, **m;
        int nutzer_def, x, i = 0, c, survivors = 0;
        srand(time(NULL));

        /*Speicher fuer die Matrix reservieren*/
        matrix = int_init();
        m = int_init();

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

        /*Randomisierte Matrix*/
        if (nutzer_def == 0) {
                printf("Fuer eine zufaellig generierte Anfangsgeneration, geben Sie 1 ein."
                "\nFuer eine interessante, vordefinierte Anfangsgeneration, geben Sie 2 (toad) oder "
                "3 (pulsar) oder 4 (spaceship) oder 5 (glidergun) oder 6 (explosion) ein.\n");
                c = getchar();
                if (c == '1') {
                        random_generation(matrix);
                } else if (c == '2') {
                        generation_toad(matrix);
                } else if (c == '3') {
                        generation_pulsar(matrix);
                } else if (c == '4') {
                        generation_spaceship(matrix);
                } else if (c == '5') {
                        generation_glidergun(matrix);
                } else if (c == '6') {
                        generation_explosion(matrix);
                }

                nutzer_def = 3;
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
        if (nutzer_def == -1) {
                printf("Programm wird abgebrochen.\n");
                flush_buff();
                destroy(matrix);
                return 0;
        }

        /*Randomisierte Matrix*/
        if (nutzer_def == 0) {
                flush();
                random_generation(matrix);
        }

        /*Anfangsgeneration ausgeben*/
        printf("\nAnfangsgeneration:\n\n");
        print(matrix);
        printf("\nGeben Sie Enter ein, um die naechste Generation anzuzeigen.\n");
        printf("Wenn Sie das Programm abbrechen wollen, geben Sie x ein.\n");
        flush();

        /*Folgegenerationen berechnen und ausgeben*/
        i = 0;
        while (1) {
                c = getchar();
                if (c == '\n'){
                        /*m = */
                        survivors = gen_berechnen(matrix);
                        /*bei Fehler*/
                        if (survivors == -1) {
                                printf("Programm wird beendet.\n");
                                flush_buff();
                                return 1;
                        } else {
                                /*matrix = m;*/
                                printf("\n%i.te Folgegeneration:\n", i + 1);
                                printf("Population: %i\n\n", survivors);
                                print(matrix);
                        }
                        printf("\nGeben Sie Enter ein, um die naechste Generation anzuzeigen.\n");
                        printf("Wenn Sie das Programm abbrechen wollen, geben Sie x ein.\n");
                } else if (c == 'x'){
                        flush();
                        break;
                }
                ++i;

        }

        flush_buff();
        destroy(matrix);
        return 0;
}
