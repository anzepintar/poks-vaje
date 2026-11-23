#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, AB = 0, CD = 0, EF = 0, R = 0;

void *fun1(void *arg) {
  int *num = (int *)arg;
  printf("Thread %ld: %d\n", syscall(SYS_gettid), *num);
  AB = A + B;
  return NULL;
}
void *fun2(void *arg) {
  int *num = (int *)arg;
  printf("Thread %ld: %d\n", syscall(SYS_gettid), *num);
  sleep(10); // Simulate some work being done
  CD = C - D;
  return NULL;
}
void *fun3(void *arg) {
  int *num = (int *)arg;
  printf("Thread %ld: %d\n", syscall(SYS_gettid), *num);
  EF = E + F;
  return NULL;
}

int main(void) {
  pthread_t nit1, nit2, nit3;

  A = 1;
  B = 2;
  C = 3;
  D = 4;
  E = 5;
  F = 6;

  pthread_create(&nit1, NULL, fun1, &A);
  pthread_create(&nit2, NULL, fun2, &B);
  pthread_create(&nit3, NULL, fun3, &C);

  pthread_join(nit1, NULL);
  pthread_join(nit2, NULL);
  pthread_join(nit3, NULL);

  printf("AB = %d\n", AB);
  printf("CD = %d\n", CD);
  printf("EF = %d\n", EF);
  printf("Rezultat = %d\n", AB * CD * EF);

  return 0;
}
