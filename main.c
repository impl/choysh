// SPDX-FileCopyrightText: 2022 Noah Fontes
//
// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <libgen.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

extern char** environ;

static void chop_chop (const char* the_real_mcchoy, char** argv)
{
  execve(the_real_mcchoy, argv, environ);
  switch (errno) {
  case EACCES:
  case EINVAL:
  case EISDIR:
  case ELIBBAD:
  case ENOENT:
  case ENOEXEC:
  case ENOTDIR:
  case EPERM:
    break;
  default:
    perror("chop chop");
    break;
  }
}

static char* dig_up (const char* cabbage)
{
  char* root = NULL;
  struct stat dirt;
  if (lstat(cabbage, &dirt) == 0 && dirt.st_size > 0) {
    root = calloc(1, dirt.st_size + 1);
    if (!root)
      return NULL;
    if (readlink(cabbage, root, dirt.st_size + 1) > dirt.st_size) {
      free(root);
      return dig_up(cabbage);
    }
  }
  return root;
}

static void chop_chop_chop (char* cabbage, char** argv)
{
  char* root = NULL;
  if (argv[0]) {
    root = dig_up(cabbage);
    argv[0] = basename(root ? root : cabbage);
  }
  chop_chop(cabbage, argv);
  free(root);
}

static void maybe_drainage_ditch (char** argv)
{
  if (argv[0])
    argv[0] = "sh";
  chop_chop("/bin/sh", argv);
}

static void maybe_giant_farm (char** argv)
{
  chop_chop_chop("/etc/choysh", argv);
}

static void maybe_cabbage_patch (char** argv)
{
  const struct passwd* farmer = getpwuid(getuid());
  if (!farmer || !farmer->pw_dir)
    return;
  char* baby_bok_choy = malloc(strlen(farmer->pw_dir) + strlen("/.choysh") + 1);
  if (!baby_bok_choy)
    return;
  strcpy(baby_bok_choy, farmer->pw_dir);
  strcat(baby_bok_choy, "/.choysh");
  chop_chop_chop(baby_bok_choy, argv);
  free(baby_bok_choy);
}

int main (int argc, char** argv)
{
  (void)argc;
  maybe_cabbage_patch(argv);
  maybe_giant_farm(argv);
  maybe_drainage_ditch(argv);
  return 1;
}
