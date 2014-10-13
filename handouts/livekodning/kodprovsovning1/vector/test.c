#include <stdio.h>
#include "vector.h"

/* I uppgiftstexten anropas vissa funktioner med arrayer som
   argument direkt ("vector_mk(3, {1.0, 2.5, 3.33})"). Detta är
   inte korrekt C-syntax. Istället måste man allokera arrayen
   innan man anropar funktionen. 
*/
int main(){
  double values1[] = {1.0, 2.5, 3.33};
  Vector v1 = vector_mk(3, values1);
  double values2[] = {2.0, 1.5, -3.33};
  Vector v2 = vector_mk(3, values2);
  Vector v3 = vector_add(v1, v2);
  double abs = vector_abs(v3);
  if(abs == 5.0)
    puts("Success!");
  else
    printf("Oh noes! abs = %f\n", abs);
  return 0;
}