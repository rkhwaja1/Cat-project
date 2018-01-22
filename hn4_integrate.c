#include "hn4.h"

int integrate( int run1, int run2, int run3, int run4, int run5, double gNaF, double gNaS, double gCaS, double gK, double gL, double gSyn, double gMod, double ENa, double ECa, double EK, double EL, double ESyn, double EMod, double V2mNaF, double V2hNaF, double V2mNaS, double V2hNaS, double V2mCaS, double V2hCaS, double V2mK, double V2Syn, double khCaS, double ThNaS, double ThCaS, double TSyn, double  cell2m, double  tf, double  tint, double  y[])
{
  // make data file name with number modelID
  //printf("a");
  double cc[29]={			 //constant parameters
    /*
     * c[0]  = gNaF
     * c[1]  = gNaS
     * c[2]  = gCaS1
     * c[3]  = gK
     * c[4]  = gL
     * c[5]  = gSyn
     * c[6]  = gMod
     * c[7]  = ENa
     * c[8]  = ECa
     * c[9]  = EK
     * c[10] = EL
     * c[11] = ESyn
     * c[12] = EMod

     * c[13]  = V2mNaF
     * c[14]  = V2hNaF
     * c[15]  = V2mNaS
     * c[16]  = V2hNaS
     * c[17]  = V2mCaS
     * c[18]  = V2hCaS
     * c[19]  = V2mK
     * c[20]  = V2Syn
     * c[21]  = khCaS
     * c[22]  = ThNaS
     * c[23]  = ThCaS
     * c[24]  = TSyn
     * c[25]  = cell2m
    
     */
    gNaF,gNaS,gCaS,gK,gL,gSyn,gMod,
    ENa,ECa,EK,EL,ESyn,EMod,
    V2mNaF,V2hNaF,V2mNaS,V2hNaS,
    V2mCaS,V2hCaS,V2mK,V2Syn,
    khCaS,ThNaS,ThCaS,TSyn,cell2m,tf,tint
  };

  char file_name_string[100];
  sprintf(file_name_string,"./code2/%i_%i_%i/V%i_%i_%i_%i_%i.dat",run1,run2,run3,run1,run2,run3,run4,run5);
  //sprintf(file_name_string,"./V%i_%i_%i_%i_%i.dat",run1,run2,run3,run4,run5);
  
  // printf("b");
  //gsl stuff
  const gsl_odeiv_step_type * T = gsl_odeiv_step_rk8pd; //choose integrator
  gsl_odeiv_step * s = gsl_odeiv_step_alloc (T, 16);
  gsl_odeiv_control * c = gsl_odeiv_control_y_new (1e-9, 1e-9); //set tolerances
  //  gsl_odeiv_control * c = gsl_odeiv_control_y_new (m, m); //set tolerances
  gsl_odeiv_evolve * e = gsl_odeiv_evolve_alloc (16);

  // printf("c\n");
  // declare variables
  double t, t1, ti, iLn, h;
  int ii,nn,status,lnPts;

  h = 1e-8; // set initial stepsize
  t1 = tf; // set total integrate time for data
  iLn=t1*(1.0/tint); // how many millisecond sized steps do i take?
  double iLn2;
  iLn2 = 0.1*iLn;
  int ln2 = (int)iLn2;

  if (ln2 < iLn2)
    {
      ln2 = ln2+1;
    }


  //printf("run3 %i, run4 %i", run3, run4);
  // allocate data matrix
  
  gsl_matrix * Vs = gsl_matrix_alloc ( ln2+1 , 2 );
  //printf("d");

  // make system using gsl options and system parameters
  // this integrator does not use the Jacbion, so pass NULL in its place
  //printf("e");
  gsl_odeiv_system sys = {func, NULL, 16, &cc[0]};  

  //printf("f");
  double V1[ln2+1];  
  double V2[ln2+1];
  //double ts[ln2+1];
  /*  double * V1;
  double * V2;
  double * ts;
  V1 = malloc((ln2+1)*sizeof(double));
  if (V1==NULL)
    {
      fprintf(stderr, "Error: Out of memory\n");
      exit(-1);
    }
  V2 = malloc((ln2+1)*sizeof(double));
  if (V2==NULL)
    {
      fprintf(stderr, "Error: Out of memory\n");
      exit(-1);
    }
  ts = malloc((ln2+1)*sizeof(double));
  if (ts==NULL)
    {
      fprintf(stderr, "Error: Out of memory\n");
      exit(-1);
      }*/

  int tstep = 0;
  int J = 0;
  t=0; // reset time for convenience
  // integrator takes very small steps, but i only care about what happens once per 0.001 seconds.
  for (ii = 0; ii <= iLn;ii++)
    {
      lnPts=ii; 
      ti = ii * t1 / iLn;
      //ts[ii+1] = ti;

      // use however many steps to move the next 0.001 seconds
      while (t < ti)
	{
	  // take one step
	  status = gsl_odeiv_evolve_apply (e, c, s,&sys,&t, ti, &h,y);
	  if (status !=GSL_SUCCESS)
	    {
	    break;
	    }
	  if (h<1e-14)
	    {
	    h=1e-14;
	    }
	}
      if (ii == tstep)
	{
	  //printf("%6.6g ", t);
	  //ts[J] = t;
	  V1[J] = y[0];
	  V2[J] = y[7];
	  gsl_matrix_set(Vs,J,0,y[0]);
	  gsl_matrix_set(Vs,J,1,y[7]);
	  tstep = tstep + 10;
	  J = J + 1;
	}
    }

  double ** bs1 = burstdata(tint*10, ln2+1, V1);
  int lnbs1 = numbs;
  double ** bs2 = burstdata(tint*10, ln2+1, V2);
  int lnbs2 = numbs;

  // write data to file
  FILE * f1 = fopen(file_name_string,"wb");
  gsl_matrix_fwrite (f1,Vs);
  fclose (f1);
2020
  // free memory
  gsl_odeiv_evolve_free (e);
  gsl_odeiv_control_free (c);
  gsl_odeiv_step_free (s);
  gsl_matrix_free (Vs);

  /*  free(ts);
  free(V2);
  free(V1);*/

  //printf("\n lnt bs1: %i, lnt bs2: %i \n", lnbs1, lnbs2);
  int jj;
  for (nn=0;nn<6;nn++)
    {
      Avs[nn] = 0.0;
      Stds[nn] = 0.0;
    }

  if ((lnbs1 > 10) && (lnbs2 > 10))
    {
      char f_2[100];
      sprintf(f_2,"./code2/%i_%i_%i/bursts1J%i_%i_%i_%i_%i.txt",run1,run2,run3,run1,run2,run3,run4,run5);
      //sprintf(f_2,"./bursts1J%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5);
      FILE * f2 = fopen(f_2,"w");
      for (nn=0;nn<lnbs1;nn++)
	{
	  fprintf(f2,"%9.9g %9.9g %9.9g %9.9g %9.9g %9.9g %9.9g\n", bs1[nn][0], bs1[nn][1], bs1[nn][2], bs1[nn][3], bs1[nn][4], bs1[nn][5], bs1[nn][6]);
	  //printf("%9.9g %9.9g %9.9g %9.9g %9.9g %9.9g %9.9g\n", bs1[nn][0], bs1[nn][1], bs1[nn][2], bs1[nn][3], bs1[nn][4], bs1[nn][5], bs1[nn][6]);
	  if (nn >= lnbs1-10)
	    {
	      for (jj=0;jj<6;jj++)
		{
		  Avs[jj] = Avs[jj] + bs1[nn][jj+1];
		}
	    }
	}
      fclose(f2);
      
      char f_3[100];
      sprintf(f_3,"./code2/%i_%i_%i/bursts2J%i_%i_%i_%i_%i.txt",run1,run2,run3,run1,run2,run3,run4,run5);
      //sprintf(f_3,"./bursts2J%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5);
      FILE * f3 = fopen(f_3,"w");
      for (nn=0;nn<lnbs2;nn++)
	{
	  fprintf(f3,"%9.9g %9.9g %9.9g %9.9g %9.9g %9.9g %9.9g\n", bs2[nn][0], bs2[nn][1], bs2[nn][2], bs2[nn][3], bs2[nn][4], bs2[nn][5], bs2[nn][6]);
	  if (nn >= lnbs2-10)
	    {20
	      for (jj=0;jj<6;jj++)
		{
		  Avs[jj] = Avs[jj] + bs2[nn][jj+1];
		}
	    }
	}
      fclose(f3);
      
      for (jj=0;jj<6;jj++)
	{
	  Avs[jj] = Avs[jj]/20.0;
	}
      
      double trm;
      for (jj=0;jj<6;jj++)
	{
	  Stds[jj] = 0.0;
	  for (nn=lnbs1-10;nn<lnbs1;nn++)
	    {
	      trm = (bs1[nn][jj+1]-Avs[jj])*(bs1[nn][jj+1]-Avs[jj]);
	      Stds[jj] = Stds[jj] + trm; 
	    }
	  for (nn=lnbs2-10;nn<lnbs2;nn++)
	    {
	      trm = (bs2[nn][jj+1]-Avs[jj])*(bs2[nn][jj+1]-Avs[jj]);
	      Stds[jj] = Stds[jj] + trm; 
	    }
	  Stds[jj] = Stds[jj]/20.0;
	  Stds[jj] = sqrt(Stds[jj]);
	}
    }

  char f_ipr[100];
  sprintf(f_ipr,"./code2/%i_%i_%i/ip%i_%i_%i_%i_%i.txt",run1,run2,run3,run1,run2,run3,run4,run5);
  //sprintf(f_ipr,"./ip%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5);
  FILE * f_ip2 = fopen(f_ipr,"w");
  for (nn=0;nn<16;nn++)
  {
    fprintf(f_ip2,"%14.14g\n", y[nn]);
  }
  fclose(f_ip2);
    
  for(nn=0;nn<lnbs1;nn++)
    {
      free(bs1[nn]);
    }
  free(bs1);
  for(nn=0;nn<lnbs2;nn++)
    {
      free(bs2[nn]);
    }
  free(bs2);

  //  printf("\n");
  
  return 0;
}
