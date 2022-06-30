#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  // printf("%s", "hello\n");
  if (argc > 2)
  {
    printf("there should be only one input!\n");
  }
  else if (argc < 2)
  {
    printf("there should be at least one input\n");
  }
  else if (!atoi(argv[1]))
  {
    printf("input must be number!\n");
  }
  else
  {
    int duration = atoi(argv[1]);
    printf("Sleeping for %d ms\n", duration);
    sleep(duration);
  }

  exit(0);
}