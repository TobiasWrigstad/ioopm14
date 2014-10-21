#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "tree/tree.h"

int main(int argc, char *argv[])
{
  tree_s *t = tree_new((cmp_f) strcmp, true);

  char *es[] = { "A", "B", "C", "D", "E", "F", NULL };

  tree_insert(t, es[2], es[2]);
  tree_insert(t, es[0], es[0]);
  tree_insert(t, es[1], es[1]);

  puts("===============================================================");
  puts("Printing the path for each element in the tree (C,A,B inserted)");
  puts("===============================================================");

  for (char **e = es; *e; ++e) 
    {
      char *s = tree_get_path_for_element(t, *e);
      printf("%s --> %s\n", *e, s);
      free(s);
    }

  tree_insert(t, es[3], es[3]);
  tree_insert(t, es[4], es[4]);
  tree_insert(t, es[5], es[5]);

  puts("===========================================================");
  puts("Printing the path for all elements in the tree (all of A-F)");
  puts("===========================================================");

  for (char **e = es; *e; ++e)
    {
      char *s = tree_get_path_for_element(t, *e);
      printf("%s --> %s\n", *e, s);
      free(s);
    }

  puts("===========================================================");
  puts("Dumping contents IN_ORDER");
  puts("===========================================================");

  tree_traversal(IN_ORDER, t, (apply_f) printf, "%s\n");

  puts("===========================================================");
  puts("Dumping contents POST_ORDER");
  puts("===========================================================");

  tree_traversal(POST_ORDER, t, (apply_f) printf, "%s\n");

  puts("===========================================================");
  puts("Dumping contents PRE_ORDER");
  puts("===========================================================");

  tree_traversal(PRE_ORDER, t, (apply_f) printf, "%s\n");

  puts("===========================================================");
  printf("Printing path for %s and element for that path\n", es[4]);
  puts("===========================================================");

  char *p = tree_get_path_for_element(t, es[4]);
  printf("%s --> %s\n", es[4], p);
  printf("%s --> %s\n", p, tree_get_element_for_path(t, p));
  free(p);

  tree_delete(t);

  return 0;
}

  
