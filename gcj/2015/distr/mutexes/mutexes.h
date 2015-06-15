// Sample input 1, in CPP.

#include <cassert>

int NumberOfOperations(long long i) {
  switch ((int)i) {
    case 0: return 4;
    case 1: return 4;
    default: assert(0);
  }
}

int GetOperation(long long i, long long index) {
  if (i == 0 && index == 0) return 1;
  if (i == 0 && index == 1) return 2;
  if (i == 0 && index == 2) return -2;
  if (i == 0 && index == 3) return -1;
  if (i == 1 && index == 0) return 1;
  if (i == 1 && index == 1) return 2;
  if (i == 1 && index == 2) return -1;
  if (i == 1 && index == 3) return -2;
  assert(0);
}
