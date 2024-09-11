#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug 
#define check
int n,m;
int a[15];
int x[15],y[15];
int ans[15];
bool vis[15];
void dfs(int pos)
{
	if(pos>n)
	{
		#ifdef debug_
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
		#endif
		bool flag=true;
		for(int i=1;i<=m;i++)
		{
			if(a[x[i]]>=a[y[i]])
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			for(int i=1;i<=n;i++)
			{
				ans[i]=a[i];
			}
		}
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=true;
			a[pos]=i;
			dfs(pos+1);
			vis[i]=false;
			if(ans[1])
			{
				break;
			}
		}
	}
}
int main()
{
	freopen("permutation.in","r",stdin);
	scanf("%d%d",&n,&m);
	#ifdef check
	if(n<1||n>10||m<0||m>5)
	{
		printf("\033[31mData Check Failed.\n");
		printf("n %d m %d\033[0m\n",n,m);
		return 1;
	}
	#endif
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		#ifdef check
		if(x[i]<1||x[i]>n||y[i]<1||y[i]>n)
		{
			printf("\033[31mData Check Failed.\n");
			printf("Rule ID %d x %d y %d\033[0m\n",i,x[i],y[i]);
			return 1;
		}
		#endif
	}
	#ifndef debug
	freopen("permutation.out","w",stdout);
	#endif
	dfs(1);
	if(ans[1]==0)
	{
		printf("-1\n");
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			printf("%d",ans[i]);
			if(i!=n)
			{
				printf(" ");
			}
		}
	}
	return 0;
}

