#include <stdio.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int main (void);
int integrate( int run1, int run2, int run3, int run4, int run5, double gNaF, double gNaS, double gCaS, double gK, double gL, double gSyn, double gMod, double ENa, double ECa, double EK, double EL, double ESyn, double EMod, double V2mNaF, double V2hNaF, double V2mNaS, double V2hNaS, double V2mCaS, double V2hCaS, double V2mK, double V2Syn, double khCaS, double ThNaS, double ThCaS, double TSyn, double  cell2m, double tf, double tint, double y[]);
int integrateNW( double gNaF, double gNaS, double gCaS, double gK, double gL, double gSyn, double  gMod, double  ENa, double  ECa, double  EK, double  EL, double  ESyn, double  EMod, double V2mNaF, double V2hNaF, double V2mNaS, double V2hNaS, double V2mCaS, double V2hCaS, double V2mK, double V2Syn, double khCaS, double  ThNaS, double  ThCaS, double  TSyn, double cell2m, double  tf, double tint, double  y[]);
int func(double t, const double y[], double f[], void * params);
double ** burstdata(double tint, int lengthy, double y[]);

int numbs;
double Avs[6];
double Stds[6];
int lastrun4;
double TmCaS;
double gCaS1;
double gCaS2;

