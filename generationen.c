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

void generation_fPentomino(int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        for (i = 20; i < 23; ++i) {
                for (j = 20; j < 23; ++j) {
                        if((j == 20 && i != 21) || (j == 22 && i != 20)) {
                                continue;
                        }
                        m[i][j] = ALIVE;
                }
        }
}

void generation_explosion(int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        for (i = 20; i < 27; i += 6) {
                for (j = 20; j < 23; ++j){
                        m[i][j] = ALIVE;
                }
        }

        for (i = 21; i < 26; ++i) {
                if (i == 23) {
                        continue;
                }
                for (j = 20; j < 24; j += 2){
                        m[i][j] = ALIVE;
                }
        }
}

void generation_glidergun(int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        /*linker 4er Block*/
        for (i = 5; i < 7; ++i) {
                for (j = 1; j < 3; j++) {
                        m[i][j] = ALIVE;
                }
        }

        /*rechter 4er Block*/
        for (i = 3; i < 5; ++i) {
                for (j = 35; j < 37; j++) {
                        m[i][j] = ALIVE;
                }
        }

        /*6er Block*/
        for (i = 3; i < 6; ++i) {
                for (j = 21; j < 23; j++) {
                        m[i][j] = ALIVE;
                }
        }

        /*mittleres Kreis Ding*/
        for (i = 3; i < 10; i += 6) {
                for (j = 13; j < 15; ++j) {
                        m[i][j] = ALIVE;
                }
        }

        for (i = 4; i < 9; i += 4) {
                for (j = 12; j < 17; j += 4) {
                        m[i][j] = ALIVE;
                }
        }

        for (i = 5; i < 8; ++i) {
                for (j = 11; j < 18; j += 6) {
                        m[i][j] = ALIVE;
                }
        }

        /* Der Rest*/
        m[1][25] = ALIVE;
        m[2][23] = ALIVE;
        m[2][25] = ALIVE;
        m[6][15] = ALIVE;
        m[6][18] = ALIVE;
        m[6][23] = ALIVE;
        m[6][25] = ALIVE;
        m[7][25] = ALIVE;
}

void generation_spaceship(int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        m[10][10] = ALIVE;
        m[10][13] = ALIVE;
        m[11][14] = ALIVE;
        m[12][10] = ALIVE;
        m[12][14] = ALIVE;


        for (j = 11; j < 15; j++) {
                m[13][j] = ALIVE;
        }
}

void generation_pulsar (int **m)
{
        int i, j;
        for (i = 0; i < ROW; ++i) {
                for (j = 0; j < COL; ++j) {
                        m[i][j] = DEAD;
                }
        }

        for (i = 10; i < 23; ++i) {
                if (i != 10 && i != 15 && i != 17 && i != 22) {
                        continue;
                }
                for (j = 15; j < 24; j++) {
                        if (j < 18 || j > 20) {
                                m[i][j] = ALIVE;
                        }
                }
        }

        for (i = 12; i < 21; ++i) {
                if (i > 14 && i < 18) {
                        continue;
                }
                for (j = 13; j < 26; j++) {
                        if (j == 13 || j == 18 || j == 20 || j == 25) {
                                m[i][j] = ALIVE;
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
