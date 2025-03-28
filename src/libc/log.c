/************************************************************************/
/*									*/
/*                      Copyright (C)1999-2008 by Zilog, Inc.               */
/*                                                                      */
/************************************************************************/
/*
	log returns the natural logarithm of its floating
	point argument.

	The coefficients are #2705 from Hart & Cheney. (19.38D)

	It calls frexp.
*/

#include <errno.h>
#include <math.h>

#define	log2	0.693147180559945e0
#define	ln10	2.30258509299404
#define	sqrto2	0.707106781186548e0
#define	p0	-0.240139179559211e2
#define	p1	0.309572928215377e2
#define	p2	-0.963769093368687e1
#define	p3	0.421087371217980e0
#define	q0	-0.120069589779605e2
#define	q1	0.194809660700890e2
#define	q2	-0.891110902798312e1

float _logf_c(float arg)
{
  double x,z, zsq, temp;
  int exp;
  
  if (arg <= 0.0) {
    errno = EDOM;
    return -HUGE_VALF;
  }
  x = frexpf(arg, & exp);
  if ( x < sqrto2 ){
    x *= 2;
    exp--;
  }
  // now x is in [sqrt(2)/2,sqrt(2)]
  // ln(x)=ln((1+z)/(1-z)) where z=(x-1)/(x+1) is such that |z|<=3-2*sqrt(2)
  // = z*sum( (z^2)^k*2/(2k+1),k=0..inf)
  // for float precision, k=4 is enough, relative precision 2e-9/(1-|z|^2)
  z = (x-1)/(x+1);
  zsq = z*z;
#if 1
  // seq(2./(2k+1),k,0,5)=[2.0,0.666666666667,0.4,0.285714285714,0.222222222222,0.181818181818]
  temp = (((0.222222222222*zsq+0.285714285714)*zsq+0.4)*zsq+0.666666666667)*zsq+2.0;
  temp = temp*z + exp*M_LN2;
  return temp;
#else  
  temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
  temp = temp/(((1.0*zsq + q2)*zsq + q1)*zsq + q0);
  temp = temp*z + exp*log2;
  return temp;
#endif
}

double _log_c(double) __attribute__((alias("_logf_c")));
