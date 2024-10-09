#include "testlib.h"
using namespace std;
const int MAXN=1e5;
int cntx[MAXN+5],cnty[MAXN+5];
bool vis[MAXN+5];
int dcnt;
struct Edge
{
	int to,next;
}edge[MAXN+5];
int edge_cnt;
int head[MAXN+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
void check_tree(int u)
{
	if(vis[u])
	{
		quitf(_fail,"not tree");
		return;
	}
	vis[u]=true;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		check_tree(v);
	}
}
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n=inf.readInt(1,MAXN,"n");
	inf.readSpace();
	int m=inf.readInt(n-1,n-1,"m");
	dcnt=m*2;
	inf.readEoln();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=inf.readInt(1,n);
		inf.readSpace();
		y=inf.readInt(1,n);
		inf.readEoln();
		cntx[x]++;
		cnty[y]++;
		add_edge(x,y);
	}
	inf.readEof();
	int rt=0;
	for(int i=1;i<=n;i++)
	{
		quitif(cnty[i]>1,_fail,"y repeated");
		if(cnty[i]==0)
		{
			rt=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		quitif((cntx[i]+cnty[i])<1,_fail,"something don't appear'");
	}
	check_tree(rt);
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			quitf(_fail,"not tree");
		}
	}
}
