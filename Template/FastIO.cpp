#include <cstdio>
namespace FastIO{
	const int bN = 1e6;
	char buf[bN]; int bp;
	void FastIOinit(){
		fread(buf, 1, bN, stdin);
		bp = 0;
	}
	inline void read(int &x) {
		char c; bool sign = false;
		for (c = buf[bp++]; c < '0' || c > '9'; c = buf[bp++]) {
			if (c == '-') sign = true;
			if (bp == bN) FastIOinit();
		}
		for (x = 0; c >= '0' && c <= '9'; c = buf[bp++]) {
			x = x * 10 + c - '0';
			if (bp == bN) FastIOinit();
		}
		if (sign) x = -x;
		if (bp == bN) FastIOinit();
	}
}
using namespace FastIO;
int main(){
	FastIOinit();
	int n;
	read(n);
	printf("%d\n", n);
}

