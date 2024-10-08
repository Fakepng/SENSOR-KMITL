#include "sort.h"

int ascending(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int descending(const void* a, const void* b) {
  return (*(int*)b - *(int*)a);
}