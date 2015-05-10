#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

template<class T> T ext_gcd(T a, T b, T &x, T &y) {
	if(b==0) { x=1, y=0; return a; }
	LL nx, ny, d; d=ext_gcd(b, a%b, nx, ny);
	x=ny, y=nx-(a/b)*ny;
	return d;
}

// ------------------------ template ends here ------------------------ //

class ElectronicPet {
	LL mul(LL a, LL b) {
		const LL inf=LL(1e10);
		if(a*1.0*b>inf) return inf;
		return a*b;
	}
	LL solve(LL p1, LL t1, LL p2, LL t2) {
		LL need1=p1*(t1-1);
		LL need2=p2*(t2-1);
		if(need1<need2) return solve(p2, t2, p1, t1);

		LL z1, z2;
		LL d=ext_gcd(p1, p2, z1, z2);
		if(d>1) {
			if(need1==need2)
				return need1+1;
			else
				return need1;
		}

		// find p1*a1=p2*a2+1
		LL a1=z1, a2=-z2;
		while(a1<0 || a2<0) a1+=p2, a2+=p1;
		while(a1>p2 || a2>p1) a1-=p2, a2-=p1;

		
		LL delta=need1-need2;
		t1-=mul(a1,delta);
		t2-=mul(a2,delta);
		// now (t1-1)*p1=(t2-1)*p2
		LL ans=need1;
		if(t1>0) ans+=(t1-1)/p2+1;
		return ans;
	}
public:
	vector<long long> minimumSec(vector <int> period1, vector <int> time1, vector <int> period2, vector <int> time2) {
		vector<LL> ans;
		forn(i, period1.size())
			ans.PB(solve(period1[_ i], time1[_ i], period2[_ i], time2[_ i]));
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long Arr4[] = {4 }; vector<long long> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, minimumSec(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long Arr4[] = {13 }; vector<long long> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, minimumSec(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {7357,10,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7356,50,1000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {7356,3,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7357,167,900000}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long Arr4[] = {54110737, 510, 2799998 }; vector<long long> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, minimumSec(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {407682800,484877059,830674177,227281073,19285523,560937767,919297611,23531788,
316159340,674806519,329433665,738538481,641235893,765181213,174785202,336152284,
570921683,400867251,774285402,943390771,837295831,294507056,493790893,522227203,
497924687,598834705,475831075,475114141,905813209,170832752,641484603,289813259,
862545694,178944781,755931661,620338556,970867185,83941427,135674814,895365643,
473440918,718282949,499031452,245406771,472643639,857414603,969063773,78465926,
1,7,2,8,7,7,3,8,1,2,8,6,1,7,10,5,3,10,1,5,5,7,1,1,10,9,3,8,5,6,7,3,7,7,5,3,1,4,
9,8,1,5,9,7,4,7,9,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {685321887,561847762,364868210,867285301,914945601,118787805,548332607,31355359,
803650261,960301524,266477641,39110673,474718169,71340489,687134789,493401968,
653058743,55748625,509077445,269937973,742890796,52585495,726357125,68477490,
4,7,9,9,7,6,1,7,3,8,6,9,1,9,9,6,10,6,8,8,10,9,6,5,781250147,170878774,855135226,
549059143,654877349,801427166,673830906,386629440,851395517,900791233,449728383,
250397037,69109668,512878462,27237926,285837889,66688537,91054902,717783650,388278693,
228914249,989188885,502709264,663817744,6,5,7,6,8,7,8,9,8,4,4,8,8,8,6,8,5,3,6,2,7,2,6,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {986705763,927574445,892948254,704066415,535436162,590308252,178891220,743922325,
856566021,518519690,225440136,785919924,5,5,5,9,9,4,7,10,7,9,4,4,818956627,417135379,
248892046,146009149,739277785,109423195,440198141,605525655,728478703,626172069,
630370468,130076349,4,1,5,4,9,10,3,1,4,9,3,1,583089191,388870099,453827819,111516603,
844765437,521615016,829962743,292223139,131621553,188850119,791754731,848542169,10,8,
1,9,10,3,9,4,3,4,4,4,278700059,895269545,67783376,711864145,956734152,422403629,
81840569,351747691,160762278,343337051,756026313,407474198,3,1,2,5,6,7,8,9,7,8,1,9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {682390001,180499376,576561187,900180870,848774944,346873906,2,8,3,10,6,5,699143960,
814962202,251766107,732807531,131595022,598147784,3,2,3,3,7,10,637954336,380997052,
636675367,968908554,354172494,436377372,1,8,7,7,8,3,419710297,126884289,571143414,
264634798,264801163,157605826,4,4,6,8,5,5,485199156,117420995,773034099,419801566,
687631343,469269453,4,6,6,7,5,9,456349996,696828998,843725003,829027352,369267156,
515309802,7,6,8,2,10,6,75700282,191511000,510072386,297737413,817129266,664602545,
8,6,10,2,6,2,325802862,171214036,503091306,72109356,917444714,754965240,1,2,10,9,5,8}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long Arr4[] = {673318145613570000, 272427089959414899, 514839304362869244, 633787117288414635, 454464797881688766, 204762528524964060, 504080854729204266, 737847637120104, 254081535792428400, 648017727926028437, 87786705585750600, 28884736289769232, 304406328380804024, 54588401143851944, 120100992721807176, 165858198137142628, 372845396080502786, 22347797649912624, 394171233376672488, 254656991527256412, 622019365541775645, 15486799026245664, 358668532896871732, 35760807548933267, 522456930371628045, 158927349266767329, 158463434481538836, 141469513282351397, 261831856132968005, 47749806160520345, 1, 4238679585, 4370872218, 3757032414, 4412593276, 4962708448, 1678841184, 671531416, 2855717065, 4476828215, 4260968262, 3591414745, 3493220164, 1717847397, 4253792751, 6859316824, 4845318865, 313863704, 282914382762833605, 45661513561458406, 350824378707972262, 46814844462883695, 580887191119526454, 244777992713291232, 2489888229, 3093035512, 851395522, 1801582464, 3597827056, 6788337352, 4563499950, 5574631976, 870962928, 7461246159, 3692671550, 1545929403, 717783656, 1941393460, 1144571240, 6924322188, 502709273, 663817749, 21097672781016579, 171453964937225455, 34574428259671760, 211948588227892740, 781775474424158280, 280730526428232176, 572883983, 1758738455, 1446860502, 343337051, 3780131565, 407474198, 977408583, 171214043, 1006182610, 360546775, 5504668278, 5284756673, 45, 9, 63, 64, 45, 63 }; vector<long long> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(3, Arg4, minimumSec(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	ElectronicPet ___test;
	/*
	___test.run_test(1);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
