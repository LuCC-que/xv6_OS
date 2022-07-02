#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <dirent.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
  if (argc > 3)
  {
    printf("input arguments can't more than 3\n");
    exit(1);
  }
  else if (argc < 3)
  {
    printf("input arguments must be 3\n");
    exit(1);
  }

  char *add = argv[1];
  DIR *dir;
  struct dirent *ent;
  if ((dir = open(add)) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      printf("%s\n", ent->d_name);
    }
  }

  exit(0);
}