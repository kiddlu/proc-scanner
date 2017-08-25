#ifndef _PROC_H_
#define _PROC_H_

typedef struct {
  int normal;
  int sync;
  int direct;
} stat_t;

stat_t proc_scan(void);
#endif