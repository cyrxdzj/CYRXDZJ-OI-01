#include "testlib.h"

using namespace std;

const int MAXN=1200,MAXA=1e9,MAXC=(1<<6)-1;
int n;
int cfa[MAXN+5];
int find_cfa(int x)
{
	if(x==cfa[x])
	{
		return x;
	}
	return cfa[x]=find_cfa(cfa[x]);
}
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	n=inf.readInt(1,MAXN,"n");
	inf.readEoln();
	for(int i=1;i<=n;i++)
	{
		cfa[i]=i;
	}
	for(int i=1,u,v;i<n;i++)
	{
		u=inf.readInt(1,n,"u");
		inf.readSpace();
		v=inf.readInt(1,n,"v");
		inf.readEoln();
		int ru=find_cfa(u),rv=find_cfa(v);
		quitif(ru==rv,_fail,"not tree");
	}
	for(int i=1;i<=n;i++)
	{
		inf.readInt(1,MAXA,"a");
		if(i<n)
		{
			inf.readSpace();
		}
		else
		{
			inf.readEoln();
		}
	}
	for(int i=1;i<=n;i++)
	{
		int b=inf.readInt(0,MAXC,"b");
		if(i<n)
		{
			inf.readSpace();
		}
		else
		{
			inf.readEoln();
		}
	}
	inf.readInt(0,MAXC,"c");
	inf.readEof();
}
