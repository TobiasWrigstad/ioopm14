#include <stdlib.h>
#include <stdint.h>

#include "balance.h"
#include "node.h"

enum balance { 
  BALANCED, 
  LEFT_LEFT_HEAVY, 
  LEFT_RIGHT_HEAVY,
  RIGHT_LEFT_HEAVY, 
  RIGHT_RIGHT_HEAVY 
};

node_s *rotate_left(node_s *n);

node_s *flip_left(node_s *n);

node_s *rotate_right(node_s *n);

node_s *flip_right(node_s *n);

enum balance balance_check(node_s *n);

// Utför rotation:
// 
//     A         B
//    B   ==>   C A         
//   C 
//        
// \param A
// \return B
node_s *rotate_left(node_s *n)
{
  node_s *pivot = n->left;
  n->left = pivot->right;
  pivot->right = n;
  return pivot;
}

// Utför rotation:
// 
//     A         C
//    B   ==>   B A         
//     C 
//        
// \param A
// \return C
node_s *flip_left(node_s *n)
{
  node_s *pivot = n->left->right;

  n->left->right = pivot->left;
  pivot->left = n->left;

  n->left = pivot->right;
  pivot->right = n;

  return pivot;
}

// Utför rotation:
// 
//     A         C
//      B  ==>  A B         
//     C 
//        
// \param A
// \return C
node_s *rotate_right(node_s *n)
{
  node_s *pivot = n->right;
  n->right = pivot->left;
  pivot->left = n;
  return pivot;
}

// Utför rotation:
// 
//     A         B
//      B  ==>  C A         
//       C
//        
// \param A
// \return B
node_s *flip_right(node_s *n)
{
  node_s *pivot = n->right->left;

  n->right->left = pivot->right;
  pivot->right = n->right;

  n->right = pivot->left;
  pivot->left = n;

  return pivot;
}

enum balance balance_check(node_s *n)
{
  if (n)
    {
      int32_t left_depth = node_depth(n->left);
      int32_t right_depth = node_depth(n->right);

      if (left_depth - right_depth > 1)
	{ // Vänstertungt träd, kontrollera vilken typ
	  return (n->left->left) ?  
	    LEFT_LEFT_HEAVY : 
	    LEFT_RIGHT_HEAVY;
	}

      if (right_depth - left_depth > 1)
	{ // Högertungt träd, kontrollera vilken typ
	  return (n->right->right) ? 
	    RIGHT_RIGHT_HEAVY : 
	    RIGHT_LEFT_HEAVY;
	}
    }

  return BALANCED;
}

void balance_subtree(node_s ***ns, uint32_t ns_size)
{
  for (uint32_t i = ns_size - 1; i; --i)
    {
      node_s **n = ns[i];

      switch (balance_check(*n)) 
	{
	case BALANCED:
	  break;
	case LEFT_LEFT_HEAVY:
	  *n = rotate_left(*n);
	  break;
	case LEFT_RIGHT_HEAVY:
	  *n = flip_left(*n);
	  break;
	case RIGHT_RIGHT_HEAVY:
	  *n = rotate_right(*n);
	  break;
	case RIGHT_LEFT_HEAVY:
	  *n = flip_right(*n);
	  break;
	}
    }
}
