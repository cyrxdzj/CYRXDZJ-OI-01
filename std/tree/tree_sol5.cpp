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
int dfn[MAXN+5],nid[MAXN+5],nowdfn;
int dfn_lca[MAXN*2+5][MAXF+5];
int dfn_lca_cnt;
int dfn_appear[MAXN+5][2];
int lg[MAXN*2+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
void pre(int u,int faa)
{
	dep[u]=dep[faa]+1;
	dfn[u]=++nowdfn;
	nid[dfn[u]]=u;
	dfn_lca_cnt++;
	dfn_lca[dfn_lca_cnt][0]=dfn[u];
	dfn_appear[dfn[u]][0]=dfn_appear[dfn[u]][1]=dfn_lca_cnt;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			pre(v,u);
			dfn_lca_cnt++;
			dfn_lca[dfn_lca_cnt][0]=dfn[u];
			dfn_appear[dfn[u]][1]=dfn_lca_cnt;
		}
	}
}
void build_lca()
{
	for(int i=2;i<=dfn_lca_cnt;i++)
	{
		lg[i]=lg[i/2]+1;
	}
	for(int j=1;j<=lg[dfn_lca_cnt];j++)
	{
		for(int i=1;i+(1<<(j-1))<=dfn_lca_cnt;i++)
		{
			dfn_lca[i][j]=min(dfn_lca[i][j-1],dfn_lca[i+(1<<(j-1))][j-1]);
		}
	}
}
int lca(int u,int v)
{
	int du=dfn[u],dv=dfn[v];
	if(du>dv)
	{
		swap(du,dv);
	}
	int l=dfn_appear[du][0],r=dfn_appear[dv][1];
	int s=lg[r-l+1];
	return nid[min(dfn_lca[l][s],dfn_lca[r-(1<<s)+1][s])];
}
void sumup(int u,int faa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			sumup(v,u);
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
	build_lca();
	#ifdef debug
	for(int i=1;i<=n;i++)
	{
		printf("%d dfn %d\n",i,dfn[i]);
	}
	for(int i=1;i<=dfn_lca_cnt;i++)
	{
		printf("%d ",dfn_lca[i][0]);
	}
	printf("\n");
	#endif
	//return 0;
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
	sumup(1,0);
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

