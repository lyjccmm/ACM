//http://codeforces.com/problemset/problem/305/B
#include <cstdio>
#include <algorithm>
#include <iostream>
#define gcd(a, b) (std::__gcd(a, b))
#define lcm(a, b) (a/gcd(a, b)*b)
using namespace std;
typedef long long LL;
const int N = 110;
struct fract{
	LL a, b;
	fract(LL _a=0, LL _b=1):a(_a), b(_b){up();upop();}
	fract err() const{ //error
		fract ret;
		ret.a = 0, ret.b = 0;
		return ret;
	}
	void upop(){ //update_operator
		if(b < 0) a = -a, b = -b;
	}
	void up(){ //update
		LL g = gcd(a, b);
		a /= g, b /= g;
	}
	bool of(LL a, LL b) const{ //overflow
		if(b != 0 && a*b/b != a) return true;
		else return false;
	}
	fract inv() const{return fract(b, a);}
	LL retLL() const{return a/b;}
	double retDB() const{return 1.*a/b;}
	long double retLDB() const{return (long double)a/b;}
	bool operator < (LL &ot) const{
		return retLL() < ot;
	}
	bool operator == (LL &ot) const{
		return b == 1 && a == ot;
	}
	bool operator > (LL &ot) const{
		return !(*this < ot || *this == ot);
	}
	bool operator < (const fract &ot) const{
		if(!of(a, ot.b) && !of(ot.a, b)) return a*ot.b < b*ot.a;
		else return this->retLDB() < ot.retLDB();
	}
	bool operator == (const fract &ot) const{
		return a == ot.a && b == ot.b;
	}
	bool operator > (const fract &ot) const{
		return !(*this < ot || *this == ot);
	}
	fract operator - () const{
		return fract(-this->a, this->b);
	}
	fract operator + (const fract &ot) const{
		LL g = gcd(b, ot.b);
		if(of(ot.b/g, a) || of(ot.a/g, b) || of(b/g, ot.b)) return err();
		LL aa = ot.b/g*a + ot.a/g*b;
		LL bb = b/g*ot.b;
		return fract(ot.b/g*a + ot.a/g*b, b/g*ot.b);
	}
	fract operator - (const fract &ot) const{
		return *this + (-ot);
	}
	fract operator * (const fract &ot) const{
		LL g1 = gcd(a, ot.b), g2 = gcd(b, ot.a);
		if(!of(a/g1, ot.a/g2) && !of(b/g2, ot.b/g1)) return fract((a/g1)*(ot.a/g2), (b/g2)*(ot.b/g1));
		else return err();
	}
	fract operator / (const fract &ot) const{
		return *this * ot.inv();
	}
};
LL p, q;
int n;
LL a[N];
void solve(){
	fract tmp = fract(p, q);
	for(int i = 0; i < n; i ++){
		tmp = tmp - fract(a[i]);
		if(tmp.b == 0) {
			puts("NO");
			return ;
		}
		tmp = tmp.inv();
	}
	tmp = tmp.inv();
	if(tmp == 0) puts("YES");
	else puts("NO");
}
int main(){
	cin >> p >> q;
	cin >> n;
	for(int i = 0; i < n; i ++) cin >> a[i];
	solve();	
}
