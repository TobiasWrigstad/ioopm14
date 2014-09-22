#include <stdio.h>
#include <stdlib.h>

// [X] Skicka med pekare
// Struct på heapen
// Struct på stacken

void quotientAndRemainder(int nominator, int denominator, 
                          int *quotient, int *remainder){
  *quotient = nominator / denominator;
  *remainder = nominator % denominator;
}

int main(int argc, char *argv[])
{
  int nominator = 13;
  int denominator = 5;
  int quotient;
  int remainder;
  quotientAndRemainder(nominator, denominator, &quotient, &remainder);
  printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  return 0;
}
