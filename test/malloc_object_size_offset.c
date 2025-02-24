#include <stdbool.h>
#include <stdlib.h>

#include "test_util.h"

size_t malloc_object_size(void *ptr);

OPTNONE int main(void) {
  char *p = malloc(16);
  size_t size = malloc_object_size(p + 5);
  return size != (SLAB_CANARY ? 19 : 27);
}
