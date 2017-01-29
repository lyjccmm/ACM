#include <cstdio>
#include <algorithm>
#define gcd(a, b) (std::__gcd(a, b))
#define lcm(a, b) (a/gcd(a, b)*b)
using namespace std;
typedef long long LL;
struct fract{
	LL a, b;
	//fract(){}
	fract(LL _a=0, LL _b=1):a(_a), b(_b){up(a, b);}
	void up(LL &a, LL &b){
		LL g = gcd(a, b);
		a /= g, b /= g;
	}
	fract inv(){return fract(b, a);}
	LL retLL(){return a/b;}
	double retDB(){return 1.*a/b;}
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
1/-10
1/5
4/5
0.800000
0
*/
