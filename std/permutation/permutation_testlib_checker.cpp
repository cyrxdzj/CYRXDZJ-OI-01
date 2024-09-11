#include<cstdio>
#include"testlib.h"
const int MAXN=1e5,MAXM=5e5;
const int FLAG_NOT_PERMUTATION=2,FLAG_NO_SOLUTION=-1,FLAG_BREAK_RULE=1,FLAG_OK=0;
int n,m;
int rx[MAXM+5],ry[MAXM+5];
int outa[MAXN+5];
int ansa[MAXN+5];
int bucket[MAXN+5];
int check(int *a)
{
	if(a[1]==-1)
	{
		return FLAG_NO_SOLUTION;
	}
	for(int i=1;i<=n;i++)
	{
		bucket[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]<1||a[i]>n)
		{
			return FLAG_NOT_PERMUTATION;
		}
		bucket[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(bucket[i]!=1)
		{
			return FLAG_NOT_PERMUTATION;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(!(a[rx[i]]<a[ry[i]]))
		{
			return FLAG_BREAK_RULE;
		}
	}
	return FLAG_OK;
}
int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	n=inf.readInt(1,MAXN);
	m=inf.readInt(0,MAXM);
	for(int i=1;i<=m;i++)
	{
		rx[i]=inf.readInt(1,MAXN);
		ry[i]=inf.readInt(1,MAXN);
	}
	for(int i=1;i<=n;i++)
	{
		outa[i]=ouf.readInt((i==1)?-1:1,n);
		if(outa[i]==-1)
		{
			break;
		}
	}
	for(int i=1;i<=n;i++)
	{
		ansa[i]=ans.readInt((i==1)?-1:1,n);
		if(ansa[i]==-1)
		{
			break;
		}
	}
	int outres=check(outa),ansres=check(ansa);
	if(ansres==FLAG_NOT_PERMUTATION)
	{
		quitf(_fail,"Why ans is not a permutation?");
	}
	else if(ansres==FLAG_BREAK_RULE)
	{
		quitf(_fail,"Why ans breaks the rule?");
	}
	else if(outres==FLAG_NOT_PERMUTATION)
	{
		quitf(_wa,"Out is not a permutation.");
	}
	else if(outres==FLAG_BREAK_RULE)
	{
		quitf(_wa,"Out breaks the rule.");
	}
	else if(ansres==FLAG_NO_SOLUTION)
	{
		if(outres==FLAG_NO_SOLUTION)
		{
			quitf(_ok,"Answer Correct. There are no solutions.");
		}
		else if(outres==FLAG_OK)
		{
			quitf(_fail,"Why ans cannot construct a solution, but out can?");
		}
	}
	else if(ansres==FLAG_OK)
	{
		if(outres==FLAG_NO_SOLUTION)
		{
			quitf(_wa,"There is a solution, but you don't found it.");
		}
		else if(outres==FLAG_OK)
		{
			quitf(_ok,"Answer Correct.");
		}
	}
	quitf(_fail,"Checker will not run to here.");
	return 0;
}

