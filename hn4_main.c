#include "hn4.h"
#include "time.h"

int main (void) {

  int run1, run2, run3, run4, run5, rr1, rr2, rr3, rr4, rr5;
  double gNaF, gNaS, gCaS, gK , gL, gSyn, gMod, ENa, ECa, EK; 
  double EL, ESyn, EMod, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS; 
  double V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, cell2m; 
  double tf1, tf2, tf3, tf4, tf5, tint;

  run1=2;  // this number gets written into the name of the data file
  run2=65;
  run3=0;
  run4=0;
  run5=0;
  
  gNaF = 50.0;	
  gNaS = 3.83;
  gCaS1 = 12.3;
  gK   = 40.0;	
  gL   = 2.96;	
  gSyn = 0.0;
  gCaS2 = 12.3;
  
  ENa  = 65.00;	
  ECa  = 160.0;	
  EK   = -70.0;	
  EL   = -54.0;	
  ESyn = -75.0;
  
  V2mNaF = 20.00;	
  V2hNaF = 23.00;		
  V2mNaS = 42.00;		
  V2hNaS = 55.00;
  V2mCaS = 45.59;        
  //V2hCaS = 58.93; 	
  V2mK   = 21.00;		
  V2syn  = 0.000;
  khCaS  = .75;		
  ThNaS = 0.100;		
  ThCaS = 0.485;		
  TSyn  = 0.009;
  
  
  gMod   = 1.00;
  EMod   = 65.000;
  cell2m = 1.000;// 1= on in both neurons. 0= on in one neuron
  
  tf1=1000.;
  tf2=30.;
  tf3=2.5;
  tf4=30.;
  tf5=30.;
  tint=0.00001;

  clock_t start;
  clock_t end;
  float seconds;
  
  double yy[16];
  double yy0[16];
 int numIP=0;

  FILE * f = fopen("ipW.txt", "r");
  double number = 0;
  int sum = 0; /* the sum of numbers in the file */
  
  while( fscanf(f, "%lf,", &number) > 0 ) // parse %d followed by ','
	{
	  yy0[numIP]= number; // instead of sum you could put your numbers in an array
	  numIP++;
	}  
  int ii;
  int a;
  int b;

  fclose(f);
  for (a=0; a<16; a++)
	    {
	      yy[a] = yy0[a];
	    }

  
  for (ii=0; ii<11; ii++)
    {
      V2hCaS = 59 - ( (double) ii * 3);
      run4 = 1 + ii;
      
	  
	  start = clock();
	  
	  rr1=integrateNW(gNaF, gNaS, gCaS, gK , gL, gSyn, 0.0, ENa, ECa, EK, EL, ESyn, 0.0, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS, V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, 0.0, tf1, tint, yy);
	  
	  rr2=integrate(run1, run2, run3, run4, 1, gNaF, gNaS, gCaS, gK , gL, gSyn, 0.0, ENa, ECa, EK, EL, ESyn, 0.0, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS, V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, cell2m, tf2, tint, yy);
	  
	 //rr3=integrate(run1, run2, run3, run4, 2, gNaF, gNaS, gCaS, gK , gL, gSyn, gMod, ENa, ECa, EK, EL, ESyn, EMod, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS, V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, 0.0, tf3, tint, yy);
	
	  //rr4=integrate(run1, run2, run3, run4, 2, gNaF, gNaS, gCaS, gK , gL, gSyn, 0.0, ENa, ECa, EK, EL, ESyn, 0.0, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS, V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, 0.0, tf4, tint, yy);

	 //rr5=integrate(run1, run2, run3, run4, 5, gNaF, gNaS, gCaS, gK , gL, gSyn, 0.0, ENa, ECa, EK, EL, ESyn, 0.0, V2mNaF, V2hNaF, V2mNaS, V2hNaS, V2mCaS, V2hCaS, V2mK, V2syn, khCaS, ThNaS, ThCaS, TSyn, 0.0, tf5, tint, yy);

	  end = clock();
	  seconds = (float)(end-start)/CLOCKS_PER_SEC;
	  
	  printf("running time: %6.6g\n", seconds);
	  
	
    }

  return(0);
}

