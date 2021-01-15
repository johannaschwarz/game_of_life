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

int main (void)
{
        int **matrix;

        srand(time(NULL));
        main_instruction();
        user_defined();

        matrix = init();

        if (matrix == NULL) {
                printf("\nSpeicherfehler\n");
                main_instruction();
        }

        random_generation(matrix);
        print(matrix);
        destroy(matrix);

        return 0;
}
