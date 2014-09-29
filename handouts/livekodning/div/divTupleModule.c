#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"

struct tuple *quotientAndRemainder(int nominator, int denominator){
  int quotient = nominator / denominator;
  int remainder = nominator % denominator;
  struct tuple *t = mkTuple();
  setFirst(t, quotient);
  setSecond(t, remainder);
  return t;
}

int main(int argc, char *argv[])
{
  int nominator = 13;
  int denominator = 5;
  struct tuple *t = quotientAndRemainder(nominator, denominator);
  int quotient = getFirst(t);
  int remainder = getSecond(t);
  printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  destroyTuple(t);
  return 0;
}
