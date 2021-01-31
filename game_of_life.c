/*
Benutzereingabe:
        1. möchte Nutzer randomisierte Anfangsgeneration oder Nutzer definierte?
        2.
        randomisierte:
                - srand()
                - rand() % 2 -> entweder 0/1
                -> bei 0: tot (-); bei 1: lebendig(*)
        Nutzer definiert:
                - Ausgabe:      gebe 10 Zeichenketten mit jeweils 10 Zeichen an.
                                die Zeichenketten sollen durch ',' getrennt sein.
                                * steht für lebendige Zelle
                                - steht für tote Zelle
                                andere Zeichen sind nicht erlaubt
                                (*------**,*****----,***----****)
                - Auslesen der Zeichenketten und speichern in raster[][]
        3. wie viele Generationen sollen angezeigt werden? -> int anzahl
                -> große while Schleife um Algorithmus ++anzahl nach jedem printf der Matrize


Algorithmus:
        1. Matrize mit *(42) als lebendige Zelle; -(45) als tote Zelle
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
#include "benutzereingaben.h"
#include "funktionen.h"
#include "generationen.h"

int main (void)
{
        /*Variablen anlegen*/
        int **matrix, **m;
        int nutzer_def, x, i = 0, c;
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
                "\nFuer eine interessante, vordefinierte Anfangsgeneration, geben Sie 2 ein.\n");
                c = getchar();
                if (c == '1') {
                        random_generation(matrix);
                } else if (c == '2') {
                        generation_toad(matrix);
                }
                nutzer_def = 3;
        }

        /*Nutzerdefinierte Matrix*/
        while (nutzer_def == 1) {
                printf("Fuer Definition der Matrix per Textdatei, Druecken sie t.\n");
                printf("Fuer Definition der Matrix per manuelle Eingabe, Druecken sie 2x Enter.\n");
                c = getchar();
                if (c == 't') {
                        flush();
                        x = text_defined(&matrix);
                } else {
                        flush();
                        x = user_defined(&matrix);
                }
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
        printf("\nDruecken Sie Enter, um die naechste Generation anzuzeigen.\n");
        printf("Wenn Sie das Programm abbrechen wollen, druecken Sie x.\n");
        flush();

        i = 0;
        /*Folgegenerationen ausdrucken*/
        while (1) {
                c = getchar();
                if (c == '\n'){
                        m = gen_berechnen(matrix);
                        if (m == NULL) {
                                printf("Programm wird beendet.\n");
                                flush_buff();
                                destroy(matrix);
                                return 0;
                        } else {
                                matrix = m;
                                printf("\n%i.te Folgegeneration:\n\n", i + 1);
                                print(matrix);
                        }
                        printf("\nDruecken Sie Enter, um die naechste Generation anzuzeigen.\n");
                        printf("Wenn Sie das Programm abbrechen wollen, druecken Sie x.\n");
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
