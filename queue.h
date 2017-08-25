/*
  copyright by bokenshonen(kidd.dawny.lu@gmail.com)
*/

#ifndef _QUEQUE_H_
#define _QUEQUE_H_

#include <stdbool.h>

#include "proc.h"
typedef stat_t item_t;

struct node
{
  item_t item;
  struct node *next;
};

typedef struct {
  struct node *front;
  struct node *rear;
} queue;

queue *init(void);
void final(queue *q);
void push(queue *q, item_t data);
void pop(queue *q);

item_t front(queue *q);
item_t back(queue *q);

int size(queue *q);

bool empty(queue *q);
#endif