#ifndef _OPT_H_
#define _OPT_H_

//global values 
struct
{
  unsigned int loop;
  unsigned int interval;

  FILE *output;
} opt;

void opt_parse(int argc, char **argv);

#endif