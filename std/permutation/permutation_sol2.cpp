#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug 
#define check
const int MAXN=1e5,MAXM=5e5;
int n,m;
int ans[MAXN+5];
int nowans;
#ifdef check
bool cka[MAXN+5];
#endif
int main()
{
	freopen("permutation.in","r",stdin);
	scanf("%d%d",&n,&m);
	#ifdef check
	if(n<1||n>100000||m<0||m>400000)
	{
		printf("\033[31mData Check Failed.\n");
		printf("n %d m %d\033[0m\n",n,m);
		return 1;
	}
	#endif
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		#ifdef check
		if(u<1||u>n||v<1||v>n)
		{
			printf("\033[31mData Check Failed.\n");
			printf("Rule ID %d x %d y %d\033[0m\n",i,u,v);
			return 1;
		}
		if(!cka[u])
		{
			cka[u]=true;
		}
		else
		{
			printf("\033[31mData Check Failed.\n");
			printf("Rule repeated. ID %d u %d\033[0m\n",i,u);
			return 1;
		}
		if(!cka[v])
		{
			cka[v]=true;
		}
		else
		{
			printf("\033[31mData Check Failed.\n");
			printf("Rule repeated. ID %d v %d\033[0m\n",i,v);
			return 1;
		}
		#endif
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
