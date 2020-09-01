/*
 *
 * Hello world!
 *
 */

#include <stdio.h>
#include <stdlib.h>

void funzione(int *);

void funzione(int *x) { (*x)++; }

void elabora(int *pi) {
  pi[0] = 1;
  pi[1] = 2;
  pi[2] = 3;
}

void elaboraDifferent(int vect[]) {
  vect[0] = 12;
  vect[1] = 123;
  vect[2] = 1234;
}

int main(void) {

  // declarations
  int iValorized;
  iValorized = 5;
  const float fPi = 3.14159265;

  printf("%f \n", fPi);

  printf("n %d\n", iValorized);
  printf("n++ %d\n", iValorized++);
  printf("++n %d\n", ++iValorized);
  printf("n-- %d\n", iValorized--);
  printf("--n %d\n", --iValorized);

  printf("+n %d\n", +iValorized);
  printf("-n %d\n", -iValorized);

  int iValorized2 = 14 % 3;

  printf("n2 %d\n", iValorized2);
  printf("n+n2 %d\n", iValorized + iValorized2);
  printf("n-n2 %d\n", iValorized - iValorized2);
  printf("n/n2 %d\n", iValorized / iValorized2);
  printf("n%%n2 %d\n", iValorized % iValorized2);

  iValorized += iValorized2;
  printf("n+=n2 %d\n", iValorized);

  iValorized -= iValorized2;
  printf("n-=n2 %d\n", iValorized);

  iValorized *= iValorized2;
  printf("n*=n2 %d\n", iValorized);

  iValorized /= iValorized2;
  printf("n/=n2 %d\n", iValorized);

  printf("n==n2 %d \n", iValorized == iValorized2);

  printf("n!=n2 %d \n", iValorized != iValorized2);

  printf("n<n2 %d \n", iValorized < iValorized2);

  printf("n>n2 %d \n", iValorized > iValorized2);

  printf("n<=n2 %d \n", iValorized <= iValorized2);

  printf("n>=n2 %d \n", iValorized >= iValorized2);

  int bVal = 0;
  int bVal2 = 1;

  printf("b %d \n", bVal);

  printf("!b %d \n", !bVal);

  printf("b && b2 %d \n", bVal && bVal2);

  printf("b || b2 %d \n", bVal || bVal2);

  int iValorized3 = (bVal++ && --bVal2) ? iValorized : iValorized2;

  printf("n3 %d \n", iValorized3);

  /*
   * Ci sono altri operatori logici binari:
   *   * op1 & op2 AND bit a bit
   *   * op1 | op2 OR bit a bit
   *   * op1 ^ op2 XOR bit a bit
   *   * op1 << op2 spostamento a sinistra di op2 bit
   *   * op1 >> op2 spostamento a destra di op2 bit
   *   * ~op1 completamento a 1
   *   * op1 &= op2
   *   * op1 |= op2
   *   * op1 ^= op2
   *   * op1 <<= op2
   *   * op1 >>= op2
   *   * op1 ~= op2
   */

  printf("5/4 = %d \n", 5 / 4);

  printf("5.0/4.0 = %f \n", 5.0 / 4.0);

  printf("(cast)(5/4) = %f \n", (double)(5 / 4));

  printf("(cast)5/4 = %f \n", (double)5 / 4);

  iValorized = iValorized2, iValorized2 = ++iValorized3;

  printf("n, n2 %d, %d \n", iValorized, iValorized2);

  int count = 0;

  printf("start \n");

label:

  count++;

  printf("counter at %d \n", count);

  switch (count) {
  case 1:
    goto label;
  case 2:
    goto label;
  case 3:
    goto stop;
  case 4:
    printf("Something happened with counter at %d \n", count);
    break;
  case 5:
    printf("Counter at %d \n", count);
    break;
  }

stop:
  printf("cycle stops at %d \n", count);

  if (count < 5) {
    goto label;
  }

  while (count <= 8) {
    count++;
    if (count == 7) {
      printf("It stops with 7 \n");
      break;
    } else {
      printf("It continue != 7 \n");
      continue;
    }
    goto label;
  }

  for (int i = 0; i < 10; i += 2) {
    printf("Cycle at %d\n", i);
  }

  for (int i = 0; i < 20; ++i, printf("%d \n", i % 3))
    ;

  // classi di memorizzazione
  auto int automatic_int;    // è la classe di default
  register int register_int; // la variabile viene posta come registro del
                             // microprocessore accesso veloce, ma sconsigliato
                             // l'utilizzo
  static int static_int; // se dichiarata in campo globale allora accessibile
                         // solo nel file in cui è dichiarata, se dichiarata in
                         // campo locale a una funzione mantiene il suo valore
                         // tra una chiamata e l'altra della funzione
  extern int extern_int; // se si ha necessità di accedere alla variabile al di
                         // fuori del sorgente

  printf("Inserisci un numero: ");
  scanf("%d", &iValorized);
  printf("Hai inserito %d\n", iValorized);

  float fValorized;

  printf("Puoi inserire un numero e poi un altro: ");
  scanf("%d%f", &iValorized, &fValorized);
  printf("Hai inserito 2 valori: %d, %f\n", iValorized, fValorized);

  printf("Copio input su output ed elimino gli spazi (usa | per uscire o q per "
         "quittare)");

  int c;
  while ((c = getchar()) != EOF) {
    if (c == '|') {
      break;
    } else if (c == 'q') {
      exit(EXIT_FAILURE);
    } else if (c != ' ') {
      putchar(c);
    }
  }

  int *p = &c;
  printf("Valore di c: %d\n", c);
  *p = 10;
  printf("Valore di c dopo modifica con puntatore: %d\n", c);

  printf("Provo a fare il passaggio di parametri con puntatore\n");
  funzione(&c);
  printf("Se va bene dovrebbe essere incrementato c di 1: %d\n", *&c);

  int a[7]; // dichiarazione di un array

  a[1] = 123; // assegnazione di 123 al secondo elemento dell'array

  int b[] = {123, 456, 789, 0, 55}; // dichiarazione di un array

  for (int i = 0; i < 7; i++) {
    a[i] = (i ^ 2) / 3;
  }

  for (int j = 6; j >= 0; j--) {
    printf("a[%d]=%d\n", j, a[j]);
    a[j] = (j ^ 3) / 2;
    printf("a[%d]=%d\n", j, a[j]);
  }

  int *pi;
  pi = a;

  printf("*pi = %d\n", *pi);

  pi++;

  printf("*pi = %d\n", *pi);

  a[1] = 12;

  printf("*pi = %d\n", *pi);

  pi = a;

  pi--;
  pi--;
  pi--;
  pi--;
  pi--;
  pi--;
  pi--;
  pi--;

  printf("*pi = %d\n", *pi);

  pi = a;

  for (int i = 0; i < 7; i++) {
    printf("a[%d]=%d\n", i, *(pi + i));
  }

  int multi[2][3];

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("multi[%d][%d]=%d\n", i, j, *((*(multi + i)) + j));
    }
  }

  for (int i = 0; i < 7; i++) {
    printf("a[%d]=%d\n", i, *(pi + i));
  }

  printf("Elaboro a\n");
  elabora(a);

  for (int i = 0; i < 7; i++) {
    printf("a[%d]=%d\n", i, *(pi + i));
  }

  printf("Elaboro a different\n");
  elaboraDifferent(a);

  for (int i = 0; i < 7; i++) {
    printf("a[%d]=%d\n", i, *(pi + i));
  }

  exit(EXIT_SUCCESS);

  return 1;
}
