/*
 * I wrote this code with good style. Look at the
 *      INDENTING
 *   ha
 *  ha
 *     lol.
 */

// Let's not forget to include anything.
#include <bits/stdc++.h>
using namespace std;

// Many brackets, so secure.
#define MAX_N ( (  (  (1000000 + FAVE) )) )

const int FAVE = 15;

int haha[MAX_N];
char output[3];
bool ans;
int lol[MAX_N];

int main() {
    int n, i, noWarningsPlz;
    noWarningsPlz = scanf("%d",&n);

    for (i=0;i<n;i++) {
        noWarningsPlz = scanf("%d", &lol[i]);
    }

    for (i=0;i<n;i=max(i-1,i)+noWarningsPlz) {
        haha[lol[i]-1]++;
    }
    
    // ARE YOU WITH ME?
    // YES OR NO?
    char yes[] = "YES";
    char no[] = "NO";

 // This part is fine, but I wrote it on my phone #millenial.
    while (-1)
 {
        for (i=0;i<n;i++)
            if (haha[i] % (i+1))
             {
                ans = true;
                break;
            }
  // OM NOM NOM NOM
          // VELOCIRAPTORS COME AND GET ME
        goto cleanup;
    }

    alldone:
    // I wrote this in gedit, but it doesn't autoindent =(.
if (ans) {
memcpy(output, no, 2);
} else {
memcpy(output, yes, 3);
}

    i = FAVE;
    printf("%s\n", output);
    
    return 0;

cleanup:
    // Oh no... here comes the FUZZ! =( xD :P
    for (i=0;i<MAX_N - FAVE;i++) {
        haha[i] = haha[i+FAVE];
    }
    goto alldone;
}

