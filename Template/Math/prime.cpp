// https://www.cometoj.com/contest/65/problem/C
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2e6 + 10;

// ----------------------------------------------------------------------------- prime_init
// 预处理质数
const int prime_kN = N; //要处理的数字总数量
const int prime_num = N; //预计处理出来质数数量

int is_not_prime[prime_kN];//is_not_prime[i]表示i是不是质数 
int prime[prime_num];//prime用来存质数 
int prime_tot;
void prime_init(){
	memset(is_not_prime, 0, sizeof(is_not_prime));
	for(int i = 2; i < prime_kN; i++){
		if(!is_not_prime[i]) prime[prime_tot ++] = i;//把质数存起来 
		for(int j = 0; j < prime_tot && i * prime[j] < prime_kN; j++){
			is_not_prime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;//保证每个合数被它最小的质因数筛去 
		}
	}    
}
// ----------------------------------------------------------------------------- prime_init end


// ----------------------------------------------------------------------------- prime_factor_process
// 对一个数进行质因数拆解
typedef long long PFP_T; //prime_factor_process type
const int prime_factor_num = 35; //预计处理出来质因数数量

PFP_T prime_factor[prime_factor_num];
int prime_factor_tot;
void prime_factor_process(PFP_T n){
	prime_factor_tot = 0;
	for(int i = 0; i < prime_tot; ++ i){
		if(1ll*prime[i]*prime[i] > n) break;
		while(n % prime[i] == 0){
			prime_factor[prime_factor_tot ++] = prime[i];
			n /= prime[i];
		}
	}
	if(n != 1){
		prime_factor[prime_factor_tot ++] = n;
	}
}
// ----------------------------------------------------------------------------- prime_factor_process end

// ----------------------------------------------------------------------------- factor_process
// 对一个数进行因数拆解
typedef long long FP_T; //factor_process type
const int factor_num = N; //预计处理出来因数数量

FP_T factor[factor_num];
int factor_tot;
void factor_process(FP_T n, int need_sort=0){
	prime_factor_process(n);
	factor_tot = 0;
	factor[factor_tot ++] = 1;

	FP_T num;
	FP_T last_num = 1;
	int last_factor_tot;
	for(int i = 0; i < prime_factor_tot; ++ i){
		if(prime_factor[i] == last_num){
			num *= last_num;
		}
		else{
			num = prime_factor[i];
			last_factor_tot = factor_tot;
		}
		for(int j = 0; j < last_factor_tot; ++ j){
			factor[factor_tot ++] = num * factor[j];
		}
		last_num = prime_factor[i];
	}
	if(need_sort) sort(factor, factor + factor_tot);
}
// ----------------------------------------------------------------------------- factor_process end


LL n, ans, d, x, y, t;
void ex_gcd(LL a, LL b, LL &d, LL &x, LL &y){
	if(!b){d = a; x = 1; y = 0;}
	else{ex_gcd(b, a%b, d, y, x); y -= x*(a/b);}
}

int main(){
	prime_init();
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%lld", &n);
		n <<= 1;
		factor_process(n, 1);
		ans = n-1;
		for(int k = 1; k < factor_tot; ++ k){
			LL i = factor[k];
			LL j = n / i;
			if(i > j) break;
			ex_gcd(i, j, d, x, y);
			if(d == 1){
				t = min(abs(x*i), abs(y*j));
				ans = min(ans, t);
			}
		}
		printf("%lld\n", ans);
	}
}
