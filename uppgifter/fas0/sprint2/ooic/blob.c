#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

/* Objects are encoded in structs and vtables (see below). 
 * Each struct has:
 * - A header which in this case is a pointer to its vtable
 * - Its instance variables just as regular fields in the post
 * 
 * A vtable is an array of pointers to functions that implements
 * methods. All such functions are expected to take a pointer to
 * an object as its first argument. A vtable also has a pointer to
 * the super class' vtable. For simplicity and dynamicity, each
 * vtable also has a list of pointers to signatures encoded as
 * interned strings [1] which is used to calculate offset in the
 * vtable's array of function pointers.
 *
 * For simplicity, there are four types for methods with 0..3 arguments. 
 *
 * A class is represented thus:
 * - A struct of the above format.
 * - A vtable with pointers to all its functions and registered.
 *   signatures to help implement calculate offset.
 * - A number of normal C functions which implement the methods of
 *   the object. 
 * 
 * The helper macro addMethod somewhat simplifies the addition of 
 * methods to vtables. 
 *
 * The helper function mkSelector returns a pointer to an interned
 * string which allows O(1) comparison using ==. 
 *
 * The internal function lookup returns the offset of a function 
 * pointer in a vtable. 
 *
 * Calling a method is as simple as:
 * - call(receiver, selector, number of arguments, arg0, ...);
 * Notably, all arguments must be pointers. 
 */


typedef void*(*method_ptr)(void*); 
typedef void*(*method_arity_zero)(void*); 
typedef void*(*method_arity_one)(void*, void*); 
typedef void*(*method_arity_two)(void*, void*, void*); 
typedef void*(*method_arity_three)(void*, void*, void*, void*); 
typedef int vtable_offset; 
typedef char *selector; 

#define HEADER struct vtable *methods;
#define HEADER_SIZE sizeof(struct vtable*)
#define addMethod(vt,idx,fp,name)			\
  vt->methods[idx] = (method_ptr) fp;			\
  vt->offsets[idx] = mkSelector(name);

typedef struct object {
  HEADER
} *Object;

struct vtable {
  struct vtable *super;
  selector *offsets;
  int upper_bound; 
  method_ptr methods[]; // size = upper_bound
};

// Fix offsets in this struct so every field starts n * N bytes in
struct sequence {
  HEADER 
  unsigned int size; 
  char content[];
};

// Fix offsets in this struct! 
struct string {
  HEADER 
  unsigned int size; 
  char content[];
};

char *string_to_cstring(struct string *this);
void string_puts(struct string *this);
void string_set_from_cstring(struct string *this, char *cstring);
struct string *string_new(unsigned int size);
int sequence_get(struct sequence *this, unsigned int *idx);
void sequence_set(struct sequence *this, unsigned int *idx, char *value);
struct sequence *sequence_new(unsigned int size);
struct vtable *sequenceVtable();
struct vtable *stringVtable(struct vtable *super);
struct vtable *stringVtable(struct vtable *super);
selector mkSelector(const char*);

selector mkSelector(const char *str) {
  static selector cached_selectors[128]; // stupid arbitrary magic number
  static unsigned int selector_index = 0;
  for (int i=0; i<selector_index; ++i) {
    if (strcmp(str,cached_selectors[i]) == 0) return cached_selectors[i];
  }
  return cached_selectors[selector_index++] = strdup(str); 
}

struct vtable *objVtable() {
  return NULL;
}

struct vtable *mkDerivedVtable(unsigned int size, struct vtable *super) {
 struct vtable *newVtable = malloc(sizeof(struct vtable) + sizeof(method_ptr) * size);
 newVtable->super	  = super;
 newVtable->offsets	  = calloc(size + 1, sizeof(char *));
 newVtable->upper_bound	  = 0;
 return newVtable;
}

struct vtable *mkVtable(unsigned int size) {
  return mkDerivedVtable(size, objVtable());
}

struct vtable *sequenceVtable() {
  struct vtable *result = mkVtable(2);
  addMethod(result, 0, sequence_set, "set");
  addMethod(result, 1, sequence_get, "get");
  return result; 
}

