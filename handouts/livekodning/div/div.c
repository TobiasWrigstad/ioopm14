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
  int nominator;
  int denominator;
  if(argc > 1){
    nominator = atoi(argv[1]);
  }
  else{
    printf("Nominator? ");
    scanf("%d", &nominator);
    while(getchar()!='\n');
  }
  if(argc > 2){
    denominator = atoi(argv[2]);
  }
  else{
    printf("Denominator? ");
    scanf("%d", &denominator);
    while(getchar()!='\n');
  }
  struct tuple *t = quotientAndRemainder(nominator, denominator);
  int quotient = getFirst(t);
  int remainder = getSecond(t);
  if(remainder == 0)
    printf("%d = %d * %d\n", nominator, denominator, quotient);
  else
    printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  destroyTuple(t);
  return 0;
}
