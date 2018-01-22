#include "hn4.h"

int integrateNW( double gNaF, double gNaS, double gCaS, double gK, double gL, double gSyn, double gMod, double  ENa, double  ECa, double  EK, double  EL, double  ESyn, double  EMod, double V2mNaF, double V2hNaF, double V2mNaS, double V2hNaS, double V2mCaS, double V2hCaS, double V2mK, double V2Syn, double khCaS, double  ThNaS, double  ThCaS, double  TSyn, double cell2m, double  tf, double tint, double  y[])
{
  
  double cc[30]={			 //constant parameters
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
    khCaS,ThNaS,ThCaS,TSyn,cell2m,tf,tint};

  //gsl stuff
 const gsl_odeiv_step_type * T = gsl_odeiv_step_rk8pd; //choose integrator
  gsl_odeiv_step * s = gsl_odeiv_step_alloc (T, 16);
  gsl_odeiv_control * c = gsl_odeiv_control_y_new (1e-9, 1e-9); //set tolerances
  //  gsl_odeiv_control * c = gsl_odeiv_control_y_new (m, m); //set tolerances
  gsl_odeiv_evolve * e = gsl_odeiv_evolve_alloc (16);

  // declare variables
  double t, t1, ti, iLn, h;
  int ii,nn,status,lnPts;

  h = 1e-8; // set initial stepsize
  t1 = tf; // set total integrate time for data

  // make system using gsl options and system parameters
  // this integrator does not use the Jacbion, so pass NULL in its place
  gsl_odeiv_system sys = {func, NULL, 16, &cc[0]};  
  
  t=0; // reset time for convenience
  // integrator takes very small steps, but i only care about what happens once per 0.001 seconds.
  while (t < tf)
    {
      // take one step
      status = gsl_odeiv_evolve_apply (e, c, s,&sys,&t, tf, &h,y);
      if (status !=GSL_SUCCESS)
	{
	  break;
	}
      if (h<1e-14)
	{
	  h=1e-14;
	}
    }
 
  // free memory
  gsl_odeiv_evolve_free (e);
  gsl_odeiv_control_free (c);
  gsl_odeiv_step_free (s);
  return 0;
}
