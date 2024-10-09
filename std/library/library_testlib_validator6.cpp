#include "testlib.h"

using namespace std;
//针对各个测试点的各种限制 
const int MAXN=5e4,MAXM=5e4,MAXC=4e5,MAXCI=MAXC;
const int MAXOP=2;
const int MAXVAL=1e9;
const long long MOD=998244353;
int n,m;
int csum;
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	n=inf.readInt(1,MAXN);
	inf.readEoln();
	for(int i=1;i<=n;i++)
	{
		int c=inf.readInt(1,MAXCI);
		inf.readEoln();
		csum+=c;
		if(csum>MAXC)
		{
			quitf(_fail,"C > %d",MAXC);
		}
		for(int j=1;j<=c;j++)
		{
			int d=inf.readInt(1,MAXVAL);
			if(j<c)
			{
				inf.readSpace();
			}
			else
			{
				inf.readEoln();
			}
		}
		long long psum=0;
		for(int j=1;j<=c;j++)
		{
			int p=inf.readInt(1,MOD-1);
			psum=(psum+p)%MOD;
			if(j<c)
			{
				inf.readSpace();
			}
			else
			{
				inf.readEoln();
			}
		}
		quitif(psum!=1,_fail,"probability sum != 1");
	}
	m=inf.readInt(1,MAXM);
	inf.readEoln();
	while(m--)
	{
		int op=inf.readInt(1,MAXOP);
		inf.readSpace();
		if(op==1)
		{
			int l,r,v;
			l=inf.readInt(1,n);
			inf.readSpace();
			r=inf.readInt(l,l);
			inf.readSpace();
			v=inf.readInt(1,MAXVAL);
			inf.readEoln();
		}
		else
		{
			int x=inf.readInt(1,n);
			inf.readEoln();
			int c=inf.readInt(1,MAXCI);
			inf.readEoln();
			csum+=c;
			if(csum>MAXC)
			{
				quitf(_fail,"C > %d",MAXC);
			}
			for(int j=1;j<=c;j++)
			{
				int d=inf.readInt(1,MAXVAL);
				if(j<c)
				{
					inf.readSpace();
				}
				else
				{
					inf.readEoln();
				}
			}
			long long psum=0;
			for(int j=1;j<=c;j++)
			{
				int p=inf.readInt(1,MOD-1);
				psum=(psum+p)%MOD;
				if(j<c)
				{
					inf.readSpace();
				}
				else
				{
					inf.readEoln();
				}
			}
			quitif(psum!=1,_fail,"probability sum != 1");
		}
	}
	inf.readEof();
}
