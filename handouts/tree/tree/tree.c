#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "node.h"
#include "util.h"

struct tree
{
  node_s *root;
  cmp_f key_cmp;
  bool should_balance;
};


#define No_left_subtree(n) ((n)->left == NULL)
#define No_right_subtree(n) ((n)->right == NULL)
#define Is_leaf(n) (No_right_subtree(n) && No_left_subtree(n))


// ================================================================
// Funktionsprototyper
// ================================================================

static inline
node_s **tree_find(tree_s *t, void *k);


// ================================================================
// Inspektering och traversering
// ================================================================

static inline
node_s **tree_find(tree_s *t, void *k)
{
  node_s **n = &(t->root);

  while (*n)
    {
      int32_t result = t->key_cmp((*n)->key, k);
      if (result == 0) break;

      n = (result < 0) ? &((*n)->left) : &((*n)->right);
    }

  return n;
}

void *tree_get(tree_s *t, void *k)
{
  node_s *n = *tree_find(t, k);

  if (n)
    {
      return n->value;
    }
  else
    {
      return NULL;
    }
}

void tree_traversal(enum order order, tree_s *t, apply_f f, void *fst_arg)
{
  node_traversal(order, t->root, f, fst_arg, false);
}

// ================================================================
// Skapa och förstör trädet
// ================================================================

tree_s *tree_new(cmp_f f, bool b)
{
  tree_s *t = malloc(sizeof(tree_s));

  if (t) *t = (tree_s) { .key_cmp = f, .should_balance = b };

  return t;
}

void tree_delete(tree_s *t)
{
  node_traversal(POST_ORDER, t->root, (apply_f) node_delete, NULL, true);

  free(t);
}

// ================================================================
// Insättning och borttagning
// ================================================================

void tree_insert(tree_s *t, void *k, void *v)
{
  node_s *root = t->root;

  if (root == NULL)
    {
      t->root = node_new(k, v);
    }
  else
    {
      node_insert(t->key_cmp, k, v, &root, t->should_balance);
    }
}

// FIXME balansering!
void *tree_remove(tree_s *t, void *k)
{
  node_s **n = tree_find(t, k);
  void *v = (*n)->value;

  // Blir tabuleringen mer läslig än inte? 
       if (Is_leaf(*n)         ) *n = NULL;
  else if (No_left_subtree(*n) ) *n = (*n)->right;
  else if (No_right_subtree(*n)) *n = (*n)->left;
  else                           {
                                   struct key_value kv = unlink_smallest(&((*n)->left));
                                   (*n)->key   = kv.key;
                                   (*n)->value = kv.value;
                                 }
                             
  return v;
}

// ================================================================
// Hjälpfunktioner för testning
// ================================================================

void *tree_get_element_for_path(tree_s *t, char *path)
{
  node_s *n = t->root;

  for (; *path && n; ++path)
    {
      switch (*path)
        {
        case 'L': n = n->left;  break;
        case 'R': n = n->right; break;
        default : assert(false); // Faulty input string
        }
    }

  return n ? n->value : NULL;
}

char *tree_get_path_for_element(tree_s *t, void *k)
{
  node_s *n = t->root;
  char *path = calloc(tree_depth(t), sizeof(char));
  char *c = path;

  while (n)
    {
      if (t->key_cmp(n->key, k) < 0)
        {
          *c++ = 'L';
          n = n->left;
        }
      else
        if (t->key_cmp(n->key, k) > 0)
	  {
	    *c++ = 'R';
	    n = n->right;
	  }
	else
	  {
	    return path;
	  }
    }

  free(path);
  return NULL;
}

uint32_t tree_depth(tree_s *t)
{
  return node_depth(t->root);
}

uint32_t tree_size(tree_s *t)
{
  return node_size(t->root);
}
