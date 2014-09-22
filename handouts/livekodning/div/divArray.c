#include <stdio.h>
#include <stdlib.h>

// [X] Array
// Skicka med pekare
// Struct på heapen
// Struct på stacken

void quotientAndRemainder(int nominator, int denominator, int arr[]){
  int quotient = nominator / denominator;
  int remainder = nominator % denominator;
  arr[0] = quotient;
  arr[1] = remainder;
}

int main(int argc, char *argv[])
{
  int nominator = 42;
  int denominator = 4;
  int arr[2];
  quotientAndRemainder(nominator, denominator, arr);
  int quotient = arr[0];
  int remainder = arr[1];
  printf("%d = %d * %d + %d\n", nominator, denominator, quotient, remainder);
  free(arr);
  return 0;
}
