#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug
const int MAXN=1e5,MAXF=18;
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
int dep[MAXN+5];
int fa[MAXN+5][MAXF+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
void pre(int u,int faa)
{
	dep[u]=dep[faa]+1;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			fa[v][0]=u;
			for(int j=1;j<=MAXF;j++)
			{
				fa[v][j]=fa[fa[v][j-1]][j-1];
			}
			pre(v,u);
		}
	}
}
int lca(int u,int v)
{
	if(dep[u]<dep[v])
	{
		swap(u,v);
	}
	for(int j=MAXF;j>=0;j--)
	{
		if(dep[fa[u][j]]>=dep[v])
		{
			u=fa[u][j];
		}
	}
	if(u==v)
	{
		return u;
	} 
	for(int j=MAXF;j>=0;j--)
	{
		if(fa[u][j]!=fa[v][j])
		{
			u=fa[u][j];
			v=fa[v][j];
		}
	}
	return fa[u][0];
}
void sumup(int u)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=fa[u][0])
		{
			sumup(v);
			ans[u]=(ans[u]+ans[v])%MOD;
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
	pre(1,0);
	for(int u=1;u<=n;u++)
	{
		for(int v=1;v<=n;v++)
		{
			int f=lca(u,v);
			#ifdef debug
			printf("%d %d lca %d\n",u,v,f);
			#endif
			ans[f]=(ans[f]+(abs(a[u]-a[v])*min(a[u],a[v])%MOD*(b[u]^b[v]^c)%MOD))%MOD;
		}
	}
	sumup(1);
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

