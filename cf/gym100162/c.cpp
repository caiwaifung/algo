#include <vector>
#include <cstdio>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define PB push_back
#define MP make_pair
const int MAXLen=10000010;
const int MAXT=11;

char str[MAXLen];
int matched[MAXLen], stack[MAXLen], top;
int len;

struct Set {
	bool neg;
	set<int> *s;
	int count() const {
		if(neg) return 1000000000-s->size();
		return s->size();
	}
};

set<int>* s_and(set<int> *a, set<int> *b) { // a & b
	if(a->size()>b->size()) swap(a, b);
	// now a<b
	set<int> *c=new set<int>();
	for(set<int>::iterator it=a->begin(); it!=a->end(); ++it)
		if(b->find(*it)!=b->end())
			c->insert(*it);
	//delete a;
	//delete b;
	return c;
}

set<int>* s_or(set<int> *a, set<int> *b) { // a | b
	if(a->size()>b->size()) swap(a, b);
	// now a<b
	for(set<int>::iterator it=a->begin(); it!=a->end(); ++it)
		b->insert(*it);
	//delete a;
	return b;
}

set<int>* s_andnot(set<int> *a, set<int> *b) { // a & !b
	if(a->size()>b->size()) {
		for(set<int>::iterator it=b->begin(); it!=b->end(); ++it)
			a->erase(*it);
		//delete b;
		return a;
	} else {
		set<int> *c=new set<int>();
		for(set<int>::iterator it=a->begin(); it!=a->end(); ++it)
			if(b->find(*it)==b->end())
				c->insert(*it);
		//delete a;
		//delete b;
		return c;
	}
}

Set set_and(Set a, Set b) {
	if(!a.neg && !b.neg) {
		Set c;
		c.neg=false;
		c.s=s_and(a.s, b.s);
		return c;
	}
	if(a.neg && b.neg) {
		Set c;
		c.neg=true;
		c.s=s_or(a.s, b.s);
		return c;
	}
	if(!a.neg && b.neg) { // a.s & !b.s
		Set c;
		c.neg=false;
		c.s=s_andnot(a.s, b.s);
		return c;
	} else {
		Set c;
		c.neg=false;
		c.s=s_andnot(b.s, a.s);
		return c;
	}
}

Set set_or(Set a, Set b) {
	if(!a.neg && !b.neg) {
		Set c;
		c.neg=false;
		c.s=s_or(a.s, b.s);
		return c;
	}
	if(a.neg && b.neg) {
		Set c;
		c.neg=true;
		c.s=s_and(a.s, b.s);
		return c;
	}
	if(!a.neg && b.neg) { // (a.s | !b.s) = !(b.s & !a.s)
		Set c;
		c.neg=true;
		c.s=s_andnot(b.s, a.s);
		return c;
	} else {
		Set c;
		c.neg=true;
		c.s=s_andnot(a.s, b.s);
		return c;
	}
}

Set get_set(int le, int ri) {
	Set a;
	a.neg=false;
	a.s=new set<int>();
	if(le>ri) return a;
	int x=0;
	forint(i, le, ri) {
		if(str[i]==',') {
			a.s->insert(x);
			x=0;
		} else x=x*10+int(str[i]-'0');
	}
	a.s->insert(x);
	return a;
}

struct Item {
	char c;
	Set s;
	Item(char c) : c(c) {}
	Item(Set s) : c(' '), s(s) {}
};

Set compute(vector<Item> s) {
	vector<Set> t;
	bool la_and=false, neg=false;
	forn(i, s.size()) {
		if(s[i].c=='!') {
			neg=!neg;
		} else if(s[i].c=='&') {
			la_and=true;
		} else if(s[i].c=='|') {
			la_and=false;
		} else if(s[i].c==' ') {
			Set cur=s[i].s;
			if(neg) {
				cur.neg=!cur.neg;
				neg=false;
			}
			//printf("@1\n");
			if(t.size()>0 && la_and)
				t[t.size()-1]=set_and(t.back(), cur);
			else
				t.PB(cur);
			//printf("@2\n");
		} else {
			printf("compute error: invalid char [%c]\n", s[i].c);
		}
	}
	forint(i, 1, t.size()-1) t[0]=set_or(t[0], t[i]);
	return t[0];
}

