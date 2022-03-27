#include <stdio.h>
#include <time.h>
#include <math.h>

int countdown(int n){

	if(n==1) return 1;

	return n*countdown(n-1);
}
int countdown_for(int n)
{
	int i, r = 1;
	for(i = 1; i <= n; i++)
	{
		// printf("%d \n", r);
		r *= i;
	}
	return r;
}
void compute_arr_recusive(float *arr_in, float *arr_out, int N){

	if(N == 1) return;
	float X_even[N/2], X_odd[N/2], x_even[N/2], x_odd[N/2];

	// Separate even and odd
	for (int i = 0, j =0; i < N; i+=2)
	{
		x_even[j] = arr_in[i];
		x_odd[j] = arr_in[i+1];
		++j;
	}
	if(N==2)
	{
		X_even[0] = x_even[0];
		X_odd[0] = x_odd[0];
	}

	compute_arr_recusive(x_even, X_even, N/2);
	compute_arr_recusive(x_odd, X_odd, N/2);

	for (int i = 0; i < N/2; ++i)
	{
		arr_out[i] =  pow(2, arr_in[i]*i/N);
	}



}
void compute_arr_for(float *arr_in, float *arr_out, int N)
{
	int i, j;
	for(i = 0; i < N; i++)
	{
		arr_out[i] = 0;
		for(j = 0; j<N; j++)
		{
			arr_out[i] = 0;
			arr_out[i] += arr_in[j] * pow(2,arr_in[j]*i/N); 
		}
	}
}
void Create_arr(float *arr, int N, float step)
{
	int i;
	for(i = 0; i < N; i++)
	{
		arr[i] = i * step;
	}
}
void Display_arr(float *arr, int N)
{
	int i;
	for(i = 0; i < N; i++)
	{
		printf("%f \n", arr[i]);
	}

}
void Write2File(float *arr, int N)
{	
	int i;

	FILE *f = fopen("Recursive_Test_Data.txt", "w");
	for(i = 0; i < N; i++)
	{
		fprintf(f, "%d: %f\n", i, arr[i]);

	}
	fclose(f);

}
void sort_even_odd(float *arr, int N)
{
	float arr_even[N/2],arr_odd[N/2];

	if (N==1) return;

	for(int i = 0, j = 0; i<N; i+=2)
	{
		arr_even[j] = arr[i];
		arr_odd[j] = arr[i+1];
		j++;
	}

	if(N==2)
	{
		arr[0] = arr_even[0];
		arr[1] = arr_odd[1];
	}

	sort_even_odd(arr_even, N/2);
	sort_even_odd(arr_odd, N/2);

	for(int i = 0; i < N/2; i++){

		arr[i] = arr_even[i];
		arr[i + N/2] = arr_odd[i];
	}

	// Display_arr(arr_even, N/2);
}
int main(){

	int N = 4096;
	float arr_in[N], arr_out[N];

	Create_arr(arr_in, N, 1);




	clock_t start, end;

	start = (double)clock();
	// Start program here


	sort_even_odd(arr_in, N);


	// End program
	end = (double)clock();

	Display_arr(arr_in, N);

	printf("function take: %lf seconds", (double)(end - start)/(double)CLOCKS_PER_SEC );	


	getchar();

}