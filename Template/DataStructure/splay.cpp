//HDU 1890	Robotic Sort
//splay模板
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <time.h>
using namespace std;
const int N = 100000 + 5;
const int INF = 0x3f3f3f3f;
typedef long long LL;
struct Node *nill;
struct Node {
    int sz;
    int val, num;
    int l, r;
    bool rev;
    Node *ch[2],*fa;
    void ini(int v = 0){ //初始化节点
    	ch[0] = ch[1] = fa = nill;
        val = v;
        rev = 0;
        sz = 1;
    }
    void up() { //更新节点
        if (this==nill) return ;
        sz = ch[0]->sz + ch[1]->sz + 1;
    }
    bool d() { //判断自己是父亲节点的左儿子还是右儿子
        return fa->ch[1]==this;
    }
    void setc(Node *o,int c) { //连节点
        ch[c] = o;
        o->fa = this;
        up();
    }
    void rot() { //平衡旋转
        int c = d(),cc = fa->d();
        Node *z = fa->fa;
        Node *tmp = fa;
        fa->setc(ch[c^1],c);
        setc(tmp,c^1);
        z->setc(this,cc);
    }
    void reverse() { //反转
        rev ^= 1;
        std::swap(ch[0],ch[1]);
    }
    void down() { //反转
        if (this==nill) return ;
        if (!rev) return ;
        rev = false;
        ch[0]->reverse();
        ch[1]->reverse();
    }
    void D() { //Down，递归调用down
        if (this==nill) return ;
        fa->D();
        down();
    }
    void splay(Node *aim = nill) { //把当前节点提到aim下方，如果aim==nill，即提到根节点
        D();
        while (fa!=aim) {
            if (fa->fa!=aim) {
                d()==fa->d() ? fa->rot() : rot();
            }
            rot();
        }
    }
    static Node *getK(Node *o, int K) { //找第K个数，o为根节点
        o->D();
        while (o != nill) {
                o->down();
                if (K==o->ch[0]->sz+1) return o;
                if (o->ch[0]->sz >= K) {
                        o = o->ch[0];
                } else {
                        K -= o->ch[0]->sz + 1;
                        o = o->ch[1];
                }
        }
        return nill;
	}
	static int getRank(Node *&root, Node *o) { //找当前这个数是rank几
        o->splay(nill);
        root = o;
        return o->ch[0]->sz+1;
	}
	static Node *getNode(Node *o, int val, int f) { //找节点，o为根节点
		//f =  0:<  1:<=  2:>  3:>=
		Node *ret = nill;
		int c;
		o->D();
		while (true) {
			if (o==nill) return ret;
			o->down();
			switch(f){
				case 0: if(o->val <  val) {ret = o;o = o->ch[1];} else {o = o->ch[0];} break;
				case 1: if(o->val <= val) {ret = o;o = o->ch[1];} else {o = o->ch[0];} break;
				case 2: if(o->val >  val) {ret = o;o = o->ch[0];} else {o = o->ch[1];} break;
				case 3: if(o->val >= val) {ret = o;o = o->ch[0];} else {o = o->ch[1];} break;
			}
		}
	}
}memo[N], *bat, *root, *pK[N];


int n;
int a[N];
LL b[N];
Node *p1, *p2;

void show(Node *o) {
        if (o==nill) return ;
        o->down();
        show(o->ch[0]);
        printf("%d ",o->val);
        show(o->ch[1]);
}
void show() {
        show(root); puts("");
}
void newNode(Node *&o,int val = 0) {
        o = bat ++;
        o->ini(val);
}
void init() {
        bat = memo;
        newNode(nill); nill->sz = 0;
        root = nill;
}
void ins(int val, int num){
    root = Node::getK(root, num);
    root->splay(nill);
    newNode(p2, val);
    pK[val] = p2;
    p2->setc(root->ch[1], 1);
    root->setc(p2, 1);
}
void solve(){
    for(int i = 1; i < n; i ++){
        int k = Node::getRank(root, pK[i]);
        printf("%d ", k-1);
        root = Node::getK(root, i);
        root->splay(nill);
        p1 = Node::getK(root, k+1);
        p1->splay(root);
        p1->ch[0]->reverse();
    }
}

int main() {
        while(~scanf("%d", &n) && n){
        	init();
        	newNode(root);
        	for(int i = 0; i < n; i ++){
	        	scanf("%I64d", &b[i]);
	        	b[i] = b[i]*N + i;
	        }
	        sort(b, b+n);
	        for(int i = 1; i <= n; i ++){
                a[b[i-1]%N] = i;
	        }
	        //for(int i = 0; i < n; i ++) printf("%d ", a[i]); printf("\n");
	        for(int i = 1; i <= n; i ++) ins(a[i-1], i);
	        ins(n+1, n+1);
	        //show();
	        solve();
	        printf("%d\n", n);
        }
        return 0;
}
