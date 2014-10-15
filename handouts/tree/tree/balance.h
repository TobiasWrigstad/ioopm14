#ifndef _balance_h_
#define _balance_h_

#include "node.h"

/// Kontrollerar hur välbalanserat ett subträd är. \sa enum balance
enum balance balance_check(node_s *n);

/// Utför 0 till `ns_size` ombalanseringar av subträd rotade i `*ns[0..ns_size-1]`.
///
/// \param ns en array av pekare till pekare till noder (se exempel)
/// \param ns_size storleken på `ns`
///
/// Låt `ns == [p1, p2, p3]` när `ns_size == 3`. Då skall gälla att
/// antingen `&((*p1)->left) == p2` eller `&((*p1)->right == p2)`, och
/// antingen `&((*p2)->left) == p3` eller `&((*p2)->right == p3)`.
void balance_subtree(node_s **ns[], uint32_t ns_size);

#endif
