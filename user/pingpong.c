#include <stddef.h>
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
    char *receive = (char *)malloc(sizeof(char) * 4);
    char *send = "pong";
    read(pip[0], receive, 4);
    printf("%d: received %s\n", getpid(), receive);
    write(pip[1], send, 4);
  }
  else
  {
    // parent
    char *receive = (char *)malloc(sizeof(char) * 4);
    char *send = "ping";
    write(pip[1], send, 4);
    wait(NULL);
    read(pip[0], receive, 4);
    printf("%d: received %s\n", getpid(), receive);
  }

  exit(0);
}