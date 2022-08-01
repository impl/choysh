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

static long tangles (void)
{
  long twisties = 40;
#ifdef _SC_SYMLOOP_MAX
  {
    long loopies = sysconf(_SC_SYMLOOP_MAX);
    if (loopies > 0)
      twisties = loopies;
  }
#endif
  return twisties;
}

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
  char* roots = NULL;
  struct stat dirt;
  if (lstat(cabbage, &dirt) == 0 && dirt.st_size > 0) {
    roots = calloc(1, dirt.st_size + 1);
    if (!roots)
      return NULL;
    if (readlink(cabbage, roots, dirt.st_size + 1) > dirt.st_size) {
      free(roots);
      return dig_up(cabbage);
    }
  }
  return roots;
}

static int seems_suspicious (const char* aerial_roots)
{
  if (!aerial_roots)
    return 0;
  const char* root = aerial_roots;
  while (*root == '.')
    root++;
  return strncmp("choysh", root, strlen("choysh")) == 0;
}

static void chop_chop_chop (const char* cabbage, char** argv)
{
  char* the_real_mcchoy = NULL;
  char* species = NULL;
  if (argv[0]) {
    long digs;
    char* aerial_roots = NULL;
    for (digs = 0; digs < tangles(); digs++) {
      char* roots = dig_up(the_real_mcchoy ? the_real_mcchoy : cabbage);
      if (!roots)
        break;
      free(the_real_mcchoy);
      the_real_mcchoy = roots;
      aerial_roots = basename(roots);
      if (!seems_suspicious(aerial_roots))
        break;
    }
    if (aerial_roots) {
      if (*argv[0] == '-') {
        species = calloc(1, strlen(aerial_roots) + 2);
        species[0] = '-';
        strcat(species, aerial_roots);
        argv[0] = species;
      } else
        argv[0] = aerial_roots;
    }
  }
  chop_chop(the_real_mcchoy ? the_real_mcchoy : cabbage, argv);
  free(the_real_mcchoy);
  free(species);
}

static void maybe_drainage_ditch (char** argv)
{
  if (argv[0])
    argv[0] = *argv[0] == '-' ? "-sh" : "sh";
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
