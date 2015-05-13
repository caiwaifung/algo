Point a[MAXN];
int n;

struct Face {
	int i, j, k;
	Face(int i, int j, int k) : i(i), j(j), k(k) {}
	Face() {}
};

Face lst[MAXN*5];
int len;

Point get_normal(int i, int j, int k) {
	return mult(a[i], a[j], a[k]);
}

bool facing(int i, Face f) {
	Point normal=get_normal(f.i, f.j, f.k);
	Point p=a[f.i]-a[i];
	return sgn(dot(normal, p))>0;
}

void init() {
	int i=1, j=2;
	while(a[i]==a[j]) ++j;
	int k=1;
	while(sameline(a[i], a[j], a[k])) ++k;
	forint(l, 1, n) {
		forint(t, 0, 1) {
			Face f(i, k, j);
			if(facing(l, f)) {
				len=4;
				lst[1]=Face(i, j, k);
				lst[2]=Face(j, i, l);
				lst[3]=Face(k, j, l);
				lst[4]=Face(i, k, l);
				return;
			}
			swap(i, j);
		}
	}
	printf("ERRO!\n");for(;;);
}

Face tl[MAXN*5];
int cc[MAXN][MAXN];
int tn;
Point normal[MAXN*5];

bool same_normal(Point p1, Point p2) {
	double s1=fabs(p1.x)+fabs(p1.y)+fabs(p1.z);
	double s2=fabs(p2.x)+fabs(p2.y)+fabs(p2.z);
	if(sgn(s1)==0) return sgn(s2)==0;
	if(sgn(s2)==0) return sgn(s1)==0;
	if(sgn(s1)!=sgn(s2)) return false;
	p1=p1*s2;
	p2=p2*s1;
	return p1==p2;
}

void solve() {
	init();
	fillchar(cc, 0);
	forint(i, 1, n) {
		tn=0;
		for(int j=1; j<=len; )
			if(facing(i, lst[j])) {
				tl[++tn]=lst[j];
				lst[j]=lst[len--];
			} else ++j;
		if(tn==0) continue;
		forint(j, 1, tn) {
			Face f=tl[j];
			++cc[f.i][f.j];
			++cc[f.j][f.k];
			++cc[f.k][f.i];
		}
		forint(j, 1, tn) {
			Face f=tl[j];
			forint(t, 1, 3) {
				if(cc[f.j][f.i]==0)
					lst[++len]=Face(i, f.i, f.j);
				int mm=f.i; f.i=f.j; f.j=f.k; f.k=mm;
			}
		}
		forint(j, 1, tn) {
			Face f=tl[j];
			--cc[f.i][f.j];
			--cc[f.j][f.k];
			--cc[f.k][f.i];
		}
	}
	forint(i, 1, len)
		normal[i]=get_normal(lst[i].i, lst[i].j, lst[i].k);
	int ans=0;
	forint(i, 1, len) {
		bool flag=true;
		forint(j, 1, i-1) if(same_normal(normal[i], normal[j]))
			flag=false;
		if(flag) ++ans;
	}
	printf("%d\n", ans);
}
