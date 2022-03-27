
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>

#define N 4096
#define PIx2 6.2832

void Gen_sig(float *x)  // Generate signals 
{
    int n;
    float t;

    for (n=0 ; n<N ; n++)
    {
        t = (float)n * (1/(float)N);

        x[n] = 3*sin(11*PIx2*t);
    } 

}

void DFT(float *x, _Complex *X)   // Fast Fourier Transform signal
{
    int n, k;             // indices for time and frequency domains

    // Calculate FFT using formula 
    for (k=0 ; k<N ; k++)
    {
        X[k] = 0;

        for (n=0 ; n<N ; n++)
        {
             X[k] += x[n] * cexp(-I * n * k * PIx2 / N);
        } 

    }

}
int main()
{
    clock_t start, end;
    double time_consume;
    int i;
    float P[N]      // Amplitude of input signals
        , x[N];      // input signals
    _Complex X[N];
    int k;

    //  Perform
    Gen_sig(x);
    start = clock();
    DFT(x, X);
    end = clock();
    time_consume = (double)(end - start)/CLOCKS_PER_SEC;
    printf("this function take %lf seconds", time_consume);
    // Amplitude of X
    for(i = 0; i<N; i++)    P[i] = cabs(X[i]);
    

    


    // write to txt file
    FILE *f = fopen("G:/IMPORTANTS!!!/CODE/FFT256/Data/DFT_Complex.txt", "w");
    // fprintf(f, "n = [0:%d];\n", N-1);
    // fprintf(f, "x = [ ");
    // for (n=0 ; n<N ; ++n) fprintf(f, "%f ,", x[n]);
    // fprintf(f, "]\n");
    // fprintf(f, "P = [ \n");
    for (k=0 ; k<N ; k++) fprintf(f, "%d: %f \n", k, P[k]);
    // fprintf(f, "]\n");
    fclose(f);

    getchar();
    return 0;
}
