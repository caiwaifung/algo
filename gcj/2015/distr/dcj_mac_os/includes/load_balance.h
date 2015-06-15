// Sample input 3, in C.

#include <assert.h>

int GetN() {
  return 7;
}

long long GetWeight(long long i) {
  switch ((int)i) {
    case 0: return 1LL;
    case 1: return 2LL;
    case 2: return 3LL;
    case 3: return 4LL;
    case 4: return 5LL;
    case 5: return 6LL;
    case 6: return 21LL;
    default: assert(0);
  }
}
