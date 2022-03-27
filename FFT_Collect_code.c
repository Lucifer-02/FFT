#include <stdio.h>
#include <math.h>
#include <time.h>

#define N       128
#define PI      3.1415926535897
#define log2N   7



int RE[N]=
{
786,
816,
837,
849,
850,
838,
814,
780,
744,
700,
653,
601,
550,
501,
484,
451,
426,
409,
398,
394,
396,
404,
415,
431,
451,
477,
479,
512,
550,
593,
641,
687,
730,
772,
806,
832,
851,
852,
847,
830,
803,
764,
482,
470,
439,
420,
403,
395,
394,
397,
405,
418,
436,
458,
483,
486,
520,
561,
607,
651,
698,
742,
778,
811,
830,
846,
848,
836,
814,
782,
744,
701,
653,
603,
552,
503,
486,
453,
427,
409,
399,
394,
395,
401,
414,
429,
448,
472,
473,
506,
544,
586,
633,
678,
722,
763,
798,
825,
842,
849,
843,
826,
798,
762,
722,
676,
627,
576,
526,
480,
468,
437,
416,
404,
396,
394,
398,
407,
420,
438,
461,
488,
492,
527,
567,
612,
658,
706,
};
int IM[N];



// bang tra cuu Sin(a) cho FFT 128 diem
const signed char Sin_table[511] =
{
0,    // Temp_N = 2
0,-100,    // Temp_N = 4
0,-71,-100,-71,    // Temp_N = 8
0,-38,-71,-92,-100,-92,-71,-38,    // Temp_N = 16
0,-20,-38,-56,-71,-83,-92,-98,-100,-98,-92,-83,-71,-56,-38,-20,    // Temp_N = 32
0,-10,-20,-29,-38,-47,-56,-63,-71,-77,-83,-88,-92,-96,-98,-100,-100,-100,-98,-96,-92,-88,-83,-77,-71,-63,-56,-47,-38,-29,-20,-10,    // Temp_N = 64
0,-5,-10,-15,-20,-24,-29,-34,-38,-43,-47,-51,-56,-60,-63,-67,-71,-74,-77,-80,-83,-86,-88,-90,-92,-94,-96,-97,-98,-99,-100,-100,-100,-100,-100,-99,-98,-97,-96,-94,-92,-90,-88,-86,-83,-80,-77,-74,-71,-67,-63,-60,-56,-51,-47,-43,-38,-34,-29,-24,-20,-15,-10,-5,    // Temp_N = 128
};

// bang tra cuu Cos(a) cho FFT 128 diem
const signed char Cos_table[511] =
{
100,    // Temp_N = 2
100,0,    // Temp_N = 4
100,71,0,-71,    // Temp_N = 8
100,92,71,38,0,-38,-71,-92,    // Temp_N = 16
100,98,92,83,71,56,38,20,0,-20,-38,-56,-71,-83,-92,-98,    // Temp_N = 32
100,100,98,96,92,88,83,77,71,63,56,47,38,29,20,10,0,-10,-20,-29,-38,-47,-56,-63,-71,-77,-83,-88,-92,-96,-98,-100,    // Temp_N = 64
100,100,100,99,98,97,96,94,92,90,88,86,83,80,77,74,71,67,63,60,56,51,47,43,38,34,29,24,20,15,10,5,0,-5,-10,-15,-20,-24,-29,-34,-38,-43,-47,-51,-56,-60,-63,-67,-71,-74,-77,-80,-83,-86,-88,-90,-92,-94,-96,-97,-98,-99,-100,-100,    // Temp_N = 128
};
 



