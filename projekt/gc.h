/// \file

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef __gc__
#define __gc__

/// The opaque data type holding all the heap data
typedef struct heap_t heap_s;

/// The signature of the trace function 
typedef void *(*trace_f)(heap_s *h, void *obj);

/// The signature of object-specific trace functions. It will be
/// called for its specific objects, and be given a generic trace
/// function f to be called on each pointer inside obj.
typedef void *(*s_trace_f)(heap_s *h, trace_f f, void *obj);

/// Create a new heap with bytes total size (including both spaces
/// and metadata), meaning strictly less than bytes will be
/// available for allocation.
///
/// \param bytes the total size of the heap in bytes
/// \return the new heap
heap_s *h_init(size_t bytes);

/// Delete a heap.
///
/// \param h the heap
void h_delete(heap_s *h);

/// Delete a heap and trace, killing off stack pointers.
///
/// \param h the heap 
/// \param dbg_value a value to be written into every pointer into h on the stack
void h_delete_dbg(heap_s *h, void *dbg_value);

/// Allocate a new object on a heap with a given format string.
///
/// Valid characters in format strings are:
/// - 'd' -- for sizeof(int) bytes 'raw' data
/// - '*' -- for a sizeof(void *) bytes pointer value
/// - '\0' -- null-character terminates the format string
///
/// \param h the heap
/// \param layout the format string
/// \return the newly allocated object
///
/// Note: the heap does *not* retain an alias to layout.
void *h_alloc_struct(heap_s *h, char *layout);

/// Allocate a new object on a heap with a given size, and
/// object-specific trace function.
///
/// \sa s_trace_f
///
/// \param h the heap
/// \param bytes the size in bytes
/// \param f the object-specific trace function
/// \return the newly allocated object
void *h_alloc_union(heap_s *h, size_t bytes, s_trace_f f);

/// Allocate a new object on a heap with a given size.
///
/// Objects allocated with this function will *not* be 
/// further traced for pointers. 
///
/// \param h the heap
/// \param bytes the size in bytes
/// \return the newly allocated object
void *h_alloc_data(heap_s *h, size_t bytes);

/// Manually trigger garbage collection.
///
/// Garbage collection is otherwise run when an allocation is
/// impossible in the available consecutive free memory.
///
/// \param h the heap
/// \return the number of bytes collected
size_t h_gc(heap_s *h);

/// Returns the available consecutive free memory. 
///
/// \param h the heap
/// \return the available consecutive free memory. 
size_t h_avail(heap_s *h);

#endif
