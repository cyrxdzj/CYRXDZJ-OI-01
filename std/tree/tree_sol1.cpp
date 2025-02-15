#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
//#define debug
const int MAXN=1e5;
const long long MOD=998244353;
int n;
long long a[MAXN+5];
int b[MAXN+5],c;
long long ans[MAXN+5];
struct Edge
{
	int to,next;
}edge[MAXN*2+5];
int edge_cnt;
int head[MAXN+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
vector<int>pts;
void dfs2(int u,int fa)
{
	pts.push_back(u);
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=fa)
		{
			dfs2(v,u);
		}
	}
}
void dfs1(int u,int fa)
{
	pts.clear();
	dfs2(u,fa);
	#ifdef debug
	printf("u %d\n",u);
	for(int i:pts)
	{
		printf("%d ",i);
	}
	printf("\n");
	#endif
	for(int v1:pts)
	{
		for(int v2:pts)
		{
			ans[u]=(ans[u]+(abs(a[v1]-a[v2])*min(a[v1],a[v2])%MOD*(b[v1]^b[v2]^c)%MOD))%MOD;
		}
	}
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=fa)
		{
			dfs1(v,u);
		}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	#ifndef debug
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	scanf("%d",&c);
	dfs1(1,0);
	for(int i=1;i<=n;i++)
	{
		printf("%lld",ans[i]);
		if(i<n)
		{
			printf("\n");
		}
	}
	return 0;
}

