#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;

inline int clz(int x){return __builtin_clz(x);}
inline int clz(LL x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(LL x){return !x ? -1 : 63-clz(x);}


//sa[0]一般是字符串结尾的空字符,所以sa从1开始是所有后缀串
//rk和sa相反,所以rk[len]一般是0
//h[i]是sa[i]和sa[i-1]的公共前缀的长度,所以h[1]一般是0,而h[0]本身不存在所以也是0
int sa[N], rk[N], h[N], st[20][N];
void da (char *s,int n,int m) { //n是s的长度+1,m是字符种类数量,一般128
	static int t1[N], t2[N], c[N];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, sizeof(c[0])*m);
	for (i=0; i<n; i++) c[x[i]=s[i]]++;
	for (i=1; i<m; i++) c[i] += c[i-1];
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, sizeof(c[0])*m);
		for (i=0; i<n; i++) c[x[i]] ++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]]==y[sa[i-1]] &&
				y[sa[i]+k]==y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (i=0, k=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);

	memcpy (st[0], h, sizeof(h[0])*n);
	for (k=1; 1<<k<=n; k++)
		for (i=0; i+(1<<k)-1<n; i++)
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
}

int getlcp (int i,int j) {
	if (i > j) swap (i, j);
	++ i;
	int f = lg2(j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}
char str[105] = "cbaaacbaaacbabcdd";
int len;
int main(){
	len = strlen(str);
	da(str, len+1, 128);
	//输出排序
	for(int i = 0; i <= len; ++ i){
		puts(str+sa[i]);
	}
	//输出rk
	for(int i = 0; i <= len; ++ i){
		printf("rk[%d] = %d\n", i, rk[i]);
	}
	//输出h
	for(int i = 0; i <= len; ++ i){
		printf("h[%d] = %d\n", i, h[i]);
	}
	//测试lcp
	printf("lcp[%d,%d] = %d\n", 0, 5, getlcp(rk[0], rk[5]));
	printf("lcp[%d,%d] = %d\n", 2, 3, getlcp(rk[2], rk[3]));
	printf("lcp[%d,%d] = %d\n", 0, 10, getlcp(rk[0], rk[10]));
}
