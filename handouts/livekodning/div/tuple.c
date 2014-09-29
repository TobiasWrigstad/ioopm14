#include <stdlib.h>
#include "struct.h"

struct tuple{
  int fst;
  int snd;
};

struct tuple *mkTuple(){
  struct tuple *t = malloc(sizeof(struct tuple));
  return t;
}

void destroyTuple(struct tuple *t){
  if(t != NULL)
    free(t);
}

int getFirst(struct tuple *t){
  return t->fst;
}

int getSecond(struct tuple *t){
  return t->snd;
}

void setFirst(struct tuple *t, int n){
  if(t != NULL)
    t->fst = n;
}

void setSecond(struct tuple *t, int n){
  if(t != NULL)
    t->snd = n;
}