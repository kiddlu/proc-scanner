#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue *init(void)
{
  queue *q = malloc(sizeof(queue));
  if (!q) {
    fprintf(stderr, "no memory\n");
    return NULL;
  }

  q->front = NULL;
  q->rear = NULL;
  return q;
}

void final(queue *q)
{
  if(q == NULL || q->front == NULL)
    return;

  while(!empty(q))
    pop(q);
  free(q);
}

void push(queue *q, item_t data)
{
  struct node *new;

  new = malloc(sizeof(struct node));
  if(new == NULL){
    fprintf(stderr, "no memory\n");
  } else {
    new->item = data;
    new->next = NULL;
    if(q->front == NULL) {
      q->front = new;
    }

    if(q->rear == NULL) {
      q->rear = new;
    } else {
      q->rear->next = new;
      q->rear = new;
    }
    return;
  }
}

void pop(queue *q)
{
  struct node *tmp = NULL;

  if(empty(q)) {
    fprintf(stderr,"empty queue");
    return;
  }

  if (q->front == q->rear) { //only one node in queue
    tmp = q->front;
    q->front = NULL;
    q->rear = NULL;
  } else {
    tmp = q->front;
    q->front = q->front->next;
  }

  free(tmp);

  return;
}

item_t front(queue *q)
{
  return q->front->item;
}

item_t back(queue *q)
{
  return q->rear->item;
}

bool empty(queue *q)
{
  return q->front == NULL;
}
