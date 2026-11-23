/*
Neto letna davčna osnova – nad (€)	Do (€)	Dohodnina (€)	Stopnja / izračun
9.721,43		16 %
9.721,43	28.592,44	1.555,43	+ 26 % nad 9.721,43
28.592,44	57.184,88	6.461,89	+ 33 % nad 28.592,44
57.184,88	82.346,23	15.897,40	+ 39 % nad 57.184,88
82.346,23		25.710,33	+ 50 % nad 82.346,23
*/
#include <stdio.h>

double dohodnina(double osnova) {
    if (osnova <= 0) return 0;
    if (osnova <= 9721.43) return osnova * 0.16;
    if (osnova <= 28592.44) return 1555.43 + (osnova - 9721.43) * 0.26;
    if (osnova <= 57184.88) return 6461.89 + (osnova - 28592.44) * 0.33;
    if (osnova <= 82346.23) return 15897.40 + (osnova - 57184.88) * 0.39;
    return 25710.33 + (osnova - 82346.23) * 0.50;
}

int main(void) {
    double bruto, akontacija, splosna, posebna = 0;
    double osnova, davek, meja[] = {9721.43, 28592.44, 57184.88, 82346.23};
    int student, meseci;

    printf("Letni bruto zasluzek (€): ");
    if (scanf("%lf", &bruto) != 1 || bruto < 0) return 1;

    printf("Imas pravico do posebne studentske olajsave? (1-da, 0-ne): ");
    scanf("%d", &student);

    printf("Koliko mesecev te starsi uveljavljajo? (0-12): ");
    scanf("%d", &meseci);

    printf("Placana akontacija dohodnine (€): ");
    scanf("%lf", &akontacija);

    if (student) posebna = 3886.35;

    splosna = bruto <= 17766.18
        ? 5551.93 + 20832.39 - 1.17259 * bruto
        : 5551.93;

    if (meseci < 0 || meseci > 12 || akontacija < 0) {
        printf("Napacen vnos.\n");
        return 1;
    }

    splosna *= (12 - meseci) / 12.0;
    osnova = bruto * 0.90 - splosna - posebna;
    if (osnova < 0) osnova = 0;

    davek = dohodnina(osnova);

    printf("\nDavcna osnova: %.2f €\n", osnova);
    printf("Ocenjena dohodnina: %.2f €\n", davek);
    printf("%s: %.2f €\n",
           davek >= akontacija ? "Doplacilo" : "Mozno vracilo",
           (davek >= akontacija ? davek - akontacija : akontacija - davek));

    int i;
    for (i = 0; i < 4 && osnova >= meja[i]; i++);

    if (i < 4)
        printf("Do naslednjega razreda manjka %.2f € davcne osnove.\n",
               meja[i] - osnova);
    else
        printf("Nahajas se v najvisjem davcnem razredu.\n");

    return 0;
}