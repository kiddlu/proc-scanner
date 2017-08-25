#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "opt.h"

#define DEFAULT_LOOP     5
#define DEFAULT_INTERVAL 10

static void usage()
{
#define VERSION_MAJOR "1"
#define VERSION_MINOR "0"
  char* usage = 
    "\n"
    "Usage:\n"
    "|| NAME\n"
    "||  proc_scanner - a tool to scan /proc infomation.\n"
    "||\n"
    "|| SYNOPSIS\n"
    "||  proc_scanner [ -l loop time] [ -i interval] [-h] [-o output]\n"
    "||\n"
    "|| DESCRIPTION\n"
    "||  Requires Linux.\n"
    "||\n"
    "|| PARAMETER\n"
    "||  -h, print this help message.\n"
    "||  -l loop time.\n"
    "||    How many times scanner loop.\n"			
    "||  -i interval.\n"
    "||    How many seconds between current and next scan.\n"	
    "||  -o output.\n"
    "||    Output result to file instead of stdout.\n"	
    "||\n"
    "|| VERSION\n"
    "||  "VERSION_MAJOR"."VERSION_MINOR", "__DATE__" "__TIME__"\n"
    "||\n"
    "|| AUTHOR\n"
    "||  huangxiaolu\n"
    "\n";
  
  printf("%s", usage);
  exit(EXIT_SUCCESS);
}

void opt_parse(int argc, char **argv)
{
  int c;

  opt.loop = DEFAULT_LOOP;
  opt.interval = DEFAULT_LOOP; 
  opt.output = stdout;

  while((c = getopt(argc, argv, "hl:i:o:")) != -1 ) {
    switch(c) {
      case 'h':
        usage();
        break;
      case 'l':
        opt.loop = strtoul(optarg, NULL, 10);
        break;
      case 'i':
        opt.interval = strtoul(optarg, NULL, 10);
        break;
      case 'o':
        opt.output = fopen(optarg, "w");
        if(opt.output == NULL) {
          fprintf(stderr, "can't open file %s\n", optarg); 
          exit(EXIT_FAILURE);
        }
        break;
      default :
        usage();
    }
  } 
}