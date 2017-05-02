//FFT
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <complex>
using namespace std;
typedef __int64 LL;
typedef complex<double> Complex;
const double pi = acos(-1.0);
const int N = 10000+5;
const double eps = 1e-6;

void fft(Complex *a, int n, int rev) {
    // n是大于等于相乘的两个数组长度的2的幂次
    // 从0开始表示长度，对a进行操作
    // rev==1进行DFT，==-1进行IDFT
    for (int i = 1,j = 0; i < n; ++ i) {
        for (int k = n>>1; k > (j^=k); k >>= 1);
        if (i<j) std::swap(a[i],a[j]);
    }
    for (int m = 2; m <= n; m <<= 1) {
        Complex wm(cos(2*pi*rev/m),sin(2*pi*rev/m));
        for (int i = 0; i < n; i += m) {
            Complex w(1.0,0.0);
            for (int j = i; j < i+m/2; ++ j) {
                Complex t = w*a[j+m/2];
                a[j+m/2] = a[j] - t;
                a[j] = a[j] + t;
                w = w * wm;
            }
        }
    }
    if (rev==-1) {
        for (int i = 0; i < n; ++ i) real(a[i]) /= n,imag(a[i]) /= n;
    }
}
int main()
{
    Complex* a = new Complex[4];
    a[0] = Complex(0, 0);
    a[1] = Complex(1, 0);
    a[2] = Complex(2, 0);
    a[3] = Complex(3, 0);
    fft(a, 4, 1);
    cout<<"----------After DFT----------"<<endl;
    for(int i = 0; i < 4; i++)
        printf("%.9f + %.9fi\n", real(a[i]), imag(a[i]));
    cout<<"----------After DFT-1----------"<<endl;
    fft(a, 4, -1);
    for(int i = 0; i < 4; i++)
        printf("%.9f + %.9fi\n", real(a[i]), imag(a[i]));
    return 0;
}
