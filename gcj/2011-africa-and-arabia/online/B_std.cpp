/*
 E-Mail : amr.9102@gmail.com
 */

#include <cstring>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <complex>
#include <list>
#include <climits>
#include <cctype>

using namespace std;

#include <ext/hash_set>
#include <ext/hash_map>

using namespace __gnu_cxx;

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) ((int)v.size())
#define mem(a,b) memset(a,b,sizeof(a))
#define mp make_pair
#define dot(a,b) ((conj(a)*(b)).X)
#define X real()
#define Y imag()
#define length(V) (hypot((V).X,(V).Y))
#define vect(a,b) ((b)-(a))
#define cross(a,b) ((conj(a)*(b)).imag())
#define normalize(v) ((v)/length(v))
#define rotate(p,about,theta) ((p-about)*exp(point(0,theta))+about)
#define pointEqu(a,b) (comp(a.X,b.X)==0 && comp(a.Y,b.Y)==0)

typedef stringstream ss;
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
typedef complex<double> point;
typedef pair<point, point> segment;
typedef pair<double, point> circle;
typedef vector<point> polygon;

const int oo = (int) 1e9;
const double PI = 2 * acos(0.0);
const double eps = 1e-9;

inline int comp(const double &a, const double &b) {
  if (fabs(a - b) < eps)
    return 0;
  return a > b ? 1 : -1;
}

int di[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
int dj[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
int diK[] = { -2, -2, -1, 1, 2, 2, 1, -1 };
int djK[] = { -1, 1, 2, 2, 1, -1, -2, -2 };

int R, C;

inline bool val(const int &i, const int &j) {
  if (i < 0 || j < 0 || i >= R || j >= C)
    return false;
  return true;
}

int N;
int n;

const int SIZE = 1010;

int rnk[SIZE];
map<int, int> cntOdd, cntSz;

struct DisjointSet {
  int parent[SIZE], rank[SIZE];
  int comp; // number of components
  DisjointSet(int n) {
    comp = n;
    memset(rank, 0, sizeof(rank));
    for (int i = 0; i < n; i++)
      parent[i] = i; // all nodes are parents of ther selves
  }
  int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]); // find node parent -- exist on any component
  }
  void join(int x, int y) {// merge 2 components with node x and node y
    int xf = find(x);
    int yf = find(y);
    if (xf == yf)
      return;
    if (rank[xf] == rank[yf])
      rank[xf]++;
    if (rank[xf] < rank[yf])
      swap(xf, yf);
    parent[yf] = xf;
    comp--;
  }
};

#define SMALL
//#define LARGE

int main() {
  freopen("a.txt", "rt", stdin);
#ifdef SMALL
  freopen("B-small-practice.in", "rt", stdin);
  freopen("B-small-practice-std.out", "wt", stdout);
#endif
#ifdef LARGE
  freopen("B-large-practice.in", "rt", stdin);
  freopen("B-large-practice-std.out", "wt", stdout);
#endif

  cin >> N;
  for (int nn = 1; nn <= N; ++nn) {
    cout << "Case #" << nn << ": ";
    cin >> n;
    int r;
    cin >> r;
    DisjointSet ds(n);
    memset(rnk, 0, sizeof rnk);
    for (int i = 0; i < r; ++i) {
      int a, b;
      cin >> a >> b;
      rnk[a]++;
      rnk[b]++;
      ds.join(a, b);
    }
    cntOdd.clear();
    cntSz.clear();
    for (int i = 0; i < n; ++i) {
      cntOdd[ds.find(i)] += (rnk[i] % 2);
      cntSz[ds.find(i)]++;
    }
    int cnt_size = 0;
    for (map<int, int>::iterator it = cntSz.begin(); it != cntSz.end(); it++) {
      if (it->second > 1)
        cnt_size++;
    }
    //    cerr << cnt_size << endl;
    int res;
    if (cnt_size > 1) {
      res = cnt_size;
      for (map<int, int>::iterator it = cntOdd.begin(); it != cntOdd.end(); it++) {
        res += max(0, it->second / 2 - 1);
      }
    } else {
      res = 0;
      for (map<int, int>::iterator it = cntOdd.begin(); it != cntOdd.end(); it++) {
        res += it->second / 2;
      }
    }
    cout << res << endl;
#ifdef SMALL
    cerr << nn << " of " << N << " is done." << endl;
#endif
#ifdef LARGE
    cerr << nn << " of " << N << " is done." << endl;
#endif
  }
  return 0;
}
