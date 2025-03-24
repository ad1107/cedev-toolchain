/*
	exp returns the exponential function of its
	floating-point argument.

	The coefficients are #1069 from Hart and Cheney. (22.35D)
*/

#include <errno.h>
#include <math.h>

#define	log2e	1.44269504088896
#define	sqrt2	1.41421356237310
#define	maxf	100 // was 10000

float _expf_c(float arg) {
  float fraction;
  float temp1, temp2, xsq;
  int ent;
  
  if (arg==0.0)
    return 1.0;
  if (arg<-maxf){
    return 0.0;
  }
  if (arg>maxf){
    errno = ERANGE;
    return HUGE_VALF;
  }
  // 1* 1 floor 2 -
  arg *= log2e;
  ent = floor( arg );
  fraction = arg - ent - 0.5;
#if 1 // 5 *, 4 +, 1 /
  fraction *= M_LN2;
  xsq = fraction * fraction;
  // pade(exp(x),x,6,4) relative error<6e-9
  // (-x^3-12*x^2-60*x-120)/(x^3-12*x^2+60*x-120)
  temp1=(xsq+60.0)*fraction;
  temp2=12.0*(xsq+10.0);
  return ldexp( sqrt2 * (temp2+temp1) / (temp2-temp1), ent );
#else // 8 * 7 + 1 /
/************************************************************************/
/*									*/
/*			Copyright (C) 2000-2008 Zilog, Inc.		*/
/*									*/
/************************************************************************/
#define	p0	0.20803843466947e7
#define	p1	0.30286971697440e5
#define	p2	0.60614853300611e2
#define	q0	0.60027203602388e7
#define	q1	0.32772515180829e6
#define	q2	0.17492876890931e4
  xsq = fraction * fraction;
  temp1 = ((p2 * xsq + p1) * xsq + p0) * fraction;
  temp2 = ((1.0 * xsq + q2) * xsq + q1) * xsq + q0;
  return ldexp( sqrt2 * (temp2+temp1) / (temp2-temp1), ent );
#endif 
}

double _exp_c(double) __attribute__((alias("_expf_c")));
