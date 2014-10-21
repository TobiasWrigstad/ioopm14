#ifndef _tree_h_
#define _tree_h_

#include <stdint.h>
#include <stdbool.h>

/// Trädet 
typedef struct tree tree_s;

/// En jämförelsefunktion som används av trädet för att jämföra element.
typedef int (*cmp_f)(void *, void *);

/// Signaturen för funktioner som skickas som argument till tree_traversal. \sa tree_traversal
typedef void (*apply_f)(void *, void *);

/// Specificerar en traverseringordning. \sa tree_traversal
enum order
  {
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
  };

/// Skapa ett nytt träd.
///
/// \param key_compare_function pekar ut den jämförelsefunktion som skall användas för att jämföra elementen i trädet
/// \param auto_balance är true om trädet skall balansera sig automatiskt vid insättning och borttagning
/// 
/// Jämförelsefunktionen skall fungera som strcmp map returvärden. 
tree_s *tree_new(cmp_f key_compare_function, bool auto_balance);

/// Ta bort trädet ur minnes.
///
/// \param tree trädet
/// 
/// Sorteringsnycklar och element tas inte bort ur minnet.
void tree_delete(tree_s *tree);

/// Stoppar in ett element i trädet. 
///
/// OBS! Implementationen förutsätter att alla nycklar är unika vid insättning!
///
/// \param tree trädet
/// \param key sorteringsnyckeln för elementet
/// \param value elementet som skall stoppas in
///
void tree_insert(tree_s *tree, void *key, void *value);

/// Traverserar trädet i angiven ordningsföljd och utför en operation på varje element.
/// \sa enum order
/// \sa apply_f
///
/// \param order traverseringsordningen
/// \param tree trädet
/// \param operation operationen som skall utföras på varje element
/// \param argument till varje operation (skickas som första argument till apply_f-funktionen om != NULL)
void tree_traversal(enum order order, tree_s *tree, apply_f operation, void *fst_arg);

/// Returnerar djupet i trädet.
///
/// \param tree trädet
/// \return tree:s djup
uint32_t tree_depth(tree_s *tree) ;

/// Returnerar trädets storlek (antalet noder).
///
/// \param tree trädet
/// \return tree:s storlek (antalet noder)
uint32_t tree_size(tree_s *tree);

/// Returnerar en pekare till ett element i trädet. 
///
/// \param tree trädet
/// \param key sorteringsnyckeln för det sökta elementet
/// \return det matchande elementet från trädet
void *tree_get(tree_s *tree, void *key);

/// Tar bort ett element ur trädet.
///
/// \param tree trädet
/// \param key sorteringsnyckeln för det sökta elementet
/// \return en pekare till elementet eller NULL om det inte fanns i trädet
void *tree_remove(tree_s *tree, void *key) ;

/// Returnerar en path till ett element i trädet. 
///
/// En path kan vara t.ex. "" för roten, "LL" för två steg
/// vänster, "LR" för vänster-höger etc.
///
/// \param tree trädet
/// \param key sorteringsnyckeln för det sökta elementet
/// \return pathen till el, ev NULL om el inte finns i trädet
char *tree_get_path_for_element(tree_s *tree, void *key);

/// Tar en sträng med samma format som returneras från
/// tree_get_path_for_element och returnerar elementet på den
/// platsen i trädet.
///
/// \param tree trädet
/// \param path pathen till elementet som skall returneras
/// \return en pekare till ett element eller NULL
void *tree_get_element_for_path(tree_s *tree, char *path);

#endif
