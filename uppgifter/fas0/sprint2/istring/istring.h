#ifndef ISTRING_H
#define ISTRING_H

#include <string.h>

/*
 * Returns a new istring instance created from supplied
 * string. Returns NULL if out of memory. Returns NULL string if
 * argument str is NULL. 
 */
char *istring_mk(const char* str);

/*
 * Deallocates the supplied istring.
 */
void istring_rm(char *str);

/*
 * Returns a standard null terminated char* representation of the
 * supplied istring. Returns NULL if out of memory.
 */
char *istring_to_string(const char *str);

/*
 * Inspects the length of the string from str and if it differs from
 * length, updates length accordingly. If str does not contain a \0
 * token, it will be inserted at the first element which is not a
 * printable ascii character, and length updated accordingly. This
 * function must be as efficient as possible and not rescan the string
 * if it can be avoided.
 *
 * This function is useful when istrings have been manipulated as
 * regular C strings, to reestablish the length invariant.
 */
size_t istrfixlen(char *s);

/* 
 * Sets the length of an istring and inserts a corresponding '\0'
 * character. If the length argument is out of bounds for the string,
 * a new istring should be returned with the contents of the original
 * string. The last character of the original string will be repeated
 * to fill the string to its given length.
 */
char* istrslen(char *s, size_t length);

/*
 * For definitions, see the manual page of respective function on the
 * solaris system and the assignment text.
 * 
 * Think about whether having O(1) access to the length can be used to
 * improve the implementations if the string.h equivalents and use
 * that to guide your implementations!
 */
char *istrchr(const char *s, int c);
char *istrrchr(const char *s, int c);
int istrcmp(const char *s1, const char *s2);
int istrncmp(const char *s1, const char *s2, size_t n);
size_t istrlen(const char *s);

/*
 * I nedanstående funktioner är dst en pekare till en vanlig
 * sträng och inte en istring. Däremot skall minnesutrymmet
 * "konverteras" till en istring av funktionerna, d.v.s. efter att
 * t.ex. istrcpy anropats bör man vid anropsplatsen göra dst =
 * STRING(dst) för att hoppa över längd-delen av strängen.
*/
char *istrcpy(char *dst, const char *src);
char *istrncpy(char *dst, const char *src, size_t n);
char *istrcat(char *dst, const char *src);
char *istrncat(char *dst, const char *src, size_t n);

#endif

