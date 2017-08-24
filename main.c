#include <stdio.h>
#include <unistd.h>

#include "queue.h"
#include "proc.h"
#include "opt.h"

static void process(queue *q)
{
  stat_t info;
  for(int i = 0; i < opt.loop; i++ ) {
    info = proc_scan();
    push(q, info);
    sleep(opt.interval);
  }
}

int main(int argc, char **argv)
{
  opt_parse(argc, argv);
  
  queue *q;
  FILE *out = opt.output;

  q = init();
  process(q);

  fprintf(out, "scan,normal,direct,sync\n");
  for(int i =1; !empty(q); i++) {
    fprintf(out, "%d,%d,%d,%d\n",
          i, front(q).normal, front(q).direct, front(q).sync);
    pop(q);
  }
  final(q);

  fclose(out);

  return 0;
}
