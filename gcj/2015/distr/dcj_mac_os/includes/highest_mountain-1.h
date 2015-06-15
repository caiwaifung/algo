// Sample input 1, in CPP.

#include <cassert>

int NumberOfPeaks() {
  return 4;
}

int GetHeight(long long i) {
  switch ((int)i) {
    case 0: return 3;
    case 1: return 1;
    case 2: return 2;
    case 3: return 4;
    default: assert(0);
  }
}
