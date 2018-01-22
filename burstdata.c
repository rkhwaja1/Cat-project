#include "hn4.h"
#include <stdio.h>

double ** burstdata(double tint, int lengthy, double y[])
{
  double spthresh = -0.01;
  double intbthresh = 0.04;  
  double bs[(int)lengthy/100][7];
  int sps[(int)lengthy/10];
  double maxy;
  int maxa;
  int a = 0;
  int lntbs = 0;
  int lntsps = 0;
  int b = 0;
  int tbsps;
  int c;

  /*  double t[lengthy];
  printf("G\n");
  for (c=0; c<lengthy; c++)
    {
      t[c] = c*tint;
    }*/

  while (y[a] > spthresh)
    {
      a = a+1;
    }
  while (a < lengthy)
    {
      while (y[a] < spthresh)
	{
	  a = a+1;
	}
	  maxy = -100;
      while (y[a] > spthresh)
	{
	  if (y[a] > maxy)
	    {
	      maxy = y[a];
	      maxa = a;
	    }
	  a = a+1;
	}
      sps[lntsps] = maxa;
      lntsps = lntsps + 1;
    }

  int here;
  int next;
  double sper;
  double sfreq;

  double minV = 200.0;
  for (a=0; a<sps[0]; a++)
    {
      if (y[a] < minV)
	{
	  minV = y[a];
	}
    }

  ///////////////////Change to include without waiting for one whole interburst interval                                                
  sfreq = 0;
  sper = 0;
  if (sps[0]*tint > intbthresh && minV < -53.0)
    {
      bs[lntbs][0] = sps[0]*tint;
      while (sper <= intbthresh)
        {
          here = sps[b];
          next = sps[b+1];
          sper = (next*tint)-(here*tint);
          sfreq = sfreq + 1.0/sper;
          b = b + 1;
        }
      lntbs = lntbs + 1;
      bs[lntbs][0] = next*tint; //time of max of first spike of burst                                                                                    
      if (lntbs > 0)
        {
          bs[lntbs-1][6] = sper; //interburst interval                                                                                                   
          bs[lntbs-1][5] = (here*tint) - bs[lntbs-1][0]; //burst duration                                                                                
          bs[lntbs-1][1] = (next*tint) - bs[lntbs-1][0]; //burst period                                                                                  
          bs[lntbs-1][2] = (double)(b - tbsps); //spikes per burst                                                                                     
          bs[lntbs-1][3] = sfreq/(bs[lntbs-1][2]-1); //spike frequency                                                                                   
          bs[lntbs-1][4] = bs[lntbs-1][5]/bs[lntbs-1][1]; //duty cycle                                                                                   
        }
      tbsps = b;
      lntbs = lntbs + 1;
    }
  /////////////////////////////////////////////////////////////////

  sfreq = 0;
  while (b < lntsps-1)
    {
      here = sps[b];
      next = sps[b+1];
      sper = (next*tint)-(here*tint);
      minV = 200.0;
      for (a=here; a<next; a++)
	{
	  if (y[a] < minV)
	    {
	      minV = y[a];
	    }
	}
      if (sper > intbthresh && minV < -53.0)
	{
	  //printf("minV %6.6g \n", minV);
	  bs[lntbs][0] = next*tint; //time of max of first spike of burst, starts after one whole interburst interval
	  if (lntbs > 0)
	    {
	      bs[lntbs-1][6] = sper; //interburst interval
	      bs[lntbs-1][5] = (here*tint) - bs[lntbs-1][0]; //burst duration
	      bs[lntbs-1][1] = (next*tint) - bs[lntbs-1][0]; //burst period
	      bs[lntbs-1][2] = b+1 - tbsps; //spikes per burst
	      bs[lntbs-1][3] = sfreq/(bs[lntbs-1][2]-1); //spike frequency
	      bs[lntbs-1][4] = bs[lntbs-1][5]/bs[lntbs-1][1]; //duty cycle
	    }
	  tbsps = b + 1;
	  lntbs = lntbs + 1;
	  sfreq = 0;
	}
      else 
	{
	  sfreq = sfreq + 1.0/sper;
	}
      b = b + 1;
    }

  numbs = lntbs-2;
  double ** BS;
  if (numbs > 1)
    {
      BS = malloc(numbs*sizeof(double*));   
      if (BS==NULL)
	{
	  fprintf(stderr, "Error: Out of memory\n");
	  exit(-1);
	}
      
      int g;
      for (g=0; g<numbs; g++)
	{
	  BS[g] = malloc(7*sizeof(double)); 
	  if (BS[g]==NULL)
	    {
	      fprintf(stderr, "Error: Out of memory\n");
	      exit(-1);
	    }
	}
      
      int d;
      for (d=0; d<numbs; d++)
	{
	  BS[d][0] = bs[d][0];
	  BS[d][1] = bs[d][1];
	  BS[d][2] = bs[d][2];
	  BS[d][3] = bs[d][3];
	  BS[d][4] = bs[d][4];
	  BS[d][5] = bs[d][5];
	  BS[d][6] = bs[d][6];
	}
    }
  else
    {
      BS = malloc(2*sizeof(double*));   
      if (BS==NULL)
	{
	  fprintf(stderr, "Error: Out of memory\n");
	  exit(-1);
	}
      
      int g;
      for (g=0; g<2; g++)
	{
	  BS[g] = malloc(7*sizeof(double)); 
	  if (BS[g]==NULL)
	    {
	      fprintf(stderr, "Error: Out of memory\n");
	      exit(-1);
	    }
	}
      
      for (g=0; g<7; g++)
	{
	  BS[0][g] = 0.0;
	  BS[1][g] = 0.0;
	}
    }

  return BS;
}
      
      
      
