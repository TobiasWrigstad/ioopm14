#include <math.h>

struct vector;
typedef struct vector *Vector;

Vector vector_mk(int size, double values[]);

Vector vector_add(Vector v1, Vector v2);

double vector_abs(Vector v);
