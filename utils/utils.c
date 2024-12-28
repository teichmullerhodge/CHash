#pragma once

#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void panic(const char *errorMessage) { perror(errorMessage); }
bool is_null_ptr(void *ptr) { return ptr == NULL; }

void malloc_failed() { perror(MEM_ALLOC_FAILED); }
void realloc_failed() { perror(REALLOC_FAILED); }
