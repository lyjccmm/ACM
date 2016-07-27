//http://hihocoder.com/problemset/problem/1195
//高斯消元模板 
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const double EPS = 1e-8;
typedef vector<double> Vec;
typedef vector<Vec> Mat;
//求解Ax=b，其中A是方阵
//当方程组无解或者有无穷多解时，返回一个长度为0的数组
//return 0无解，1有解，2有无穷多解 
int gauss(const Mat &A, const Vec &b, Vec &ret){
    int n = A.size(), m = A[0].size();
    Mat B(n, Vec(m + 1));
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++) B[i][j] = A[i][j];
        //把b存放在A的右边方便一起处理
        B[i][m] = b[i];
    }
    int row = 0;//正在处理第几行数
    for(int i = 0; i < m; i ++){//正在处理的列数
        if(row == n) return 2;
    	//把正在处理的未知数系数的绝对值最大的式子换到第i行
        int pivot = row;
        for(int j = row + 1; j < n; j ++){
            if(fabs(B[j][i]) > fabs(B[pivot][i])) pivot = j;
        }
        swap(B[row], B[pivot]);
        //有无穷多解
		if(fabs(B[row][i]) < EPS) continue;
		//把正在处理的未知数的系数变为1
        for(int j = i + 1; j < m + 1; j ++) B[row][j] /= B[row][i];
        B[row][i] = 1;
        for(int j = 0; j < n; j ++){
            if(j != row){
                //从第j个式子中消去第i个未知数
                for(int k = i + 1; k < m + 1; k ++) B[j][k] -= B[j][i] * B[row][k];
                B[j][i] = 0;
            }
        }
        row ++;
    }
    for(int i = row; i < n; i ++) if(fabs(B[i][m]) > EPS) return 0;
    if(row < m) return 2;
    ret = Vec(m);
    for(int i = 0; i < m; i ++) ret[i] = B[i][m];
    return 1;
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    Mat mat(m, Vec(n));
    Vec b(m);
    Vec ans;
    for(int i = 0; i < m; i ++){
        for(int j = 0; j < n; j ++){
            scanf("%lf", &mat[i][j]);
        }
        scanf("%lf", &b[i]);
    }
    int flag = gauss(mat, b, ans);
    switch(flag){
    	case 0:puts("No solutions");break;
    	case 1:for(int i = 0 ; i < ans.size(); i ++) printf("%.0f\n", ans[i] + EPS);break;
    	case 2:puts("Many solutions");break;
    }
}
