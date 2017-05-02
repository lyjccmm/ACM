#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 6e5 + 5;

struct SAM{
	static const int kN = N << 1;
	static const int chN = 26;
	int fa[kN], go[kN][chN], l[kN], tot, root, last;

	int newNode(int _l){
		memset(go[tot], -1, sizeof(go[tot]));
		fa[tot] = -1;
		l[tot] = _l;
		return tot ++;
	}
	void init(){
		tot = 0;
		root = last = newNode(0);
	}
	void build(char *s, char ch){
		for(int i = 0; s[i]; ++ i) add(s[i] - ch);
		topo();
		match_init();
	}
	void addKey(){
		int p = last, np = newNode(l[p]+1);
		while(~p) p = fa[p];
		fa[np] = root;
		last = np;
	}
	void add(int c){
		int p = last, np = newNode(l[p]+1);
		while (~p && go[p][c] == -1) go[p][c] = np, p = fa[p];
		if (p == -1) fa[np] = root;
		else {
			int q = go[p][c];
			if (l[p]+1 == l[q]) fa[np] = q;
			else {
				int nq = newNode(l[p]+1);
				memcpy(go[nq],go[q],sizeof(go[q]));
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				while (~p && go[p][c] == q) go[p][c] = nq, p = fa[p];
			}
		}
		last = np;
	}

	//topo
	
	int ord[kN], cnt[kN];
	void topo(){ // 求出parent树的拓扑序  
		int maxVal=0;  
		memset(cnt, 0, sizeof(cnt));  
		for (int i = 0; i < tot; ++ i) maxVal = max(maxVal, l[i]), ++ cnt[l[i]];  
		for (int i = 1; i <= maxVal; ++ i) cnt[i] += cnt[i-1];
		for (int i = 0; i < tot; ++ i) ord[-- cnt[l[i]]] = i;
	}  
	
	//multi-match
	
	int mx[kN], tmp[kN];
	void match_init(){
		for(int i = 0; i < tot; ++ i) mx[i] = l[i], tmp[i] = 0;
	}
	void parent_update(){
		for(int i = tot-1; i >= 1; -- i){
			tmp[fa[ord[i]]] = max(tmp[ord[i]], tmp[fa[ord[i]]]);
		}
	}
	void match_update(){
		for(int i = 0; i < tot; ++ i){
			mx[i] = min(mx[i], tmp[i]);
			tmp[i] = 0;
		}
	}
	void match(char *s, char ch = 0){
		int p = root, _val = 0;
		for(int i = 0, c; s[i]; ++ i){
			c = s[i] - ch;
			while(p != root && go[p][c] == -1){
				p = fa[p];
				_val = l[p];
			}
			if(go[p][c] != -1){
				p = go[p][c];
				++ _val;
				tmp[p] = max(_val, tmp[p]);
			}
		}
		parent_update();
		match_update();
	}
	int getMaxMatchLen(){
		int ret = 0;
		for(int i = 0; i < tot; ++ i) ret = max(ret, mx[i]);
		return ret;
	}
	
}sam;

