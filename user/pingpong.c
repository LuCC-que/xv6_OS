#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
  printf("hello, ping pong\n");

  int pip[2];
  if (pipe(pip) == -1)
  {
    printf("fail to create pip\n");
    exit(1);
  }

  int rc = fork();

  if (rc < 0)
  {
    printf("fail to create child\n");
    exit(1);
  }
  else if (rc == 0)
  {
    // child
  }
  else
  {
    // parent
  }

  exit(0);
}