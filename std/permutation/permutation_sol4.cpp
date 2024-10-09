#include<cstdio>
#include<algorithm>
#include<queue>
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
queue<int>q;
int deg[MAXN+5];
int nowbfn;
int ans[MAXN+5];
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
		if(deg[i]==0)//发现起点。需要注意可能有多个起点。 
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans[u]=++nowbfn;
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			deg[v]--;
			if(deg[v]==0)
			{
				q.push(v);
			}
		}
	}
	#ifndef debug
	freopen("permutation.out","w",stdout);
	#endif
	for(int i=1;i<=n;i++)
	{
		if(deg[i])//如果到现在还有入度不为0的边，说明图里出现了环，因此无解。 
		{
			printf("-1");
			return 0;
		}
	}
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
