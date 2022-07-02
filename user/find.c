#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *fmtname(char *path)
{
  char *p;

  for (p = path + strlen(path); p >= path && *p != '/'; --p)
    ;
  ++p;

  printf("the final p is %s\n", p);
  return p;
}

void find(char *path, char *filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    printf("Fail to open %s\n", path);
    exit(1);
  }

  if (fstat(fd, &st) < 0)
  {
    printf("Fail to stat %s\n", path);
    close(fd);
    exit(1);
  }

  switch (st.type)
  {
  case T_FILE:
    printf("%s %d %d %u", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while (read(fd, &de, sizeof(de)))
    {
      if (!de.inum || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0)
      {
        printf("ls: cannot stat %s\n", buf);
        continue;
      }

      if (st.type == T_FILE)
      {
        if (!strcmp(de.name, filename))
          printf("%s\n", buf);
      }
      else if (st.type == T_DIR)
      {
        find(buf, filename);
      }
    }

    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    find(".", argv[1]);
  }
  else if (argc == 3)
  {
    find(argv[1], argv[2]);
  }
  else
  {
    printf("Input arguments must be 3 or 2\n");
    exit(1);
  }

  // argv[1] is path
  // argv[2] is filename

  exit(0);
}