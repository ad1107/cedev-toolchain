/************************************************************************/
/*									*/
/*			Copyright (C)1987-2008 by				*/
/*		            Zilog, Inc.           			*/
/*									*/
/*		        San Jose, California     			*/
/*									*/
/************************************************************************/
/*
	floating point tangent

	A series is used after range reduction.
	Coefficients are #4285 from Hart & Cheney. (19.74D)
*/

#include <errno.h>
#include <math.h>
#if 1
float _tanf_c(float arg){
  // dbg_printf("tan %f\n",arg);
#define invpi 	1.27323954473516   // 4/pi
#define pio4	0.785398163397448
  float temp, e, argsq;
  int i,sign;
  
  sign = 1;
  if (arg<0.){
    arg = -arg;
    sign = -1;
  }
  i = arg*invpi;
  arg -= i*pio4;
  i &= 3;
  if (i&1) // pi/4-arg=pi/2-(arg+pi/4) => tan(arg+pi/4)=1/tan(pi/4-arg)
    arg=pio4-arg;
  if (i/2)
    sign=-sign;
  // P:=pade(tan(x),x,10,6)
  // (x^5-105*x^3+945*x)/(15*x^4-420*x^2+945)
  argsq = arg*arg;
  temp = ((argsq-105)*argsq+945)*arg/((15*argsq-420)*argsq+945);
  if (i==1 || i==2) {
    if (temp==0.) {
      errno = ERANGE;
      if (sign>0)
        return HUGE_VALF;
      return -HUGE_VALF;
    }
    temp = 1./temp;
  }
  return sign==1?temp:-temp;
}

#else

#define invpi 	1.27323954473516
#define p0 	-0.130682026475483e+5
#define p1	0.105597090171495e+4
#define p2	-0.155068565348327e+2
#define p3	0.342255438724100e-1
#define p4	0.338663864267717e-4
#define q0	-0.166389523894712e+5
#define q1	0.476575136291648e+4
#define q2	-0.155503316403171e+3

float _tanf_c(float arg)
{
	float sign, temp, e, x, xsq;
	int flag, i;

	flag = 0;
	sign = 1.;
	if(arg < 0.){
		arg = -arg;
		sign = -1.;
	}
	arg = arg*invpi;   /*overflow?*/
        x = modff(arg, &e);
	i = e;
	switch(i%4) {
	case 1:
		x = 1. - x;
		flag = 1;
		break;

	case 2:
		sign = - sign;
		flag = 1;
		break;

	case 3:
		x = 1. - x;
		sign = - sign;
		break;

	case 0:
		break;
	}

	xsq = x*x;
	temp = ((((p4*xsq+p3)*xsq+p2)*xsq+p1)*xsq+p0)*x;
	temp = temp/(((1.0*xsq+q2)*xsq+q1)*xsq+q0);

	if(flag == 1) {
		if(temp == 0.) {
			errno = ERANGE;
			if (sign>0)
				return(HUGE_VALF);
			return(-HUGE_VALF);
		}
		temp = 1./temp;
	}
	return(sign*temp);
}
#endif

double _tan_c(double) __attribute__((alias("_tanf_c")));
