#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* 
   * Den nedanstående funktionen är koden som skrevs live. Notera
     att funktionen inte skiljer på stora och små bokstäver.

   * If-satsen är egentligen inte nödvändig. For-loopen kommer att
     göra rätt även om längden på s är 0 (skippa loopen helt)
     eller 1 (en iteration i loopen).

   * När man har kommit igenom halva strängen behöver man inte
     kolla längre (om den första halvan är den andra halvan
     baklänges så kommer det omvända gälla också). Vi har inte
     passerat mitten på strängen så länge som "i < len - 1 - i".

*/

int isPalindrome(char *s){
  int len = strlen(s);
  if(len <= 1)
    return 1;
  for(int i = 0; i < len; i++){
    if(tolower(s[i]) != tolower(s[len - 1 - i]))
      return 0;
  }
  return 1;
}

// Koden har modifierats från originalet för att underlätta testning
int main(int argc, char *argv[]){
  if(argc < 2){
    puts("usage: ./palindrome s");
    return 1;
  }
  
  char *s = argv[1];
  if(isPalindrome(s))
    printf("\"%s\" is a palindrome\n", s);
  else
    printf("\"%s\" is not a palindrome\n", s);
  return 0;
}