#include <stdio.h>
#include <stdlib.h>

struct tuple{
  int fst;
  int snd;
};

// [X] Struct på heapen

struct tuple *quotientAndRemainder(int nominator, int denominator){
  int quotient = nominator / denominator;
  int remainder = nominator % denominator;
  struct tuple *p = malloc(sizeof(struct tuple)); // På heapen!
  p->fst = quotient; // PRECIS samma sak som (*p).fst = quotient;
  p->snd = remainder;
  return p;
}

int main(int argc, char *argv[])
{
  int nominator = 10;
  int denominator = 5;
  struct tuple *t = quotientAndRemainder(nominator, denominator);
  int quotient = t->fst;
  int remainder = t->snd;
  printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  free(t);
  return 0;
}
