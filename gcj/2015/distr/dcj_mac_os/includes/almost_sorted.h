// Sample input 3, in C.

#include <assert.h>

#include <stdbool.h>

long long NumberOfFiles() {
  return 5LL;
}

long long MaxDistance() {
  return 4LL;
}

long long Identifier(long long i) {
  switch ((int)i) {
    case 0: return 1000000LL;
    case 1: return 2000000LL;
    case 2: return 4000000LL;
    case 3: return 3000000LL;
    case 4: return 5000000LL;
    default: assert(0);
  }
}
