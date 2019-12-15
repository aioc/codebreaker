/*
 * Solution Template for RPS
 * 
 * Australian Informatics Olympiad 2019
 * 
 * This file is provided to assist with reading and writing of the input
 * files for the problem. You may modify this file however you wish, or
 * you may choose not to use this file at all.
 */

#include <cstdio>

/* N is the number of rounds contested. */
int N;

/*
 * Ra, Pa and Sa are the number of times your opponent will throw rock, paper,
 * and scissors, respectively.
 */
int Ra;
int Pa;
int Sa;

/*
 * Rb, Pb and Sb are the number of times you will throw rock, paper, and
 * scissors, respectively.
 */
int Rb;
int Pb;
int Sb;

int answer;

int main(void) {
    /* Read the value of N from the input file.  */
    scanf("%d", &N);

    /* Read the value of Ra, Pa and Sa from the input file.  */
    scanf("%d%d%d", &Ra, &Pa, &Sa);

    /* Read the value of Rb, Pb and Sb from the input file.  */
    scanf("%d%d%d", &Rb, &Pb, &Sb);

    /*
     * TODO: This is where you should compute your solution. Store the answer
     * (the maximum number of points you could score after N rounds have been
     * played) in the variable answer.
     */

    // Nine cases, one for each possible pairing of throws
    int score = 0;
    while (Rb && Sa) {
        Rb--;
        Sa--;
        score++;
        N--;
    }

    while (Pb && Ra) {
        Pb--;
        Ra--;
        score++;
        N--;
    }

    while (Sb && Pa){
        Sb--;
        Pa--;
        score++;
        N--;
    }

    while (Rb && Ra) {
        Rb--;
        Ra--;
        N--;
    }

    while (Pb && Pa) {
        Pb--;
        Pa--;
        N--;
    }

    while (Sb && Sa) {
        Sb--;
        Sa--;
        N--;
    }

    while (Rb && Pa) {
        Rb--;
        Pa--;
        N--;
    }

    while (Pb && Sa) {
        Pb--;
        Sa--;
        score--;
        N--;
    }

    while (Sb && Ra) {
        Sb--;
        Ra--;
        score--;
        N--;
    }

    answer = score;

    /* Write the answer to the output file. */
    printf("%d\n", answer);

    return 0;
}
