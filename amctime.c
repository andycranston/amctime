/*
 * @(!--#) @(#) amctime.c, version 003, 05-march-2018
 *
 * filter to show any files which have been accessed,
 * modified or had their attributes changes in the last
 * number of seconds
 *
 */

/* #define DEBUG 1 */

/************************************************************************/

/*
 *  includes
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/************************************************************************/

/*
 *  defines
 */

#define MAX_LINE_LENGTH 8000
#define THREE_PLUS_NULL 4
#define DEFAULT_DELTA_IN_SECONDS 60

/************************************************************************/

/*
 *  globals
 */

char *progname;

/************************************************************************/

int main(argc, argv)
  int   argc;
  char *argv[];
{
  struct timespec timenow_ts;
  time_t          timenow;
  double          delta;
  char            line[MAX_LINE_LENGTH + sizeof(char)];
  int             lenline;
  struct stat     stbuf;
  time_t          accesstime;
  time_t          modifiedtime;
  time_t          chmodtime;
  char            amc[THREE_PLUS_NULL];

  progname = argv[0];

  if (argc < 2) {
    delta = DEFAULT_DELTA_IN_SECONDS;
  } else {
    delta = (double)atoi(argv[1]);
  }

#ifdef DEBUG
  printf("Delta=%e seconds\n", delta);
#endif

  if (clock_gettime(CLOCK_REALTIME, &timenow_ts) != 0) {
    fprintf(stderr, "%s: unable to get current time - call to clock_gettime() failed\n", progname);
    exit(1);
  }

  timenow = timenow_ts.tv_sec;

#ifdef DEBUG
  printf("Current time: %s", ctime(&timenow));
#endif

  while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
    lenline = strlen(line);

    if (lenline > 0) {
      if (line[lenline - 1] == '\n') {
        line[lenline - 1] = '\0';
        lenline--;
      }
    }

    if (lenline == 0) {
      continue;
    }

    if (stat(line, &stbuf) < 0) {
      fprintf(stderr, "%s: unable to stat file \"%s\"\n", progname, line);
      continue;
    }

    accesstime = (stbuf.st_atim).tv_sec;
    modifiedtime = (stbuf.st_mtim).tv_sec;
    chmodtime = (stbuf.st_ctim).tv_sec;

#ifdef DEBUG
    printf("Access time.....: %s", ctime(&accesstime));
    printf("Modified time...: %s", ctime(&modifiedtime));
    printf("Chmod time......: %s", ctime(&chmodtime));
#endif

    strncpy(amc, "---", THREE_PLUS_NULL);

    if (difftime(timenow, accesstime) <= delta) {
      amc[0] = 'a';
    }

    if (difftime(timenow, modifiedtime) <= delta) {
      amc[1] = 'm';
    }

    if (difftime(timenow, chmodtime) <= delta) {
      amc[2] = 'c';
    }

    if (strncmp(amc, "---", THREE_PLUS_NULL) != 0) {
      printf("[%s] %s\n", amc, line);
    }
  }

  exit(0);
}

/*** end of file ***/

