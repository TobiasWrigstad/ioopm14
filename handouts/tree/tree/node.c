#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "tree.h"
#include "node.h"
#include "balance.h"

#define Call(f,a1,a2) do { if (a1) f(a1,a2); else f(a2,NULL); } while(0)
#define Val_or_whole(n,i)   ((i) ? n : n->value)

node_s *node_new(void *k, void *v)
{
  node_s *n = malloc(sizeof(node_s));

  if (n) *n = (node_s) { .key = k, .value = v };

  return n;
}

struct key_value node_delete(node_s *n)
{
  struct key_value kv = { .key = n->key, .value = n->value };
  free(n);
  return kv;
}

struct key_value unlink_smallest(node_s **n)
{
  while (*n) 
    {
      if ((*n)->left)  { n = &((*n)->left); continue; }
      if ((*n)->right) { n = &((*n)->right);          } else { break; }
    }
  
  node_s *tmp = *n;
  *n = NULL; 

  return node_delete(tmp);
}

void node_insert(cmp_f key_cmp, void *k, void *v, node_s **n, bool balance)
{
  node_s **cursor = n; 
  node_s ***parents;
  uint32_t pidx = 0;

  if (balance) parents = calloc(node_depth(*n), sizeof(node_s **));

  while (*cursor)
    {
      if (balance) parents[pidx++] = cursor;

      cursor = (key_cmp((*cursor)->key, k) < 0) ? 
	&((*cursor)->left) : 
	&((*cursor)->right); 
    }

  *cursor = node_new(k, v);

  if (balance) 
    {
      balance_subtree(parents, pidx);

      free(parents);
    }
}

void node_traversal(enum order order, node_s *n, apply_f f, void *arg, bool whole)
{
  if (n == NULL) return;

  switch (order)
    {
    case PRE_ORDER:
      Call(f, arg, Val_or_whole(n, whole));
      node_traversal(order, n->left,  f, arg, whole);
      node_traversal(order, n->right, f, arg, whole);
      break;

    case POST_ORDER:
      node_traversal(order, n->left,  f, arg, whole);
      node_traversal(order, n->right, f, arg, whole);
      Call(f, arg, Val_or_whole(n, whole));
      break;

    case IN_ORDER:
      node_traversal(order, n->left,  f, arg, whole);
      Call(f, arg, Val_or_whole(n,whole));
      node_traversal(order, n->right, f, arg, whole);
      break;

    default:
      assert(false); // This should never happen
    }
}
