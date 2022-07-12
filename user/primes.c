#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int *fd)
{
  int p, d;
  close(fd[1]);
  // read one value
  if (read(fd[0], (void *)&p, sizeof(p)) != sizeof(p))
  {
    fprintf(2, "Read fail!\n");
    exit(1);
  }
  // print it out
  printf("prime %d\n", p);

  if (read(fd[0], (void *)&d, sizeof(d)))
  {
    int fd1[2];
    pipe(fd1);
    if (fork() == 0)
    {
      // child call the function again
      primes(fd1);
    }
    else
    {
      close(fd1[0]);
      do
      {
        if (d % p != 0)
        {
          write(fd1[1], (void *)&d, sizeof(d));
        }
      } while (read(fd[0], (void *)&d, sizeof(d)));

      // close file desciptor, save resource for child
      close(fd[0]);
      close(fd1[1]);
      wait(0);
    }
  }
  exit(0);
}

int main(int argc, char *argv[])
{
  int fd[2];
  int start = 2;
  int end = 35;
  pipe(fd);
  if (fork() == 0)
  {
    // child
    primes(fd);
  }
  else
  {
    close(fd[0]);
    for (int i = start; i <= end; i++)
    {
      // file descriptors are not neccassarily files.
      if (write(fd[1], (void *)&i, sizeof(i)) != 4)
      {
        fprintf(2, "Write fail!\n");
        exit(1);
      }
    }
    close(fd[1]);
    wait(0);
  }

  exit(0);
}