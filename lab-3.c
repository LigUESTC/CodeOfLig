#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

//__64
//unsigned short pagetable[256]\[256]\[256]\[256]\[1024];
//ҳ��¼��С(8�ֽ�) ҳ��С �߼���ַ
//ҳ��С/ҳ��¼��С=ÿҳ��¼��
//ҳ����=(64-log2ҳ��С)/log2ÿҳ��¼��������������+1��
//������е�������

struct LCG
{
unsigned multiple;//����
unsigned addition;//����
}lcg[32];

struct LOG
{
	unsigned char bit;
	unsigned __int64 pwr;
}recsize,pagesize;

struct KILO
{
	unsigned char n;
	unsigned short b;//�����ȡ512
	char prefix;
}simp;

struct PAGETABLE
{
	char mod;//��߼�ҳ��
	char lth;//�м伶ҳ��
	char grd;//�м伶ҳ����
	char ini;//ҳ�ڵ�ַ����
}pagetbl;

char hex[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�߼���ַ�����֣�
char num[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�߼���ַ�����֣�
char num_phy[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�����ַ�����֣�
char hex_phy[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//�����ַ�����֣�
char addr[65];//�߼���ַ���ֽڣ�
char addr_phy[65];//�����ַ���ֽڣ�

void tonum_phy(void)
{
char i,j;
for (i=0;i<=15;i++)
for (j=0;j<=3;j++)
{
num_phy[i]+=addr_phy[4*i+j]<<(3-j);
}

}

void tohex_phy(void)
{
	char i;
	for (i=0;i<=15;i++)
	{
	if ((num_phy[i]>=0)&&(num_phy[i]<=9))
		hex_phy[i]=num_phy[i]+0x30;
	else hex_phy[i]=num_phy[i]-0x09+0x40;
	}
	
}

void fillLCG(void)//���������������������ͬ��������ġ�
{
lcg[0].multiple=0;	lcg[0].addition=0;
lcg[1].multiple=1;	lcg[1].addition=1;
lcg[2].multiple=3;	lcg[2].addition=1;
lcg[3].multiple=5;	lcg[3].addition=3;
lcg[4].multiple=9;	lcg[4].addition=7;
lcg[5].multiple=19;	lcg[5].addition=13;
lcg[6].multiple=39;	lcg[6].addition=25;
lcg[7].multiple=79;	lcg[7].addition=49;
lcg[8].multiple=159;	lcg[8].addition=97;
lcg[9].multiple=317;	lcg[9].addition=195;
lcg[10].multiple=633;	lcg[10].addition=391;
lcg[11].multiple=1265;	lcg[11].addition=783;
lcg[12].multiple=2531;	lcg[12].addition=1565;
lcg[13].multiple=5063;	lcg[13].addition=3129;
lcg[14].multiple=10125;	lcg[14].addition=6259;
lcg[15].multiple=20251;	lcg[15].addition=12517;
lcg[16].multiple=40503;	lcg[16].addition=25033;
lcg[17].multiple=81007;	lcg[17].addition=50065;
lcg[18].multiple=162013;	lcg[18].addition=100131;
lcg[19].multiple=324027;	lcg[19].addition=200261;
lcg[20].multiple=648055;	lcg[20].addition=400521;
lcg[21].multiple=1296111;	lcg[21].addition=801041;
lcg[22].multiple=2592223;	lcg[22].addition=1602081;
lcg[23].multiple=5184445;	lcg[23].addition=3204163;
lcg[24].multiple=10368889;	lcg[24].addition=6408327;
lcg[25].multiple=20737779;	lcg[25].addition=12816653;
lcg[26].multiple=41475559;	lcg[26].addition=25633305;
lcg[27].multiple=82951117;	lcg[27].addition=51266611;
lcg[28].multiple=165902235;	lcg[28].addition=102533221;
lcg[29].multiple=331804471;	lcg[29].addition=205066441;
lcg[30].multiple=663608943;	lcg[30].addition=410132881;
lcg[31].multiple=1327217885;	lcg[31].addition=820265763;
}

unsigned LCGtreat(unsigned seed,unsigned char bits,unsigned char times)//���������������������ͬ��������ġ�
{
unsigned char i=0;
unsigned __int64 sed=seed;
unsigned ret;
unsigned __int64 mul=lcg[bits].multiple;
unsigned __int64 add=lcg[bits].addition;
unsigned mod=1;
mod=1<<bits;
for (i=0;i<times;i++)
	{
	sed=(((sed*mul)%mod)+add)%mod;
	}
ret=(unsigned)sed;
return ret;
}

void getpagetable(void)
{
	pagetbl.ini=pagesize.bit;
	pagetbl.lth=pagetbl.ini-recsize.bit;
	pagetbl.mod=(64-pagetbl.ini)%pagetbl.lth;
	pagetbl.grd=(64-pagetbl.ini)/pagetbl.lth;
	if (pagetbl.mod==0)
	{
		pagetbl.mod=pagetbl.lth;
		pagetbl.grd--;
	}
}

void numtoaddr(void)
{
	char i=0;
	char j=0;
	for (i=0;i<=15;i++)
	{
		for (j=0;j<=3;j++)
		addr[4*i+j]=(num[i]&(1<<(3-j)))>>(3-j);
	}
}

unsigned __int64 addrtonum(char bgn, char p)//��ȡ��bgn��ʼpλ������
{
	char i=0;
	char t=bgn;
	unsigned __int64 r=0;
	unsigned __int64 reg=1;
	for (i=p-1;i>=0;i--)
	{
		if (addr[t])
		r+=reg<<i;
		t++;
	}
	return r;
}

void numtoaddr_phy(unsigned n, char bgn, char p)//��n����bgn��ʼp���ֽڵ�����addr_phy[]
{
char i=0;
char q=p-1;
for (i=0;i<p;i++)
{
q=p-1-i;
addr_phy[bgn+i]=(n&(1<<q))>>q;
}

}

char pref(unsigned char i)//��ǰ׺
{
	switch (i)
	{
		case 1:return 'k';
		case 2:return 'M';
		case 3:return 'G';
		case 4:return 'T';
		case 5:return 'P';
		case 6:return 'E';
		default:return 'e';
	}
}

struct KILO kilo(unsigned char i)//��ǰ׺
{
struct KILO p;
unsigned char j=i/10;
p.n=i%10;
p.b=1<<p.n;
p.prefix=pref(j);
return p;
}

void input(void)//�����߼���ַ
{
	char i;
	char j=15;
	char strl;
	gets(hex);
	gets(hex);//������2��gets()����Ϊ��һ��gets()��������
	strl=strlen(hex);
	if (strl<16)
	{
		for (i=strl-1;i>=0;i--)
		{
			hex[j]=hex[i];
			j--;
		}
		for (;j>=0;j--)
			hex[j]=0x30;
	}
}

void empty(void)
{
char i;
for (i=0;i<=15;i++)
	hex[i]=0;
}

char checkillegalhex(void)
{
	char i=0;
	char r=0;
	for (i=0;i<=15;i++)
	{
	if (!isxdigit(hex[i]))//ctype.h
	r++;
	else ;
	}
	return r;
}

void hextonum(void)
{
	char i=0;
	for (i=0;i<=15;i++)
	{
		if (isdigit(hex[i]))
			num[i]=hex[i]-0x30;
		else num[i]=(hex[i]%0x20)+0x09;
	}
}

void printhex(char p)
{
if ((p>=0)&&(p<=9))
printf("%d",p);
else printf("%c",p-0x09+0x40);
}

int main()
{
	char beg=0;
	char i=0;
	char confirm=0;
	char logiceqphysic=0;

	unsigned int* p=0;
	unsigned int* part1=0;
	unsigned __int64 part2=0;
	printf("64λϵͳҳ��ʵ��\n");
	do
	{
		printf("������ҳ��С�����ֽ�Ϊ��λȡ��2Ϊ�׵Ķ�������\n");
		do
		{
			scanf("%u",&pagesize.bit);
			if (pagesize.bit<1)
				printf("ҳ��С��Ϊ1�ֽڣ����ҳ��¼��С�޷�ȡֵ�����������롣\n");
			else if (pagesize.bit>=64)
				{
					printf("ҳ��С����Ϊ2��64�η��ֽڣ��߼���ַ���������ַ��\n");
					logiceqphysic=1;
					break;
				}
			else break;
		}while (1);
		if (pagesize.bit<=63)
		{
			pagesize.pwr=1;
			pagesize.pwr=pagesize.pwr<<pagesize.bit;
			printf("�������ҳ��СΪ%I64u�ֽڡ�\n",pagesize.pwr);
			if (pagesize.bit>=10)
			{
				simp=kilo(pagesize.bit);
				printf("��%u%c",simp.b,simp.prefix);
				printf("B��\n");
			}
		}
		else 
			logiceqphysic=1;
		printf("ȷ����\n����1��ʾȷ��������0��ʾȡ����\n");
		scanf("%d",&confirm);
	}while (confirm==0);
	do
	{
		printf("������ҳ��¼��С�����ֽ�Ϊ��λȡ��2Ϊ�׵Ķ�����\n");
		do
		{
			scanf("%u",&recsize.bit);
			if (recsize.bit>=pagesize.bit)
				printf("��ʱһҳ���ֻ�ܴ��һ��ҳ����ΪҪ��һҳ����Ҫ�������ҳ����������������\n");
			else
			{
				recsize.pwr=1;
				recsize.pwr=recsize.pwr<<recsize.bit;
				break;
			}
		}while (1);

		printf("�������ҳ��¼��СΪ%I64u�ֽڡ�\n",recsize.pwr);
			if (recsize.bit>=10)
			{
				simp=kilo(recsize.bit);
				printf("��%u%c",simp.b,simp.prefix);
				printf("B��\n");
			}
		printf("ȷ����\n����1��ʾȷ��������0��ʾȡ����\n");
		scanf("%d",&confirm);
	}while (confirm==0);
	do
	{
		printf("������16�����߼���ַ����Ҫ����0x����h�������ִ�Сд��\n");
		do
		{
		empty();
		input();
		if (checkillegalhex())
			printf("�ⲻ��һ���Ϸ���16�����߼���ַ����������������\n");
		else break;
		}while (1);
		hextonum();
		printf("�������16�����߼���ַ�ǣ�\n");
		for (i=0;i<=15;i++)
			printhex(num[i]);
		printf("\n");
		printf("ȷ����\n����1��ʾȷ��������0��ʾȡ����\n");
		scanf("%d",&confirm);
	}while (confirm==0);

	if (logiceqphysic==1)
		memcpy(addr_phy,addr,65);
	else //�߼���ַ�������ַ���
	{
	getpagetable();
	numtoaddr();
	memcpy(&addr_phy[64-pagesize.bit],&addr[64-pagesize.bit],pagesize.bit);
	beg=pagetbl.mod+pagetbl.lth*pagetbl.grd;
	part2=addrtonum(beg, 64-beg);
	part1=(unsigned int*)calloc(pagetbl.grd+1,4);
	p=part1;
	*p=(unsigned int)addrtonum(0,pagetbl.mod);
		if (pagetbl.grd)
		{
		p=part1+1;
		for (i=0;i<pagetbl.grd;i++)
			{
				*p=(unsigned int)addrtonum(pagetbl.mod+i*pagetbl.lth,pagetbl.lth);
				p++;
			}
		}
	fillLCG();
	p=part1;
	*p=LCGtreat(*p,pagetbl.mod,1);
	p++;
	for (i=1;i<=pagetbl.grd;i++)
		{
			*p=LCGtreat(*p,pagetbl.lth,i);
			/*
			void getpagetable(void)
			{
				pagetbl.ini=pagesize.bit;
				pagetbl.lth=pagetbl.ini-recsize.bit;
				pagetbl.mod=(64-pagetbl.ini)%pagetbl.lth;
				pagetbl.grd=(64-pagetbl.ini)/pagetbl.lth;
				if (pagetbl.mod==0)
				{
					pagetbl.mod=pagetbl.lth;
					pagetbl.grd--;
				}
			}
			*/
			p++;
		}
	p=part1;
	numtoaddr_phy(*p,0,pagetbl.mod);
	p++;
		for (i=0;i<pagetbl.grd;i++)
			{
				numtoaddr_phy(*p,pagetbl.mod+i*pagetbl.lth,pagetbl.lth);
				p++;
			}
	}
		tonum_phy();
		tohex_phy();
printf("��Ӧ�������ַ�ǣ�\n");
for (i=0;i<=15;i++)
printhex(num_phy[i]);
printf("\n");
return 0;
}