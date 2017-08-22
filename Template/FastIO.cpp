#include <cstdio>
namespace FastIO{
	const int bN = 1;
	char buf[bN]; int bp, sz;
	inline bool IOinit() {
		sz = fread(buf, 1, bN, stdin);
		bp = 0;
		return sz != 0;
	}
	inline bool IOcheck() {
		if (bp == sz) {
			if(sz == bN) return IOinit();
			else return false;
		}
		return true;
	}
	inline bool read(int &x) {
		if (!IOcheck()) return false;
		char c; bool sign = false;
		for (c = buf[bp++]; c < '0' || c > '9'; c = buf[bp++]) {
			if (c == '-') sign = true;
			if (!IOcheck()) return false;
		}
		for (x = 0; c >= '0' && c <= '9'; c = buf[bp++]) {
			x = x * 10 + c - '0';
			if (!IOcheck()) return false;
		}
		if (sign) x = -x;
		return true;
	}
}
using namespace FastIO;
int main(){
	IOinit();
	int n;
	read(n);
	printf("%d\n", n);
}
