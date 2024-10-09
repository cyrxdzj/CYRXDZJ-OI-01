#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug 
const int MAXN=1e5,MAXM=5e5;
int n,m;
int ans[MAXN+5];
int nowans;
int main()
{
	freopen("permutation.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ans[u]=++nowans;
		ans[v]=++nowans;
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]==0)
		{
			ans[i]=++nowans;
		}
	}
	#ifndef debug
	freopen("permutation.out","w",stdout);
	#endif
	for(int i=1;i<=n;i++)
	{
		printf("%d",ans[i]);
		if(i!=n)
		{
			printf(" ");
		}
	}
}