//Nghich dao cho FFF 128 diem
void nghich_dao() // du lieu adc doc duoc can phai dua qua ham nay de xu li (goi ham nay 1 lan duy nhat truoc khi tinh FFT)
{
   unsigned int i;
   i=RE[  1]; RE[  1]=RE[ 64]; RE[ 64]=i;
   i=RE[  2]; RE[  2]=RE[ 32]; RE[ 32]=i;
   i=RE[  3]; RE[  3]=RE[ 96]; RE[ 96]=i;
   i=RE[  4]; RE[  4]=RE[ 16]; RE[ 16]=i;
   i=RE[  5]; RE[  5]=RE[ 80]; RE[ 80]=i;
   i=RE[  6]; RE[  6]=RE[ 48]; RE[ 48]=i;
   i=RE[  7]; RE[  7]=RE[112]; RE[112]=i;
   i=RE[  9]; RE[  9]=RE[ 72]; RE[ 72]=i;
   i=RE[ 10]; RE[ 10]=RE[ 40]; RE[ 40]=i;
   i=RE[ 11]; RE[ 11]=RE[104]; RE[104]=i;
   i=RE[ 12]; RE[ 12]=RE[ 24]; RE[ 24]=i;
   i=RE[ 13]; RE[ 13]=RE[ 88]; RE[ 88]=i;
   i=RE[ 14]; RE[ 14]=RE[ 56]; RE[ 56]=i;
   i=RE[ 15]; RE[ 15]=RE[120]; RE[120]=i;
   i=RE[ 17]; RE[ 17]=RE[ 68]; RE[ 68]=i;
   i=RE[ 18]; RE[ 18]=RE[ 36]; RE[ 36]=i;
   i=RE[ 19]; RE[ 19]=RE[100]; RE[100]=i;
   i=RE[ 21]; RE[ 21]=RE[ 84]; RE[ 84]=i;
   i=RE[ 22]; RE[ 22]=RE[ 52]; RE[ 52]=i;
   i=RE[ 23]; RE[ 23]=RE[116]; RE[116]=i;
   i=RE[ 25]; RE[ 25]=RE[ 76]; RE[ 76]=i;
   i=RE[ 26]; RE[ 26]=RE[ 44]; RE[ 44]=i;
   i=RE[ 27]; RE[ 27]=RE[108]; RE[108]=i;
   i=RE[ 29]; RE[ 29]=RE[ 92]; RE[ 92]=i;
   i=RE[ 30]; RE[ 30]=RE[ 60]; RE[ 60]=i;
   i=RE[ 31]; RE[ 31]=RE[124]; RE[124]=i;
   i=RE[ 33]; RE[ 33]=RE[ 66]; RE[ 66]=i;
   i=RE[ 35]; RE[ 35]=RE[ 98]; RE[ 98]=i;
   i=RE[ 37]; RE[ 37]=RE[ 82]; RE[ 82]=i;
   i=RE[ 38]; RE[ 38]=RE[ 50]; RE[ 50]=i;
   i=RE[ 39]; RE[ 39]=RE[114]; RE[114]=i;
   i=RE[ 41]; RE[ 41]=RE[ 74]; RE[ 74]=i;
   i=RE[ 43]; RE[ 43]=RE[106]; RE[106]=i;
   i=RE[ 45]; RE[ 45]=RE[ 90]; RE[ 90]=i;
   i=RE[ 46]; RE[ 46]=RE[ 58]; RE[ 58]=i;
   i=RE[ 47]; RE[ 47]=RE[122]; RE[122]=i;
   i=RE[ 49]; RE[ 49]=RE[ 70]; RE[ 70]=i;
   i=RE[ 51]; RE[ 51]=RE[102]; RE[102]=i;
   i=RE[ 53]; RE[ 53]=RE[ 86]; RE[ 86]=i;
   i=RE[ 55]; RE[ 55]=RE[118]; RE[118]=i;
   i=RE[ 57]; RE[ 57]=RE[ 78]; RE[ 78]=i;
   i=RE[ 59]; RE[ 59]=RE[110]; RE[110]=i;
   i=RE[ 61]; RE[ 61]=RE[ 94]; RE[ 94]=i;
   i=RE[ 63]; RE[ 63]=RE[126]; RE[126]=i;
   i=RE[ 67]; RE[ 67]=RE[ 97]; RE[ 97]=i;
   i=RE[ 69]; RE[ 69]=RE[ 81]; RE[ 81]=i;
   i=RE[ 71]; RE[ 71]=RE[113]; RE[113]=i;
   i=RE[ 75]; RE[ 75]=RE[105]; RE[105]=i;
   i=RE[ 77]; RE[ 77]=RE[ 89]; RE[ 89]=i;
   i=RE[ 79]; RE[ 79]=RE[121]; RE[121]=i;
   i=RE[ 83]; RE[ 83]=RE[101]; RE[101]=i;
   i=RE[ 87]; RE[ 87]=RE[117]; RE[117]=i;
   i=RE[ 91]; RE[ 91]=RE[109]; RE[109]=i;
   i=RE[ 95]; RE[ 95]=RE[125]; RE[125]=i;
   i=RE[103]; RE[103]=RE[115]; RE[115]=i;
   i=RE[111]; RE[111]=RE[123]; RE[123]=i;
}

void FFT() //ham tinh FFT
{
    int thuc_W, ao_W ;
    int temp_N=2,index=1,dem=0;
	int thuc_Ek,ao_Ek,KQ_thuc,KQ_ao;
    for(int buoc=0;buoc<log2N;buoc++)
    {
		for(int k=0;k<index;k++)
        {
		   thuc_W = Cos_table[dem];
		   ao_W =   Sin_table[dem];
	       for(int i=k;i<N;i+=temp_N)  
					{
						thuc_Ek = RE[i]; 
						ao_Ek = IM[i]; 		  
						
					    KQ_thuc = (thuc_W * RE[i+index] - ao_W * IM[i+index])/100;
						KQ_ao = (thuc_W * IM[i+index]  + RE[i+index] * ao_W)/100;
						
						RE[i]   =  thuc_Ek + KQ_thuc;
						RE[i+index] =  thuc_Ek - KQ_thuc;
						 
						IM[i]   = ao_Ek + KQ_ao;
						IM[i+index] = ao_Ek - KQ_ao;
					}
			    dem++;
		     }		
		  index   <<=1;
		  temp_N  <<=1;		
    }
}

int main()
{
   clock_t start, end;
   double time_consume;

	nghich_dao();
   start = (double)clock();
	FFT();
   end = (double)clock();

   time_consume = (end - start)/(double)CLOCKS_PER_SEC;
   printf("this function take %lf seconds", time_consume);


	// printf("Ket qua tinh toan FFT:\n");
	// for(int x = 0; x < N; x++)
	// printf("%i + %ii\n,",  RE[x],IM[x]);
	
	// printf("\n");
	//              int y_y=0;
	// 			 for (int i=1;i<128;i++) 
	// 				{
	// 					RE[y_y] = sqrt(RE[i] * RE[i] + IM[i] * IM[i]);  // tinh Ak
	// 					y_y++;
	// 					printf("%i",RE[y_y]);
	// 			    }				

   getchar();

	return 0;
}