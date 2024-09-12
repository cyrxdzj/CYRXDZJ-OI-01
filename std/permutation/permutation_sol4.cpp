#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
//#define debug 
#define check
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
	#ifdef check//����check���еĴ�����ȫ���Ժ��� �� 
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
		#endif
		add_edge(u,v);
		deg[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(deg[i]==0)//������㡣��Ҫע������ж����㡣 
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
		if(deg[i])//��������ڻ�����Ȳ�Ϊ0�ıߣ�˵��ͼ������˻�������޽⡣ 
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

