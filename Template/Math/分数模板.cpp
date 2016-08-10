#include <cstdio>
#include <algorithm>
typedef long long LL;
struct fract{
	LL a, b;
	fract(){}
	fract(LL _a, LL _b){
		a = _a;
		b = _b;
		up();
	}
	void up(){
		LL g = std::__gcd(a, b);
		a /= g;
		b /= g;
		if(b < 0) a = -a, b = -b;
	}
	fract operator + (const fract &ot) const{
		LL aa = a * ot.b + ot.a * b;
		LL bb = b * ot.b;
		return fract(aa, bb);
	}
	fract operator - (const fract &ot) const{
		LL aa = a * ot.b - ot.a * b;
		LL bb = b * ot.b;
		return fract(aa, bb);
	}
	fract operator * (const fract &ot) const{
		LL aa = a * ot.a;
		LL bb = b * ot.b;
		return fract(aa, bb);
	}
	fract operator / (const fract &ot) const{
		LL aa = a * ot.b;
		LL bb = b * ot.a;
		return fract(aa, bb);
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
}
