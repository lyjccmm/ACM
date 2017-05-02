//RMQ
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N = (int)1e5 + 5;
const int LOG_N = 30;
int d[N][LOG_N];
void RMQ_init(const vector <int>& A){
	int n = A.size();
	for(int i = 0; i < n; i ++) d[i][0] = A[i];
	for(int j = 1; (1 << j) <= n; j ++){
		for(int i = 0; i + (1 << j) - 1 < n; i ++){
			d[i][j] = min(d[i][j-1], d[i + (1 << (j-1))][j-1]);
		}
	}
}
int RMQ(int L, int R){
	int k = 0;
	while( (1 << (k+1)) <= R-L+1) k++;
	return min(d[L][k], d[R-(1<<k)+1][k]);
} 
