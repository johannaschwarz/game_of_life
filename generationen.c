#include "generationen.h"

void random_generation(int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        if ((rand() % 6) == 0) {
                                m[i][j] = ALIVE;
                        } else {
                                m[i][j] = DEAD;
                        }
                }
        }
}

void generation_toad(int **m)
{
        int i, j, n = 7;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        for (i = 7; i < 9; ++i) {
                for (j = n; j < (n + 3); ++j) {
                        m[i][j] = ALIVE;
                }
                --n;
        }
}
