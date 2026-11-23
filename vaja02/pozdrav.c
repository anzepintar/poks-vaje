#include <stdio.h>
int main(int argc, char *argv[]) {
    printf("Vnesi ime: ");
    char ime[100];
    scanf("%s", ime);
    printf("Vnesi starost: ");
    int starost;
    scanf("%d", &starost);
    printf("Pozdravljen %s, ki ima %d let!\n", ime, starost);
    return 0;
}