int pri(char c) {
	if(c=='!') return 0;
	if(c=='&') return 1;
	if(c=='|') return 2;
	if(c==')') return 3;
	if(c=='(') return 4;
	return -1;
}

vector<Set> s;
vector<char> o;
void do_op() {
	if(o.back()=='&') {
		s[s.size()-2]=set_and(s[s.size()-2], s[s.size()-1]);
		s.pop_back();
		o.pop_back();
	} else if(o.back()=='|') {
		s[s.size()-2]=set_or(s[s.size()-2], s[s.size()-1]);
		s.pop_back();
		o.pop_back();
	} else if(o.back()=='!') {
		s[s.size()-1].neg^=true;
		o.pop_back();
	}
}

Set get() {
	s.clear(); o.clear();
	//vector<vector<Item> > s;
	//s.PB(vector<Item>());
	for(int i=1; i<=len; ++i) {
		if(str[i]=='{') {
			Set cur=get_set(i+1, matched[i]-1);
			i=matched[i];
			s.PB(cur);
		} else if(str[i]=='(') {
			o.PB(str[i]);
		} else {
			while(o.size()>0 && pri(str[i])>pri(o.back()))
				do_op();
			if(str[i]==')')
				o.pop_back();
			else
				o.PB(str[i]);
			//printf("get error: invalid char [%c]\n", str[i]);
		}
	}
	//if(s.size()!=1) printf("get error: s.size()!=1\n");
	//return compute(s[0]);
	while(o.size()>0) do_op();
	if(s.size()!=1) printf("get error: s.size()!=1\n");
	return s[0];
}

/*
Set get(int le, int ri);
Set extract(int &i) {
	if(str[i]=='!') {
		++i;
		Set a=extract(i);
		a.neg=!a.neg;
		return a;
	}
	if(str[i]=='(') {
		int j=matched[i];
		i=j+1;
		return get(matched[j]+1, j-1);
	}
	if(str[i]=='{') {
		int j=matched[i];
		i=j+1;
		return get_set(matched[j]+1, j-1);
	}
	printf("extract fail: invalid char [%c]\n", str[i]);
	return Set();
}

Set get(int le, int ri) {
	vector<Set> s;
	vector<char> o;
	while(le<=ri) {
		Set a=extract(le);
		s.PB(a);
		if(le<=ri) {
			o.PB(str[le]);
			++le;
		}
	}
	vector<Set> s2;
	s2.PB(s[0]);
	forn(i, o.size()) {
		if(o[i]=='&') {
			s2[s2.size()-1]=set_and(s2[s2.size()-1], s[i+1]);
		} else if(o[i]=='|') {
			s2.PB(s[i+1]);
		} else {
			printf("get fail: invalid op [%c]\n", o[i]);
		}
	}
	forint(i, 1, s2.size()-1)
		s2[0]=set_or(s2[0], s2[i]);
	return s2[0];
}
*/

int main() {
	int cs=0;
	while(1) {
		if(scanf("%s", str+1)<1) break;
		len=strlen(str+1);
		top=0;
		forint(i, 1, len) {
			if(str[i]=='(' || str[i]=='{') stack[++top]=i;
			if(str[i]==')' || str[i]=='}') {
				matched[stack[top]]=i;
				matched[i]=stack[top];
				--top;
			}
		}

		Set s=get();
		//Set s=get(1, len);
		int num=s.count();
		printf("Case %d: %d\n", ++cs, num);
		//delete s.s;
	}
	return 0;
}
