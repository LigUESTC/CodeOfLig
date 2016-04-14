#define FULL 10

#include <stdio.h>
#include <windows.h>

unsigned f(unsigned p,unsigned c)
{
unsigned res=0;
if (p<c)
res=0;
else if (p==c)
res=1;
else if ((p>c)&&(p<c+FULL))
res=2;
else if (p==c+FULL)
res=3;
else res=4;
return res;
}

unsigned f0(unsigned p,unsigned c)
{
unsigned i=0;
for (i=1;i<=p;i++)
printf("Producer %u: 0 -> 1\nConsumer %u: 1 -> 0\n",i,i);
for (i=p+1;i<=c;i++)
printf("Consumer %u: waiting\n",i);
return 0;
}

unsigned f1(unsigned p,unsigned c)
{
unsigned i=0;
for (i=1;i<=p;i++)
printf("Producer %u: 0 -> 1\nConsumer %u: 1 -> 0\n",i,i);
return 0;
}

unsigned f2(unsigned p,unsigned c)
{
unsigned i=0;
for (i=1;i<=c;i++)
printf("Producer %u: 0 -> 1\nConsumer %u: 1 -> 0\n",i,i);
for (i=c+1;i<=p;i++)
printf("Producer %u: %u -> %u\n",i,i-c-1,i-c);
return 0;
}

unsigned f3(unsigned p,unsigned c)
{
unsigned i=0;
for (i=1;i<=c;i++)
printf("Producer %u: 0 -> 1\nConsumer %u: 1 -> 0\n",i,i);
for (i=c+1;i<=c+FULL;i++)
printf("Producer %u: %u -> %u\n",i,i-c-1,i-c);
return 0;
}

unsigned f4(unsigned p,unsigned c)
{
unsigned i=0;
for (i=1;i<=c;i++)
printf("Producer %u: 0 -> 1\nConsumer %u: 1 -> 0\n",i,i);
for (i=c+1;i<=c+FULL;i++)
printf("Producer %u: %u -> %u\n",i,i-c-1,i-c);
for (i=c+1+FULL;i<=p;i++)
printf("Producer %u: waiting\n",i);
return 0;
}

int main()
{
unsigned p, c;
printf("请输入生产者数量p\n");
scanf("%u",&p);
printf("请输入消费者数量c\n");
scanf("%u",&c);
switch (f(p,c))
{
case 0:f0(p,c);break;
case 1:f1(p,c);break;
case 2:f2(p,c);break;
case 3:f3(p,c);break;
case 4:f4(p,c);break;
default:;
}
system("pause");
return 0;
}