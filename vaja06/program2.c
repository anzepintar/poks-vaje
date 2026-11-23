#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

void *izpis(void *arg) {
  if(*(int *)arg == 2) {
    nice(10);
  }
  for (int i = 1; i <= 40; i++) {
    fflush(stdout);
    printf("Thread %ld i = %d : ", syscall(SYS_gettid), i);
    for (int j = 0; j < 30; j++) {
    fflush(stdout);
      printf("%d", *(int *)arg);
      usleep(10000);
      fflush(stdout);
    }
    fflush(stdout);
    printf("\n");
    usleep(500000);
  }
  return NULL;
}

int main(void) {
  pthread_t nit1, nit2;

  int a = 1;
  int b = 2;
  pthread_create(&nit1, NULL, izpis, &a);
  pthread_create(&nit2, NULL, izpis, &b);

  pthread_join(nit1, NULL);
  pthread_join(nit2, NULL);

  return 0;
}
