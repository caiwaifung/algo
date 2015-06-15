// Sample input 2, in CPP.

#include <cassert>

int NumberOfPeaks() {
  return 3;
}

int GetHeight(long long i) {
  switch ((int)i) {
    case 0: return 2;
    case 1: return 2;
    case 2: return 2;
    default: assert(0);
  }
}