struct vtable *stringVtable(struct vtable *super) {
  struct vtable *result = mkDerivedVtable(5, super);
  addMethod(result, 0, sequence_set, "set");
  addMethod(result, 1, sequence_get, "get");
  addMethod(result, 2, string_set_from_cstring, "set_from_cstring");
  addMethod(result, 3, string_to_cstring, "to_cstring");
  addMethod(result, 4, string_puts, "puts");
  return result; 
}

struct sequence *sequence_new(unsigned int size) {
  struct sequence *result = malloc(HEADER_SIZE + sizeof(unsigned int) + sizeof(char) * size);
  if (result) {
    result->methods = sequenceVtable(objVtable());
    result->size = size;
    unsigned int idx = size-1;
    while (idx > 0) {
      result->content[idx--] = 0;
    }
    return result; 
  } else {
    return NULL; 
  }
}

void sequence_set(struct sequence *this, unsigned int *idx, char *value) {
  if (0 <= *idx && *idx < this->size) {
    this->content[*idx] = *value; 
  }
}

int sequence_get(struct sequence *this, unsigned int *idx) {
  if (0 < *idx && this->size < *idx) {
    return this->content[*idx];
  } else {
    return -1; 
  }
}

struct string *string_new(unsigned int size) {
  struct string *result = (struct string *)sequence_new(size); 
  if (result) {
    result->methods = stringVtable(result->methods);
  }
  return result;
}

void string_set_from_cstring(struct string *this, char *cstring) {
  int length = 0;
  while (*cstring && length < this->size-1) {
    this->content[length++] = *(cstring++);
  }
  if (length == this->size-1) {
    this->content[length] = '\0'; 
  }
  this->size = length;
}

void string_puts(struct string *this) {
  puts(this->content);
}

char *string_to_cstring(struct string *this) {
  char *result = malloc(this->size + 1);
  strncpy(result, this->content, this->size);
  result[this->size] = '\0';
  return result; 
}

vtable_offset __lookup(struct vtable *class, selector signature) {
  if (class == NULL) return -1;

  for (int index = 0; class->offsets[index]; ++index) {
    if (class->offsets[index] == signature) return index;
  }

  return __lookup(class->super, signature);
}

vtable_offset lookup(void *receiver, selector signature) {
  return __lookup(((Object) receiver)->methods, signature);
}

void *call(void *receiver, selector signature, int argc, ...) {
  va_list ap;
  va_start(ap, argc);
  void *result = NULL; 
  int index = lookup(receiver, signature);
  assert(index >= 0);
  void *arg1 = NULL;
  void *arg2 = NULL;
  void *arg3 = NULL;

  method_ptr method = ((Object) receiver)->methods->methods[index];

  switch (argc) {
  case 0:
    result = ((method_arity_zero) method)(receiver);
    break;
  case 1:
    arg1 = va_arg(ap, void*);
    result = ((method_arity_one) method)(receiver, arg1);
    break;
  case 2:
    arg1 = va_arg(ap, void*);
    arg2 = va_arg(ap, void*);
    result = ((method_arity_two) method)(receiver, arg1, arg2);
    break;
  case 3:
    arg1 = va_arg(ap, void*);
    arg2 = va_arg(ap, void*);
    arg3 = va_arg(ap, void*);
    result = ((method_arity_three) method)(receiver, arg1, arg2, arg3);
    break;
  default: 
    fprintf(stderr, "Sorry, I don't support calling methods with %d arguments!\n", argc);
    result = NULL; 
  }

  va_end(ap); 
  return result;
}

int main(int argc, char *argv[]) {
  struct string *str = string_new(15);
  int index = 0; 
  char value = 'A';
  char *s = NULL; 
  call(str, mkSelector("set_from_cstring"), 1, "Xnita Ekberg");

  s = call(str, mkSelector("to_cstring"), 0);
  printf("'%s'\n", s);
  call(str, mkSelector("set"), 2, &index, &value);

  s = call(str, mkSelector("to_cstring"), 0);
  printf("'%s'\n", s);
  return 0;
}
