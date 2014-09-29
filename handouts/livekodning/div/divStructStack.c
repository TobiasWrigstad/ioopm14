#include <stdio.h>
#include <stdlib.h>

struct tuple{
  int fst;
  int snd;
};

// [X] Struct på stacken
// Struct på heapen

struct tuple quotientAndRemainder(int nominator, int denominator){
  int quotient = nominator / denominator;
  int remainder = nominator % denominator;
  struct tuple t;
  t.fst = quotient;
  t.snd = remainder;
  return t;
}

int main(int argc, char *argv[])
{
  int nominator = 13;
  int denominator = 5;
  struct tuple t = quotientAndRemainder(nominator, denominator);
  int quotient = t.fst;
  int remainder = t.snd;
  printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  return 0;
}
