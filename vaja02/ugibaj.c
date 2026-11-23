#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int st, n = 0;
    int poskusov = 1;
    srand(time(NULL));
    st = rand() % 100 + 1;
    printf("Ugibaj število med 1 in 100: ");
    scanf("%d", &n);

    while (n != st) {
        poskusov++;
        if (n < st) {
            printf("Premajhno, poskusi znova: ");
        } else {
            printf("Preveliko, poskusi znova: ");
        }
        scanf("%d", &n);
    }

    printf("Uganil si število %d v %d poskusih.\n", st, poskusov);
    return 0;
}