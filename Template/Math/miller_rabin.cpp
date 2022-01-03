// 米勒罗宾判素数
// SPOJ Prime or Not
// https://www.spoj.com/problems/PON/
#include <iostream>
typedef long long LL;
// 18位素数：154590409516822759
// 19位素数：2305843009213693951 (梅森素数)
// 19位素数：4384957924686954497
LL prime[] = {2, 3, 5, 233, 331};
int prime_num = 5;
LL mul_mod(LL a, LL b, LL p) { //快速乘，计算a*b%p
    // return a * b % p;
    LL ret = 0;
    while (b) {
        if (b & 1) ret = (ret + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ret;
}
LL pow_mod(LL a, LL b, LL p) { //快速幂，计算a^b%p
    LL ret = 1;
    while (b) {
        if (b & 1) ret = mul_mod(ret, a, p);
        a = mul_mod(a, a, p);
        b >>= 1;
    }
    return ret;
}
bool miller_rabin_check(LL a, LL num, LL d, LL r) {
    LL x = pow_mod(a, d, num);
    if (x == 1 || x == num - 1) return true; //最终的余数是1或n-1则可能是素数
    while (r --) { //考虑开始在不断地往下余的过程
        x = mul_mod(x, x, num);
        if (x == 1) return false;
        if (x == num - 1) return true; //中间如果有一个余数是n-1说明中断了此过程，则可能是素数
    }
    return false; //否则如果中间没有中断但最后是余数又不是n-1和1说明一定不是素数
}
bool miller_rabin(LL num) {
    if (num == 2) return true;
    if (num < 2 || !(num & 1)) return false;
    LL d = num - 1;
    LL r = 0;
    while ((d & 1) == 0) { // num-1 分解成 d * 2^r，d为奇数
        d >>= 1;
        ++ r;
    }
    for (int i = 0; i < prime_num; ++ i) {
        if (prime[i] >= num) continue;
        if(!miller_rabin_check(prime[i], num, d, r)) return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    int T;
    std::cin >> T;
    for (int cas = 1; cas <= T; ++ cas) {
        LL num;
        std::cin >> num;
        if (miller_rabin(num)) {
            std::cout << "YES" << std::endl;
        } 
        else {
            std::cout << "NO" << std::endl;
        }
    }
}
