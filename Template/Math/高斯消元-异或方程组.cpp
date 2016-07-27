//http://hihocoder.com/problemset/problem/1196
//高斯消元, 异或方程组 
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> Vec;
typedef vector<Vec> Mat;
int dir[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};
char str[15];
int gauss(const Mat &A, const Vec &b, Vec &ret){
    int n = A.size(), m = A[0].size();
    Mat B(n, Vec(m + 1));
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++) B[i][j] = A[i][j];
        B[i][m] = b[i];
    }
    int row = 0;
    for(int i = 0; i < m; i ++){
        if(row == n) return 2;
        int pivot = row;
        for(int j = row + 1; j < n; j ++){
            if(B[j][i] > B[pivot][i]) pivot = j;
        }
        swap(B[row], B[pivot]);
		if(B[row][i] == 0) continue;
        for(int j = 0; j < n; j ++){
            if(j != row){
                for(int k = i + 1; k < m + 1; k ++) B[j][k] ^= (B[j][i] & B[row][k]);
                B[j][i] = 0;
            }
        }
        row ++;
    }
    for(int i = row; i < n; i ++) if(B[i][m] != 0) return 0;
    if(row < m) return 2;
    ret = Vec(m);
    for(int i = 0; i < m; i ++) ret[i] = B[i][m];
    return 1;
}
bool ok(int x, int y){
	if(x < 0 || x >= 5 || y < 0 || y >= 6) return false;
	return true;
}
int main(){
	int nx, ny;
    Mat mat(30, Vec(30, 0));
    Vec b(30);
    Vec ans;
    for(int i = 0; i < 5; i ++){
        scanf("%s", str);
        for(int j = 0; str[j]; j ++) b[i*6+j] = (str[j] - '0') ^ 1;
    }
    for(int i = 0; i < 5; i ++){
    	for(int j = 0; j < 6; j ++){
	    	for(int k = 0; k < 5; k ++){
	    		nx = i + dir[k][0];
	    		ny = j + dir[k][1];
	    		if(ok(nx, ny)){
		    		mat[i*6+j][nx*6+ny] = 1;
		    	}
	    	}
	    }
    }
    gauss(mat, b, ans);
    int cnt = 0;
    for(int i = 0; i < 30; i ++) if(ans[i]) cnt ++;
    printf("%d\n", cnt);
    for(int i = 0; i < 30; i ++) if(ans[i]) printf("%d %d\n", i / 6 + 1, i % 6 + 1);
}
