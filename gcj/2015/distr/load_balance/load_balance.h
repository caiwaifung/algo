// Sample input 1, in C.

#include <assert.h>

int GetN() {
  return 4;
}

long long GetWeight(long long i) {
  switch ((int)i) {
    case 0: return 1LL;
    case 1: return 1LL;
    case 2: return 1LL;
    case 3: return 1LL;
    default: assert(0);
  }
}
