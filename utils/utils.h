#define MEM_ALLOC_FAILED "Error calling malloc. Pointer is NULL."
#define REALLOC_FAILED "Error calling realloc. Pointer is NULL."
#define self(X) (&X)
#include "utils.c"
#include <stdbool.h>

void panic(const char *errorMessage);
bool is_null_ptr(void *ptr);
void malloc_failed();
void realloc_failed();
