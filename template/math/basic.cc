namespace MathBasic {
    const LL MOD=LL(1e9)+7;
    LL pow(LL a, LL b) {
        LL t=1;
        for(; b>0; b>>=1, a=a*a%MOD)
            if(b&1) t=t*a%MOD;
        return t;
    }
    LL inv(LL a) {
        return pow(a, MOD-2);
    }
    LL binom(LL n, LL k) {
        LL u=1, v=1;
        forint(i, 1, k) {
            u=u*(n-i+1)%MOD;
            v=v*i%MOD;
        }
        return u*inv(v)%MOD;
    }
};
using namespace MathBasic;
