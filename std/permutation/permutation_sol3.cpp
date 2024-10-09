#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug 
const int MAXN=1e5,MAXM=5e5;
int n,m;
struct Edge
{
	int to,next;
}edge[MAXM+5];
int edge_cnt;
int head[MAXN+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
int deg[MAXN+5];
int nowdfn;
int ans[MAXN+5];
void dfs(int u,int fa)
{
	ans[u]=++nowdfn;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=fa)
		{
			dfs(v,u);
		}
	}
}
int main()
{
	freopen("permutation.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		deg[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(deg[i]==0)
		{
			dfs(i,0);
			break;
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
	return 0;
}

