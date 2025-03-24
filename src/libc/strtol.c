#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

/*************************************************
*
* strtol - string to long conversion
*
* Inputs:
*    cp - pointer to the character string
*    endptr - place to put ptr to first invalid character
*    base - radix
*
* Returns:
*    the value of the number
*
*************************************************/
#if 1
 // https://stackoverflow.com/questions/7457163/what-is-the-implementation-of-strtol
long strtol(const char * nptr, char ** endptr, int base) {
  const char *p = nptr, *endp;
  int is_neg = 0, overflow = 0;
  /* Need unsigned so (-LONG_MIN) can fit in these: */
  unsigned long n = 0UL, cutoff;
  int cutlim;
  if (base < 0 || base == 1 || base > 36) {
#ifdef EINVAL /* errno value defined by POSIX */
    errno = EINVAL;
#endif
    return 0L;
  }
  endp = nptr;
  while (*p==' ')
    p++;
  if (*p == '+') {
    p++;
  } else if (*p == '-') {
    is_neg = 1, p++;
  }
  if (*p == '0') {
    p++;
    /* For strtol(" 0xZ", &endptr, 16), endptr should point to 'x';
     * pointing to ' ' or '0' is non-compliant.
     * (Many implementations do this wrong.) */
    endp = p;
    if (base == 16 && (*p == 'X' || *p == 'x')) {
      p++;
    } else if (base == 2 && (*p == 'B' || *p == 'b')) {
      /* C23 standard supports "0B" and "0b" prefixes. */
      p++;
    } else if (base == 0) {
      if (*p == 'X' || *p == 'x') {
        base = 16, p++;
      } else if (*p == 'B' || *p == 'b') {
        base = 2, p++;
      } else {
        base = 8;
      }
    }
  } else if (base == 0) {
    base = 10;
  }
  cutoff = (is_neg) ? -(LONG_MIN / base) : LONG_MAX / base;
  cutlim = (is_neg) ? -(LONG_MIN % base) : LONG_MAX % base;
  while (1) {
    int c;
    if (*p >= 'A')
      c = ((*p - 'A') & (~('a' ^ 'A'))) + 10;
    else if (*p <= '9')
      c = *p - '0';
    else
      break;
    if (c < 0 || c >= base) break;
    endp = ++p;
    if (overflow) {
      /* endptr should go forward and point to the non-digit character
       * (of the given base); required by ANSI standard. */
      if (endptr) continue;
      break;
    }
    if (n > cutoff || (n == cutoff && c > cutlim)) {
      overflow = 1; continue;
    }
    n = n * base + c;
  }
  if (endptr) *endptr = (char *)endp;
  if (overflow) {
    errno = ERANGE; return ((is_neg) ? LONG_MIN : LONG_MAX);
  }
  return (long)((is_neg) ? -n : n);
}

#else // Zilong bugged version
/************************************************************************/
/*                                    */
/*            Copyright (C)1987-2008 by                */
/*                    Zilog, Inc.                       */
/*                                    */
/*                San Jose, California                 */
/*                                    */
/************************************************************************/
long strtol(const char *__restrict nptr,
            char **__restrict endptr, int base)
{
  long sum,psum;
  char sign;
  int radix = base;
  char *cp = (char*)nptr;
  char digit;

  while (isspace(*cp))
    ++cp;

  sign = 0;
  if ( *cp == (char)'-' ) {
    sign = 1;
    ++cp;
  }
  else if ( *cp == (char)'+' )
    ++cp;

  if (base == 0)
  {
    radix = 10;
    if (*cp == (char)'0')
    {
      if (cp[1] == (char)'x' || cp[1] == (char)'X')
      {
        radix = 16;
      }
      else
      {
        radix = 8;
      }
    }
  }

  if (base == 16 && *cp == (char)'0' && (cp[1] == (char)'x' || cp[1] == (char)'X'))
    cp += 2;

  sum = 0;
  for (;;) {
    digit = toupper(*(cp++));
    if (digit >= (char)'A')
      digit = (digit - (char)'A') + (char)10;
    else
      digit -= (char)'0';
    if (digit < (char)0 || digit >= (char)radix)
      break;
    psum = sum;
    sum *= radix;
    sum    += digit;
    if (sum < psum) {    /* overflow */
      sum = sign ? LONG_MIN : LONG_MAX;
      errno=ERANGE;
      break;
    }
  }

  if (endptr) {
    --cp;
    if (base == 0) {
      while (*cp == (char)'h' || *cp == (char)'u' ||
         *cp == (char)'l' || *cp == (char)'L')
    ++cp;
    }
    *endptr = (char*)cp;
  }
  return(sign ? -sum : sum);
}
#endif
