//http://acm.hdu.edu.cn/showproblem.php?pid=5536
//字典树 
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1000 + 5;
int n, ans, tot;
int a[N];
int ch[N * 31][2], cnt[N * 31];
int getnode(){
    ch[tot][0] = ch[tot][1] = 0;
    cnt[tot] = 0;
    return tot ++;
}
void insert(int x, int dt){
    int p = 0;
    for(int i = 30; i >= 0; i --){
        int c = x >> i & 1;
        if(ch[p][c] == 0){
            ch[p][c] = getnode();
        }
        p = ch[p][c];
        cnt[p] += dt;
    }
}
void update(int x){
    int p = 0, now = 0;
    for(int i = 30; i >= 0; i--){
        int c = x >> i & 1 ^ 1;
        if(cnt[ch[p][c]] == 0){
            c ^= 1;
        }
        else{
            now |= 1 << i;
        }
        p = ch[p][c];
    }
    ans = max(ans, now);
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        ans = 0;
        tot = 0;
        getnode();
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            insert(a[i], 1);
        }
        for(int i = 1; i < n; i++){
            insert(a[i], -1);
            for(int j = i + 1; j <= n; j++){
                insert(a[j], -1);
                update(a[i]+a[j]);
                insert(a[j], 1);
            }
            insert(a[i], 1);
        }
        printf("%d\n", ans);
    }
}
