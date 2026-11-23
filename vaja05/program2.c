#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

typedef struct {
  int arg1;
  int arg2;
  int *rez;
} thread_data_t;

static void *sum(void *argument) {
  thread_data_t *data = argument;
  *data->rez = data->arg1 + data->arg2;
  printf("Thread %ld: %d\n", syscall(SYS_gettid), *data->rez);
  return 0;
}

static void *minus(void *argument) {
  thread_data_t *data = argument;
  *data->rez = data->arg1 - data->arg2;
  printf("Thread %ld: %d\n", syscall(SYS_gettid), *data->rez);
  return 0;
}

int main(void) {
  printf("Main: %ld\n", syscall(SYS_gettid));

  const int A = 1;
  const int B = 2;
  const int C = 3;
  const int D = 4;
  const int E = 5;
  const int F = 6;

  int AB;
  int CD;
  int EF;

  pthread_t thread_ab;
  pthread_t thread_cd;
  pthread_t thread_ef;

  thread_data_t data_ab = {A, B, &AB};
  thread_data_t data_cd = {C, D, &CD};
  thread_data_t data_ef = {E, F, &EF};

  pthread_create(&thread_ab, NULL, sum, &data_ab);
  pthread_create(&thread_cd, NULL, minus, &data_cd);
  pthread_create(&thread_ef, NULL, sum, &data_ef);

  pthread_join(thread_ab, NULL);
  pthread_join(thread_cd, NULL);
  pthread_join(thread_ef, NULL);

  int rez = AB * CD * EF;

  printf("AB = %d\n", AB);
  printf("CD = %d\n", CD);
  printf("EF = %d\n", EF);
  printf("Rezultat = %d\n", rez);

  return 0;
}
