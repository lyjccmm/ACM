#include <cstdio>

int main(){
	double a = 1/2.0;
	double b = 1/6.0;
	double c = 1/3.0;
	double d;

	if(b+c == a){
		printf("%d\n", 111);
	}
	d = b + c;
	if(d == a){
		printf("%d\n", 222);
	}
	printf("%.20f\n", a);
	printf("%.20f\n", d);
}
