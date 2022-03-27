
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define PIx2 6.2832

void Gen_sig(double *x, int N)  // Generate signals 
{
    double t, freq1 = 10, freq2 = 5;

    for (int n=0 ; n<N ; n++)
    {
        t = (double)n * (1/(double)N);

        x[n] = 3*sin(freq1*PIx2*t) + 5*sin(freq2*PIx2*t);

    } 

}

void FFT(double *x, _Complex *X, int N)   // Fast Fourier Transform signal
{
    if (N==1) return;

    _Complex X_even[N/2], X_odd[N/2], W;
    double x_even[N/2], x_odd[N/2];

    // Separate even and odd indexs
    for(int i = 0, j = 0; i < N; i += 2)
    {
        x_even[j] = x[i];
        x_odd[j]  = x[i+1];
        ++j;
    }

    // Minimum case
    if (N==2) {

        X_even[0] = x_even[0];
        X_odd[0] = x_odd[0];
    }


    // Calculate FFT using formula 

    FFT(x_even, X_even, N/2);
    FFT(x_odd, X_odd, N/2);

    // printf("\n N: %d \n", N);


    // Pairing together
    for (int k=0 ; k<N/2 ; k++)
    {
        W = cexp(-I * PIx2 * k /N);
        X[k] = X_even[k] + W * X_odd[k];
        X[k + N/2] = X_even[k] - W * X_odd[k];

/*        printf("X_even[%d]: %f + %fi\n", k, creal(X_even[k]), cimag(X_even[k]));
        printf("X_odd[%d]: %f + %fi\n", k, creal(X_odd[k]), cimag(X_odd[k]));
        printf("X[%d]: %f + %fi\n", k, creal(X[k]), cimag(X[k]));
*/
    }


}
int main()
{
    int N = 32;   // Number of sample points ATTENTION!!! Nyquist Law

    clock_t start, end;
    double time_consume;

    double P[N]      // Amplitude of input signals
        , x[N];     // input signals
    _Complex X[N];  // FFT values


    //  Generate signals
    Gen_sig(x, N);

    // Perform FFT and measure run time
    start = clock();
    FFT(x, X, N);
    end = clock();

    time_consume = (double)(end - start)/CLOCKS_PER_SEC;
    printf("this function take %lf seconds", time_consume);


    // Nomarlize the amplitude
    int N_oneside = N/2;
    _Complex X_oneside[N/2];

    for (int i = 0; i < N_oneside; ++i)
    {
        X_oneside[i] = X[i]/N_oneside;
    }


    // Amplitude of X
    for(int i = 0; i<N; i++)    P[i] = cabs(X_oneside[i]);



    // write to txt file
    FILE *f = fopen("G:/IMPORTANTS!!!/CODE/FFT256/Data/FFT_Recursive.txt", "w");

    for (int i = 0; i < N; ++i) 
    {
        fprintf(f, "%f,", x[i]);   
    }
    fprintf(f, "\n");
    for (int k = 0; k < N_oneside ; k++) fprintf(f,"%f,", P[k]);

    fclose(f);
    
    getchar();
    return 0;
}
