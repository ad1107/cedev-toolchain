/************************************************************************/
/*									*/
/*                Copyright (C) 1999-2008 by Zilog, Inc.                */
/*									*/
/************************************************************************/
/*
	C program for floating point sin/cos.
	Calls modf.
	There are no error exits.
	Coefficients are #3370 from Hart & Cheney (18.80D).
*/
#include <math.h>
//#include <debug.h>
//#undef NDEBUG


#define twoopi	  0.636619772367581

#if 1
#define piotwo 1.57079632679
float taylor_sin(float d){
  // x*(1-x^2/3!+x^4/5!-x^6/7!+x^8/9!)
  // == x* (2.7557319224e-06*x^8-0.000198412698413*x^6+0.00833333333333*x^4-0.166666666667*x^2+1.0)
  float x2=d*d;
  return d*(1.0+x2*(-0.166666666667+x2*(0.00833333333333+x2*(-0.000198412698413+x2*2.7557319224e-06)))); // 6* 4+
}

float taylor_cos(float d){
  // 1-x^2/2+x^4/24-x^6/720+x^8/40320
  // =2.48015873016e-05*x^8-0.00138888888889*x^6+0.0416666666667*x^4-0.5*x^2+1.0
  float x2=d*d;
  return 1.0+x2*(-.5+x2*(0.0416666666667+x2*(-0.00138888888889+x2*2.48015873016e-05))); // 5* 4+
}

float sinus(float d, int quad){
  //dbg_printf("sinus %f %i\n",d,quad);
  int neg=0;
  if (d<0){
    d=-d;
    neg=1;
  }
  // sin(x)=+/-sin_or_cos(x-k*pi/2), k=round(x/(pi/2))
  int k = d*twoopi+.5;
  d -= k*piotwo; // d in [-pi/4,pi/4]
  k += quad;
  if (k&2)
    neg=!neg;
  if (k&1)
    d=taylor_cos(d);
  else
    d=taylor_sin(d);
  return neg?-d:d;
}
#else
#define p0	  0.135788409787738e8
#define p1	 -0.494290810090284e7
#define p2	  0.440103053537527e6
#define p3	 -0.138472724998245e5
#define p4	  0.145968840666577e3
#define q0	  0.864455865292253e7
#define q1	  0.408179225234330e6
#define q2	  0.946309610153821e4
#define q3	  0.132653490878614e3

float sinus(float arg, int quad)
{
	float e, f;
	int k;
	float ysq;
	float x,y;
	float temp1, temp2;

	x = arg;
	if(x<0) {
		x = -x;
		quad = quad + 2;
	}
	x = x*twoopi;	/*underflow?*/
	if(x>32764){
		y = modff(x,&e);
		e = e + quad;
		modff(0.25*e,&f);
		quad = e - 4*f;
	}else{
		k = x;
		y = x - k;
		quad = (quad + k) & 03;
	}
	if (quad & 01)
		y = 1-y;
	if(quad > 1)
		y = -y;

	ysq = y*y;
	temp1 = ((((p4*ysq+p3)*ysq+p2)*ysq+p1)*ysq+p0)*y;
	temp2 = ((((ysq+q3)*ysq+q2)*ysq+q1)*ysq+q0);
	return(temp1/temp2);
}
#endif

float _sinf_c(float arg) {
	return sinus(arg, 0);
}

double _sin_c(double) __attribute__((alias("_sinf_c")));
