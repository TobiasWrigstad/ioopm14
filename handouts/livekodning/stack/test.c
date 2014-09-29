#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define TEST(ID, test) test_count++; \
                       if(test) pass_count++; \
                       else printf("Failed test " #ID ": " #test "\n");

void runTests(){
  int test_count = 0;
  int pass_count = 0;

  Stack s = mkStack();
  int *x = malloc(sizeof(int));
  *x = 111;
  int *y = malloc(sizeof(int));
  *y = 222;

  TEST(1, (int*) top(s) == NULL);

  push(s, x);
  TEST(2, (int*) top(s) == x);

  push(s, y);
  TEST(3, (int*) top(s) == y);

  TEST(4, size(s) == 2);

  int *result = (int*) pop(s);
  TEST(5, result == y);
  TEST(6, *result == 222);
  TEST(7, size(s) == 1);

  result = (int*) pop(s);
  TEST(8, result == x);
  TEST(9, *result == 111);
  TEST(10, size(s) == 0);

  printf("Passed %d out of %d tests\n", pass_count, test_count);
}

int main(){
  runTests();
}