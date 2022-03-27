
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 32
#define PIx2 6.2832
 
int main()
{
    // time and frequency domain data arrays
    int n, k;             // indices for time and frequency domains
    float x[N], t;           // discrete-time signal, x
    float Xre[N], Xim[N]; // DFT of x (real and imaginary parts)
    float P[N];           // power spectrum of x
     
    // Generate random discrete-time signal x in range (-1,+1)
    for (n=0 ; n<N ; ++n)
    {
        t = (float)n * 0.03125;

        x[n] = 3*sin(11*PIx2*t);
    } 
     
    // Calculate DFT of x using brute force
    for (k=0 ; k<N ; ++k)
    {
        // Real part of X[k]
        Xre[k] = 0;
        for (n=0 ; n<N ; ++n) Xre[k] += x[n] * cos(n * k * PIx2 / N);
         
        // Imaginary part of X[k]
        Xim[k] = 0;
        for (n=0 ; n<N ; ++n) Xim[k] -= x[n] * sin(n * k * PIx2 / N);
         
        // Power at kth frequency bin
        P[k] = sqrt(Xre[k]*Xre[k] + Xim[k]*Xim[k]);
    }
    

    // Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("G:/IMPORTANTS!!!/CODE/FFT256/Data/dftplots.txt", "w");
    // fprintf(f, "n = [0:%d];\n", N-1);
    // fprintf(f, "x = [ ");
    // for (n=0 ; n<N ; ++n) fprintf(f, "%f ,", x[n]);
    // fprintf(f, "]\n");
    // fprintf(f, "P = [ ");
    for (k=0 ; k<N ; ++k) fprintf(f, "%d: %f \n", k, P[k]);
    // fprintf(f, "]\n");
    fclose(f);
     
    // exit normall
    return 0;
}