//敌兵布阵 HDU 1166
//题目链接 
//http://acm.hdu.edu.cn/showproblem.php?pid=1166
///////////////////////////////////////////////////////////////////////
//普通线段树 
#include<cstdio>
#include<cstring> 
#define t_mid (l + r >> 1)
#define ls (o << 1)
#define rs (o << 1 | 1)
#define lson ls, l, t_mid
#define rson rs, t_mid+1, r
const int N = 50000 + 5;
int n;
int a[N], c[N << 2];
char str[15];
void up(int o){
	c[o] = c[ls] + c[rs];
}
int build(int o, int l, int r){
	if(l == r) return c[o] = a[l];
	return c[o] = build(lson) + build(rson);
}
void update(int o, int l, int r, int pos, int dt){
	if(l == r){
		c[o] += dt;
		return ;
	}
	if(pos <= t_mid) update(lson, pos, dt);
	if(pos > t_mid) update(rson, pos, dt);
	up(o);
}
int query(int o, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return c[o];
	int ret = 0;
	if(ql <= t_mid) ret += query(lson, ql, qr);
	if(qr > t_mid) ret += query(rson, ql, qr);
	return ret;
}
int main(){
	int T, x, y;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++){
		printf("Case %d:\n", cas);
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
		build(1, 1, n);
		while(~scanf("%s", str) && strcmp(str, "End")){
			scanf("%d%d", &x, &y);
			if(!strcmp(str, "Add")) update(1, 1, n, x, y);
			if(!strcmp(str, "Sub")) update(1, 1, n, x, -y);
			if(!strcmp(str, "Query")) printf("%d\n", query(1, 1, n, x, y));
		}
	}
}
///////////////////////////////////////////////////////////////////////
//树状数组
#include<cstdio>
#include<cstring>
typedef long long LL;
const int N = 50000 + 5;
LL sz[N];
char str[15];
int n;
LL Sum(int x){
	LL ret = 0;
	for(int i = x; i; i -= i&(-i)) ret += sz[i];
	return ret;
}
int main(){
	int T, t, x, y;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++){
		printf("Case %d:\n", cas);
		memset(sz, 0, sizeof(sz));
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
			scanf("%d", &t);
			for(int j = i; j <= n; j += j&(-j)) sz[j] += t;
		}
		while(~scanf("%s", str) && strcmp(str, "End")){
			scanf("%d%d", &x, &y);
			if(!strcmp(str, "Add")) for(int i = x; i <= n; i += i&(-i)) sz[i] += y;
			if(!strcmp(str, "Sub")) for(int i = x; i <= n; i += i&(-i)) sz[i] -= y;
			if(!strcmp(str, "Query")) printf("%I64d\n", Sum(y) - Sum(x-1));
		}
	}
} 
/////////////////////////////////////////////////////////////////////// 
//zkw线段树 
#include<cstdio>
#include<cstring>
const int N = 50000 + 5;
int n, D;
int a[N], c[N << 2];
char str[15];
void up(int o){
	c[o] = c[o << 1] + c[o << 1 | 1];
}
void build(){
	for(D = 1; D <= n+1; D <<= 1) ;  
    for(int i = D+1; i <= D+n; i ++) scanf("%d", &c[i]);  
    for(int i = D-1; i > 0; i --) up(i);
}
void update(int p, int dt){
	for(c[p+=D] += dt, p >>= 1; p; p >>= 1) up(p);
}
int query(int l, int r){
	int ret = 0;
    for(l = l+D-1, r = r+D+1; l^r^1; l >>= 1, r >>= 1){
        if(~l&1) ret += c[l^1];
        if(r&1)  ret += c[r^1];
    }
    return ret;
}
int main(){
	int T, x, y;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas ++){
		printf("Case %d:\n", cas);
		scanf("%d", &n);
		build();
		while(~scanf("%s", str) && strcmp(str, "End")){
			scanf("%d%d", &x, &y);
			if(!strcmp(str, "Add")) update(x, y);
			if(!strcmp(str, "Sub")) update(x, -y);
			if(!strcmp(str, "Query")) printf("%d\n", query(x, y));
		}
	}
}
