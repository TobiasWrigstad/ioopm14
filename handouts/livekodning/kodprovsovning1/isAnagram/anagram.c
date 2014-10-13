#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Notera att den här funktionen implementerar den första
   anagramuppgiften. Den hanterar alltså inte godtyckliga
   blanksteg.
*/
int isAnagram(char *s1, char *s2){
  char *tmp = malloc((strlen(s2) + 1)*sizeof(char));
  strcpy(tmp, s2);
  
  for(int i = 0; s1[i] != '\0'; i++){
    char c1 = s1[i];
    int found = 0;
    for(int j = 0; j < strlen(s2); j++){
      char c2 = tmp[j];
      if(c1 == c2){
        tmp[j] = '\0';
        found = 1;
        break;
      }
    }
    if(found == 0){
      return 0;
    }
  }
  for(int i = 0; i < strlen(s2); i++){
    if(tmp[i] != '\0')
      return 0;
  }
  free(tmp);
  return 1;
}

// Koden har modifierats för att underlätta testning
int main(int argc, char *argv[]){
  if(argc < 3){
    puts("usage: anagram s1 s2");
    return 1;
  }

  char *s1 = argv[1];
  char *s2 = argv[2];
  if(isAnagram(s1, s2))
    printf("\"%s\" is an anagram of \"%s\"\n", s1, s2);
  else
    printf("\"%s\" is not an anagram of \"%s\"\n", s1, s2);
  return 0;


/* // Den ursprungliga main-funktionen
  int error = 0;
  if(!isAnagram("silent", "listen")){
    puts("1. Oh no!");
    error++;
  }
  if(isAnagram("silent", "loud")){
    puts("2. Oh no!");
    error++;
  }
  if(!isAnagram("", "")){
    puts("3. Oh no!");
    error++;
  }
  if(isAnagram("", "nothing")){
    puts("4. Oh no!");
    error++;
  }
  if(error == 0)
    puts("Ah yiss!");
  return 0;
*/
}