#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAX 35;
#define CUR 2;

void fill_array(int *array)
{
  for (int i = 0; i < 35; ++i)
  {
    array[i] = i + 1;
  }
}

int main(void)
{

  printf("primes lab");

  // int pip[2];
  int array[35];
  fill_array(array);

  int pip[2];
  int pip[2];
  if (pipe(pip) == -1)
  {
    printf("fail to create pip\n");
    exit(1);
  }

  exit(0);
}