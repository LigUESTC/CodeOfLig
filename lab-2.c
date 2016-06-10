//���ʵ��ο������������������࣬�ߵȽ������������ġ�����ϵͳԭ����Ƽ�Ӧ�á��Ȿ��Ƥ��ĵ�116ҳ����120ҳ
#include <stdio.h>
#include <string.h>

#define KINDS 31
#define NUM 31

unsigned char p;
unsigned char r;

unsigned char available[KINDS];
unsigned char lock;

struct PROCESS
{
unsigned char max[KINDS];
unsigned char allocation[KINDS];
unsigned char need[KINDS];
unsigned char scheduled;
}process[NUM];

struct SCHEDULE
{
unsigned char processNO;
unsigned char work[KINDS];
unsigned char need[KINDS];
unsigned char allocation[KINDS];
unsigned char workplusallo[KINDS];
unsigned char finish;
}schedule[NUM];

void inputresources(void)
{
	unsigned char i=0;
	unsigned char j=0;
	printf("���м��㷨����\nע�⣺���е��±궼�Ǵ�0��ʼ�ġ�\n���Ҫ��������������ô������֮������ÿո������\n");
	printf("�������������\n",i);
	scanf("%d",&p);
	printf("��������Դ����\n",i);
	scanf("%d",&r);
	for (i=0;i<p;i++)
	{
		printf("���������P%d��Ҫ�������Դ��max\n",i);
		for (j=0;j<r;j++)
			scanf("%d",&process[i].max[j]);
	}
	for (i=0;i<p;i++)
	{
		printf("���������P%d�ѷ������Դ��allocation\n",i);
		for (j=0;j<r;j++)
			scanf("%d",&process[i].allocation[j]);
	}
	printf("������ʣ�����Դ��available\n",i);
	for (j=0;j<r;j++)
		scanf("%d",&available[j]);
	for (i=0;i<p;i++)
	{
		process[i].scheduled=0;
		for (j=0;j<r;j++)
		process[i].need[j]=process[i].max[j]-process[i].allocation[j];
	}
}

unsigned char isavailable(unsigned char p[], unsigned char q[])
{
	unsigned char res=0;
	unsigned char s=0;
	unsigned char t=0;
	for (t=0;t<r;t++)
	{
		if (p[t]<=q[t])
			res++;
	}
	s=res/r;
	return s;
}

int main()
{
	unsigned char a;
	unsigned char b=0;
	unsigned char i;
	unsigned char j;
	unsigned char k;
	lock=0;
	inputresources();
	for (i=0;i<p;i++)
	{
		a=isavailable(process[i].need,available);
		b=b+a;
		if (a)
			break;
	}
	if (b==0)
	{
		printf("��������\n");
		lock=1;
		return 0;
	}
	else
	{
		process[i].scheduled=1;
		schedule[0].processNO=i;
		memcpy(schedule[0].work,available,r);
		memcpy(schedule[0].need,process[i].need,r);
		memcpy(schedule[0].allocation,process[i].allocation,r);
		for (j=0;j<r;j++)
			schedule[0].workplusallo[j]=schedule[0].work[j]+schedule[0].allocation[j];
		schedule[0].finish=1;
		memcpy(schedule[1].work,schedule[0].workplusallo,r);
	}
	for (k=1;k<p;k++)
	{
		a=0;
		b=0;
		for (i=0;i<p;i++)
		{
			if (!process[i].scheduled)
			{
			a=isavailable(process[i].need,schedule[k].work);
			b=b+a;
			if (a)
				break;
			}
			else ;
		}
		if (b==0)
		{
			printf("��������\n");
			lock=1;
			return 0;
		}
		else
		{
			process[i].scheduled=1;
			schedule[k].processNO=i;
			memcpy(schedule[k].need,process[i].need,r);
			memcpy(schedule[k].allocation,process[i].allocation,r);
			for (j=0;j<r;j++)
				schedule[k].workplusallo[j]=schedule[k].work[j]+schedule[k].allocation[j];
			schedule[k].finish=1;
			if (k<NUM-1)
			memcpy(schedule[k+1].work,schedule[k].workplusallo,r);
		}
	}
	if (!lock)
	{
		printf("����˳��Ϊ��\n");
		for (i=0;i<p;i++)
		{
			printf("%d",schedule[i].processNO);
			if (i<p-1)
				printf("��");
			else printf("\n");
		}
	}
	return 0;
}