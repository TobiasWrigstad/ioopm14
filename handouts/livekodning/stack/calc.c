#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void readline(char dest[128]){
  fgets(dest, 128, stdin);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void showStack(Stack s){
  Iterator i = init(s);
  while(hasNext(i)){
    int *elem = (int*)getNext(i);
    printf("%d", *elem);
    if(hasNext(i)){
      printf(", ");
    }
  }
  printf(" <-- Stack\n");
  freeIterator(i);
}

void pushNum(Stack s, int num){
  int *elem = malloc(sizeof(int));
  *elem = num;
  push(s, elem);
}

void doAdd(Stack s){
  if(size(s) < 2){
    puts("*** ERROR: Not enough arguments ***");
  }else{
    int *arg1 = (int*)pop(s);
    int *arg2 = (int*)pop(s);
    int *result = malloc(sizeof(int));
    *result = *arg1 + *arg2;
    push(s, result);
    free(arg1);
    free(arg2);
  }
}

void doMultiply(Stack s){
  if(size(s) < 2){
    puts("*** ERROR: Not enough arguments ***");
  }else{
    int *arg1 = (int*)pop(s);
    int *arg2 = (int*)pop(s);
    int *result = malloc(sizeof(int));
    *result = *arg1 * *arg2;
    push(s, result);
    free(arg1);
    free(arg2);
  }
}

int main(){
  Stack s = mkStack();
  char buffer[128];
  strcpy(buffer, "abc");
  while(strlen(buffer) > 0){
    puts("================");
    showStack(s);
    puts("");
    readline(buffer);

    if(strcmp(buffer, "+") == 0){
      doAdd(s);
    }
    else if(strcmp(buffer, "*") == 0){
      doMultiply(s);
    }
    else if(isdigit(buffer[0])){
      int num = atoi(buffer);
      pushNum(s, num);
    }
    else if(strlen(buffer) > 0){
      printf("*** ERROR: Unknown command '%s' ***\n", buffer);
    }
  }
  freeStack(s);
  return 0;
}
