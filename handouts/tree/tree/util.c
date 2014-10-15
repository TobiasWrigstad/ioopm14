#include "util.h"

uint32_t node_depth(node_s *n)
{
  #define Max(a,b) (a < b ? b : a)

  return n ? 1 + Max(node_depth(n->left), node_depth(n->right)) : 0;
}

uint32_t node_size(node_s *n)
{
  return n ? 1 + node_size(n->left) + node_size(n->right) : 0;
}

