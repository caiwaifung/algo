#include <iostream>
using namespace std;

typedef long long int64;

int64 gcd(int64 a, int64 b) {
    return b==0 ? a : gcd(b, a%b);
}

class Fraction {
public:
    int64 a, b; // num = a/b
    
    Fraction (int64 _a = 0LL) {
        a = _a, b = 1LL;
    }
    
    Fraction (int64 _a, int64 _b) {
        //cout << "create fraction: "<<_a<<" / "<<_b<<endl;
        a = _a, b = _b;
        adjust();
    }
    
    void adjust() {
        int c = gcd(a, b);
        a /= c;
        b /= c;
        if (b < 0) a = -a, b = -b;
    }
    
    bool isPositive() {
        return a > 0;
    }
    
    friend Fraction operator +(const Fraction &a, const Fraction &b) {
        int64 ca = a.b / gcd(a.b, b.b);
        int64 cb = b.b / gcd(a.b, b.b);
        return Fraction(a.a*cb + b.a*ca, a.b*cb);
    }
    
    friend Fraction operator -(const Fraction &a, const Fraction &b) {
        int64 ca = a.b / gcd(a.b, b.b);
        int64 cb = b.b / gcd(a.b, b.b);
        return Fraction(a.a*cb - b.a*ca, a.b*cb);
    }
    
    friend Fraction operator *(const Fraction &a, const Fraction &b) {
        return Fraction(a.a*b.a, a.b*b.b);
    }
    
    friend Fraction operator /(const Fraction &a, const Fraction &b) {
        return Fraction(a.a*b.b, a.b*b.a);
    }
    
    friend bool operator ==(const Fraction &a, const Fraction &b) {
        return a.a*b.b == a.b*b.a;
    }
    
    friend bool operator <(const Fraction &a, const Fraction &b) {
        return (b-a).isPositive();
    }
    
    friend bool operator >(const Fraction &a, const Fraction &b) {
        return (a-b).isPositive();
    }
    
    friend bool operator <=(const Fraction &a, const Fraction &b) {
        return a < b || a == b;
    }
    
    friend bool operator >=(const Fraction &a, const Fraction &b) {
        return a > b || a == b;
    }
};

char num_str[100][20];
pair<Fraction, int> num[100];
pair<pair<int, Fraction>, int> list[100];
int round[100];
int n;

void go(int dep, Fraction st, Fraction en, int si, int ei) {
    if (dep > 30) {
        for (int i = si; i <= ei; i ++)
            round[num[i].second] = dep;
        return;
    }
    if (si > ei) return;
    //printf("dep=%d st=%.15lf en=%.15lf si=%d ei=%d\n", dep, st.a/(double)st.b, en.a/(double)en.b, si, ei);
    Fraction m1 = (st * Fraction(2) + en) / Fraction(3);
    Fraction m2 = (st + en * Fraction(2)) / Fraction(3);
    int i = si;
    while (i <= ei && num[i].first < m1) {
        //printf("  %lld/%lld < %lld/%lld\n", num[i].first.a, num[i].first.b, m1.a, m1.b);
        //cout<<num[i].first.a<<"/"<<num[i].first.b<<" < "<<m1.a<<"/"<<m1.b<<endl;
        i ++;
    }
    go(dep+1, st, m1, si, i-1);
    while (i <= ei && num[i].first <= m2)
        round[num[i ++].second] = dep;
    go(dep+1, m2, en, i, ei);
}

void solve(int cs) {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        scanf("%s", num_str[i]);
        num[i].first.a = 0;
        num[i].first.b = 1;
        //cout<<num[i].first.a<<"/"<<num[i].first.b<<endl;
        for (int k = 2; k < strlen(num_str[i]); k ++) {
            num[i].first.a = num[i].first.a*10LL + (int)(num_str[i][k]-'0');
            num[i].first.b *= 10LL;
        }
        //cout<<num[i].first.a<<"/"<<num[i].first.b<<endl;
        num[i].first.adjust();
        num[i].second = i;
    }
    for (int i = 0; i < n; i ++)
        list[i] = make_pair(make_pair(0xFF, num[i].first), i);
    sort(num, num+n);
    go(1, Fraction(0), Fraction(1), 0, n-1);
    for (int i = 0; i < n; i ++)
        list[i].first.first = round[i];
    /*
    for (int i = 0; i < n; i ++) {
        printf("round[%d] = %d\n", i, round[i]);
        //printf("list[%d].second = %d\n", i, round[i]);
    }*/
    sort(list, list+n);
    /*
    for (int i = 0; i < n; i ++) {
        printf("list[%d].second = %d\n", i, list[i].second);
        printf("list[%d].first.second = %I64d / %I64d\n", i, list[i].first.second.a, list[i].first.second.b);
    }
    */
    printf("Case #%d:\n", cs);
    for (int i = 0; i < n; i ++)
        printf("%s\n", num_str[list[i].second]);
}

int main() {
    freopen("A-large-practice.in", "r", stdin);
    freopen("A-large-practice.out", "w", stdout);
    int cs;
    scanf("%d", &cs);
    for (int i = 1; i <= cs; i ++)
        solve(i);
    return 0;
}
