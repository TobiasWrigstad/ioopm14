#ifndef _node_h_
#define _node_h_

#include <stdbool.h>
#include <stdint.h>

#include "tree.h"

typedef struct node node_s;

struct node
{
  struct node *left;
  struct node *right;
  void *key;
  void *value;
};

struct key_value
{
  void *key;
  void *value;
};

/// Skapar en ny nod.
///
/// \param el elementet
/// \return en pekare till en ny nod som allokerats på heapen
node_s *node_new(void *k, void *v);

/// Tar bort en nod ur minnet och returnerar en pekare till dess element.
struct key_value node_delete(node_s *n);

/// Returnerar subträdets djup. \sa tree_depth
uint32_t node_depth(node_s *n);

/// Returnerar subträdets storlek. \sa tree_size
uint32_t node_size(node_s *n);

/// Traverserar subträdet. \sa tree_traversal
void node_traversal(enum order order, node_s *n, apply_f f, void *arg, bool called_internally);

/// Tar bort den minsta lövnoden i trädet och returnerar en pekare till dess element.
/// \param n_field en pekare till föräldranodens höger/vänster-post
struct key_value unlink_smallest(node_s **n_field);

/// Stoppar in ett nytt element i trädet.
void node_insert(cmp_f key_cmp, void *k, void *v, node_s **n, bool balance);

#endif
