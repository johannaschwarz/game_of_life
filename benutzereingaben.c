#include "benutzereingaben.h"

void user_defined(void)
{
        int i, j;
        printf("\nGebe %d Zeichenketten mit jeweils %d Zeichen an.\n", ROW, COL);
        printf("Die Zeichenketten sollen durch ',' getrennt sein.\n");
        printf("Andere Zeichen sind nicht erlaubt.\n");
        printf("Beispiel:\n");
        for (j = 0; j < 2; j++) {
                for (i = 0; i < COL; ++i) {
                        if ((rand() % 2) == 0) {
                                printf("*");
                        } else {
                                printf("-");
                        }
                }
                if (j == 0) {
                        printf(",");
                }
        }
        printf("\n");


}

void main_instruction(void)
{
        printf("\n");
        printf("Das Spielfeld besteht aus %d Zeilen und %d Reihen\n", ROW, COL);
        printf("* steht fuer lebendige Zellen.\n");
        printf("- steht fuer tote Zellen.\n");
        printf("Wollen Sie die Anfangsgeneration selbst definieren? Geben Sie 'y' fuer ja, 'n' fuer nein ein.\n");
}
