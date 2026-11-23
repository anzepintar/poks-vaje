#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>


int N = 0;
int M = 0;
pthread_mutex_t M_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *stevec(void *argument) {
  for(int i = 0; i<2000; i++){
    int a = N;
    a++;
    usleep(10000);
    N = a;
  }
  printf("Števec N: %ld\n", syscall(SYS_gettid));
  return 0;
}

static void *varenStevec(void *argument) {
  for(int i = 0; i<2000; i++){
    pthread_mutex_lock(&M_mutex);
    int b = M;
    b++;
    usleep(1);
    M = b;
    pthread_mutex_unlock(&M_mutex);
  }
  printf("Varen števec M: %ld\n", syscall(SYS_gettid));
  return 0;
}

int main(void) {
  printf("Main: %ld\n", syscall(SYS_gettid));


  pthread_t nit1, nit2;
  pthread_t nitv1, nitv2;

  pthread_create(&nit1, NULL, stevec, NULL);
  pthread_create(&nit2, NULL, stevec, NULL);
  pthread_create(&nitv1, NULL, varenStevec, NULL);
  pthread_create(&nitv2, NULL, varenStevec, NULL);

  pthread_join(nit1, NULL);
  pthread_join(nit2, NULL);
  pthread_join(nitv1, NULL);
  pthread_join(nitv2, NULL);

  printf("N = %d,\n", N);
  printf("M = %d,\n", M);

  return 0;
}
