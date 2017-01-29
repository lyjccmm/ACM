#include <cstdio>
#include <algorithm>
#define gcd(a, b) (std::__gcd(a, b))
#define lcm(a, b) (a/gcd(a, b)*b)
using namespace std;
typedef long long LL;
struct fract{
	LL a, b;
	fract(LL _a=0, LL _b=1):a(_a), b(_b){up();upop();}
	void upop(){
		if(b < 0) a = -a, b = -b;
	}
	void up(){
		LL g = gcd(a, b);
		a /= g, b /= g;
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
		LL t1 = a*ot.b, t2 = b*ot.a;
		if(t1 / ot.b == a && t2 / b == ot.a) return t1 < t2;
		else return this->retLDB() < ot.retLDB();
	}
	bool operator == (const fract &ot) const{
		return a == ot.a && b == ot.b;
	}
	bool operator > (const fract &ot) const{
		return !(*this < ot || *this == ot);
	}
	fract operator + (const fract &ot) const{
		LL g = gcd(b, ot.b);
		return fract(ot.b/g*a + ot.a/g*b, b/g*ot.b);
	}
	fract operator - (const fract &ot) const{
		LL g = gcd(b, ot.b);
		return fract(ot.b/g*a - ot.a/g*b, b/g*ot.b);
	}
	fract operator * (const fract &ot) const{
		LL g1 = gcd(a, ot.b), g2 = gcd(b, ot.a);
		return fract((a/g1)*(ot.a/g2), (b/g2)*(ot.b/g1));
	}
	fract operator / (const fract &ot) const{
		LL g1 = gcd(a, ot.a), g2 = gcd(b, ot.b);
		return fract((a/g1)*(ot.b/g2), (b/g2)*(ot.a/g1));
	}
};
int main(){
	fract a = fract(2, 5);
	fract b = fract(1, 2);
	fract c = a + b;
	fract d = a - b;
	fract e = a * b;
	fract f = a / b;
	printf("%lld/%lld\n", c.a, c.b);
	printf("%lld/%lld\n", d.a, d.b);
	printf("%lld/%lld\n", e.a, e.b);
	printf("%lld/%lld\n", f.a, f.b);
	printf("%f\n", f.retDB());
	printf("%lld\n", f.retLL());
}
/*
9/10
-1/10
1/5
4/5
0.800000
0
*/
