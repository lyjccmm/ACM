#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = (int)1e6 + 5;
char str[N];
int a[2*N + 1];
//s[]是原来字符串，len是字符串长度，ret[]是每个点为中心的回文长度(包括中间的#号) 
int Manacher(char s[], int len, int ret[]){
	char Ma[len << 1 | 1];
	char sep = '#';	
	for(int i = 0; i < len; i ++){
		Ma[i << 1] = sep;
		Ma[i << 1 | 1] = s[i];
	}
	Ma[len << 1] = sep;
	len = len << 1 | 1;
	int R = 0, id = 0, Max = 0;
	for(int i = 0; i < len; i ++){
		if(R > i) ret[i] = min(ret[2*id-i], R-i);
		else ret[i] = 1;
		while(i-ret[i] >= 0 && i+ret[i] < len && Ma[i-ret[i]] == Ma[i+ret[i]]) ret[i]++;
		if(i+ret[i] > R){
			R = i+ret[i];
			id = i;
		}
		Max = max(Max, ret[i]-1);
	}
	return Max;
}
int main(){
	int n, len;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%s", str);
		len = strlen(str);
		printf("%d\n", Manacher(str, len, a));
		/*for(int i = 0; i < len; i ++){
			printf("%d", a[i << 1 | 1] - 1);
			printf(i == len-1 ? "\n" : " ");
		}*/
	}
}
