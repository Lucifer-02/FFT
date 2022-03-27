
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define N 256                   // ATTENTION!!! Number of sample points, Nyquist Law
#define logN log((int)N)+1      // logarit 2 of N                   
#define PIx2 6.2832             // 2 times Pi


void Gen_sig(double *x)  // Generate signals 
{
    double t, freq1 = 10, freq2 = 5;

    for (int n=0 ; n<N ; n++)
    {
        t = (double)n * (1/(double)N);

        x[n] = 3*sin(freq1*PIx2*t) + 5*sin(freq2*PIx2*t);

    } 

}

// reverse n early bit of index
int revBit(int nbit, int index)
{
    int i, j;
    for(i = 0, j = nbit - 1; i <= j; ++i, --j)
    {
        if( (index >> i & 1) != (index >> j & 1) )
        {
            index ^= 1<<i;
            index ^= 1<<j;
        }
    }
    return index;
}

void FFT(double *x, _Complex *X)   // Fast Fourier Transform signal
{
    
    _Complex X_next[N]  // this array is used to save transform value at each step
            , W[N]      // Coefs of odd part
            , temp;     // To swap index

    int i, j, k,  even_index, odd_index;;

    // At first level, X = x
    for(i = 0; i < N; i++){
        X[i] = x[i];
    }

    // Separate even and odd indexs until only remain 2 numbers
    for(i = 0; i < N; ++i)
    {
        j = revBit(logN, i);
        if(i < j) 
        {
            temp = X[j];
            X[j] = X[i];
            X[i] = temp;
        }
    }

    // Have total (ln(N) - 1) step according Butterfly graph, at step = 1, N = 2*step
    for (int step = 1 ; step < N; step<<=1)
    {
        _Complex w = 1 ,                                // Coef e^(-i*2pi*k/N) with first value is 1                                
                w_base = cexp(-I * PIx2 / (step*2));

        // coresponding each step we have different number of coef 
        for(k = 0; k < step; ++k)
        {
            W[k] = w;
            w   *= w_base;
        }

        even_index = 0;                 // start even index                 
        odd_index  = even_index + step; // start odd index

        while(even_index < N)
        {
            // Perform caculate based on Formula
            for (i=0 ; i < step ; ++i)
            {
                X_next[even_index + i]        = X[even_index + i] + W[i] * X[odd_index + i];
                X_next[even_index + i + step] = X[even_index + i] - W[i] * X[odd_index + i];

            } 
            even_index += 2*step;               // next even index
            odd_index   = even_index + step;    // next odd index
        }

        // Final copy values from X_next to X
        for(i = 0; i < N; ++i)
        {
            X[i] = X_next[i];
        }
    }



}
int main()
{

    clock_t start, end;
    double time_consume;

    double P[N]      // Amplitude of input signals
        , x[N];     // input signals
    _Complex X[N];  // FFT values


    //  Generate signals
    Gen_sig(x);

    // Perform FFT and measure run time
    start = clock();
    FFT(x, X);
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



    // write to .txt file
    FILE *f = fopen("G:/IMPORTANTS!!!/CODE/FFT256/Data/FFT_For.txt", "w");

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
