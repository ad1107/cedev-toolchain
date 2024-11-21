#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include <ti/screen.h>
#include <ti/getkey.h>

int main(void)
{

    os_ClrHome();

    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char *pEnd;

    long int li1, li2, li3, li4;
    li1 = strtol (szNumbers,&pEnd,10);
    li2 = strtol (pEnd,&pEnd,16);
    li3 = strtol (pEnd,&pEnd,2);
    li4 = strtol (pEnd,NULL,0);
    printf("%ld\r\n", li1);
    printf("%ld\r\n", li2);
    printf("%ld\r\n", li3);
    printf("%ld\r\n", li4);

    const char* str = "1234567890123";
    char* endptr = NULL;
    long ret = strtol(str, &endptr, 10);

    printf("ret = %ld\r\n", ret);
    printf("endptr = %p\r\n", endptr);
    printf("*endptr = %d\r\n", *endptr);
    printf("str = %p\r\n", str);
    printf("endptr-str = %ld\r\n", (unsigned long)endptr-(unsigned long)str);
    os_GetKey();
    return 0;
}