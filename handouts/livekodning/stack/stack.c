#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct node{
  void *elem;
  struct node *next;
};

struct node *mkNode(void *element, struct node *next){
  struct node *n = malloc(sizeof(struct node));
  if(n == NULL)
    return NULL;
  n->elem = element;
  n->next = next;
  return n;
}

struct stack{
  struct node *top;
};

struct stack *mkStack(){
  struct stack *s = malloc(sizeof(struct stack));
  if(s == NULL)
    return NULL;
  s->top = NULL;
  return s;
}

void freeStack(struct stack *s){
  assert(s != NULL);
  struct node *cursor = s->top;
  while(cursor != NULL){
    struct node *tmp = cursor;
    cursor = cursor->next;
    free(tmp);
  }
  free(s);
}

void push(struct stack *s, void *elem){
  assert(s != NULL);
  struct node *newTop = mkNode(elem, s->top);
  s->top = newTop;
}

void *pop(struct stack *s){
  assert(s != NULL);
  if(s->top == NULL)
    return NULL;
  struct node *tmpNode = s->top;
  s->top = s->top->next;
  void *result = tmpNode->elem;
  free(tmpNode);
  return result;
}

void *top(struct stack *s){
  assert(s != NULL);
  if(s->top == NULL)
    return NULL;
  return s->top->elem;
}

int size(struct stack *s){
  assert(s != NULL);
  int counter = 0;
  struct node *cursor = s->top;
  while(cursor != NULL){
    counter++;
    cursor = cursor->next;
  }
  return counter;
}

// Nedan finns koden för en stackiterator. En iterator fungerar
// som en pekare in en annan datastruktur, och kan användas för
// att iterera genom datastrukturens alla element utan att man
// behöver veta hur strukturen ser ut på insidan. En iterator
// erbjuder i allmänhet två operationer:
//
//  * hasNext returnerar true (eller 1) om det finns fler element
//    att peka ut, annars false (eller 0). I vårt fall kollar vi
//    helt enkelt om stacknoden vi för närvarande pekar ut är
//    NULL.
//
//  * getNext returnerar elementet för den nod som vi för
//    närvarande pekar ut OCH flyttar iteratorn till nästa nod.
//    Notera att vi inte returnerar stackens noder, utan elementen
//    som varje nod pekar ut (annars skulle abstraktionen läcka!).
//    Den typiska användningen är att man bara anropar getNext om
//    hasNext returnerar true.
//
// Se koden för showStack i calc.c för ett exempel på hur en
// iterator kan användas.

struct iterator{
  struct node *current;
};

struct iterator *init(struct stack *s){
  assert(s != NULL);
  struct iterator *i = malloc(sizeof(struct iterator));
  if(i == NULL)
    return NULL;
  i->current = s->top;
  return i;
}

int hasNext(struct iterator *i){
  assert(i != NULL);
  if(i->current != NULL)
    return 1;
  else
    return 0;
}

void *getNext(struct iterator *i){
  assert(i != NULL);
  struct node *tmp = i->current;
  i->current = i->current->next;
  return tmp->elem;
}

void freeIterator(struct iterator *i){
  assert(i != NULL);
  free(i);
}