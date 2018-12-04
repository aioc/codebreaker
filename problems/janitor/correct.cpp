/*
 * Solution Template for Janitor
 * 
 * Australian Informatics Olympiad 2018
 * 
 * This file is provided to assist with reading and writing of the input
 * files for the problem. You may modify this file however you wish, or
 * you may choose not to use this file at all.
 */

#include <cstdio>

/* R is the number of rows of tiles */
int R;
/* C is the number of columns of tiles */
int C;
/* Q is the number of tile replacements */
int Q;
int grid[11][100005];
int row_updates[100005];
int col_updates[100005];
int height_updates[100005];
int d_row[4];
int d_col[4];
int answer;
int is_local_max;

int main(void) {
    /* Open the input and output files. */
    FILE *input_file = stdin;
    FILE *output_file = stdout;

    /* Read the values of R, C and Q from the input file.  */
    fscanf(input_file, "%d%d%d", &R, &C, &Q);

    /* Read in information about initial heights of the tiles */
    for (int rv = 0; rv < R; rv++) {
        for (int i = 0; i < C; i++) {
            fscanf(input_file, "%d", &grid[rv][i]);
        }
    }
    for (int qv = 0; qv < Q; qv++) {
        fscanf(input_file, "%d%d%d", &row_updates[qv], &col_updates[qv],
                &height_updates[qv]);
    }

    d_row[0] = 0;
    d_col[0] = 1;
    d_row[1] = 1;
    d_col[1] = 0;
    d_row[2] = 0;
    d_col[2] = -1;
    d_row[3] = -1;
    d_col[3] = 0;
    answer = 0;
    for (int rv = 0; rv < R; rv++) {
        for (int cv = 0; cv < C; cv++) {
            is_local_max = 1;
            for (int d = 0; d < 4; d++) {
                int dr = rv + d_row[d];
                int dc = cv + d_col[d];
                if ((dr >= 0) && (dr < R) && (dc >= 0) && (dc < C)) {
                    int adj_value = grid[dr][dc];
                    int sqr_value = grid[rv][cv];
                    if (adj_value > sqr_value) {
                        is_local_max = 0;
                    }
                }
            }
            if (is_local_max == 1) {
                answer = answer + 1;
            }
        }
    }
    /* Write the answer to the output file. */
    fprintf(output_file, "%d\n", answer);

    for (int qv = 0; qv < Q; qv++) {
        int rv = row_updates[qv] - 1;
        int cv = col_updates[qv] - 1;
        int h = height_updates[qv];
        int prev_local_maxes = 0;
        int new_local_maxes = 0;
        int csquaremax = 1;
        for (int d = 0; d < 4; d++) {
            int dr = rv + d_row[d];
            int dc = cv + d_col[d];
            if ((dr >= 0) && (dr < R) && (dc >= 0) && (dc < C)) {
                int adj_value = grid[dr][dc];
                int sqr_value = grid[rv][cv];
                if (adj_value > sqr_value) {
                    csquaremax = 0;
                }
                int csquaremax2 = 1;
                for (int d2 = 0; d2 < 4; d2++) {
                    int dr2 = dr + d_row[d2];
                    int dc2 = dc + d_col[d2];
                    if ((dr2 >= 0) && (dr2 < R) && (dc2 >= 0) && (dc2 < C)) {
                        int adj_value2 = grid[dr2][dc2];
                        int sqr_value2 = grid[dr][dc];
                        if (adj_value2 > sqr_value2) {
                            csquaremax2 = 0;
                        }
                    }
                }
                if (csquaremax2 == 1) {
                    prev_local_maxes = prev_local_maxes + 1;
                }
            }
        }
        if (csquaremax == 1) {
            prev_local_maxes = prev_local_maxes + 1;
        }
        grid[rv][cv] = h;
        csquaremax = 1;
        for (int d = 0; d < 4; d++) {
            int dr = rv + d_row[d];
            int dc = cv + d_col[d];
            if ((dr >= 0) && (dr < R) && (dc >= 0) && (dc < C)) {
                int adj_value = grid[dr][dc];
                int sqr_value = grid[rv][cv];
                if (adj_value > sqr_value) {
                    csquaremax = 0;
                }
                int csquaremax2 = 1;
                for (int d2 = 0; d2 < 4; d2++) {
                    int dr2 = dr + d_row[d2];
                    int dc2 = dc + d_col[d2];
                    if ((dr2 >= 0) && (dr2 < R) && (dc2 >= 0) && (dc2 < C)) {
                        int adj_value2 = grid[dr2][dc2];
                        int sqr_value2 = grid[dr][dc];
                        if (adj_value2 > sqr_value2) {
                            csquaremax2 = 0;
                        }
                    }
                }
                if (csquaremax2 == 1) {
                    new_local_maxes = new_local_maxes + 1;
                }
            }
        }
        if (csquaremax == 1) {
            new_local_maxes = new_local_maxes + 1;
        }
        answer = answer - prev_local_maxes + new_local_maxes;
        /* Write the answer to the output file. */
        fprintf(output_file, "%d\n", answer);
    }

    /* Finally, close the input/output files. */
    fclose(input_file);
    fclose(output_file);

    return 0;
}
