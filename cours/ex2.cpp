#include <cstdio>
#include <omp.h>
#include <unistd.h>
#include <vector>

int calcul2()
{
  sleep(2);
  return 2;
}
int calcul3()
{
  sleep(3);
  return 3;
}

int calcul4()
{
  sleep(4);
  return 4;
}

int main()
{
  std::vector<int> A(100000, 0); 
  int k = 0;

#pragma omp parallel num_threads(2) default(none) shared(k, A)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    printf("Hello je suis %d/%d\n", thid, numth);
#pragma omp for reduction(+:k)
    for (int i = 0; i < 100000; i++) {
      A[i] = i;
      k++;
    }
  }

  printf("%d\n", k);

  return 0;
}
