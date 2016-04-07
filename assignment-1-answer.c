#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>

main()
{
unsigned short buf[100];
gets(buf);
system(buf);
printf("进程已经被结束\n");
system("pause");

}