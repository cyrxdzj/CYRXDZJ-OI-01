#include<cstdio>
#include<algorithm>
using namespace std;
///#define debug
//FastIO
template<typename T>
void read(T &x)
{
	x=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		{
			f*=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	x*=f;
}
template<typename T>
void write(T x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
	{
		write(x/10);
	}
	putchar('0'+(x%10));
}
const int MAXN=1e5;
const int MAXBIT=6;
const long long MOD=998244353;
//离散化
int dcnt;
long long data[MAXN+5];
void add_data(long long x)
{
	data[++dcnt]=x;
}
void init_data()
{
	sort(data+1,data+1+dcnt);
	dcnt=unique(data+1,data+1+dcnt)-data-1;
}
int get_dataid(long long x)
{
	return lower_bound(data+1,data+1+dcnt,x)-data;
}
//基本内容 
int n;
int a[MAXN+5];
int b[MAXN+5],c;
long long ans[MAXBIT][MAXN+5];	//分开每一位存储 
int nowbid;	//当前在枚举第几位？ 
struct Data
{
	int cnt;
	long long sum,sum2;	//sum2 即为平方和 
	Data()
	{
		cnt=0;
		sum=0ll;
		sum2=0ll;
	}
	Data(int id,int c=1)
	{
		cnt=c;
		sum=data[id]*c%MOD;
		sum2=data[id]*data[id]%MOD*c%MOD;
	}
};
Data operator +(Data a,Data b)	//重载运算符以方便后续编写代码 
{
	Data res;
	res.cnt=a.cnt+b.cnt;
	res.sum=(a.sum+b.sum)%MOD;
	res.sum2=(a.sum2+b.sum2)%MOD;
	return res;
}
Data operator -(Data a,Data b)
{
	Data res;
	res.cnt=a.cnt-b.cnt;
	res.sum=(((a.sum-b.sum)%MOD)+MOD)%MOD;
	res.sum2=(((a.sum2-b.sum2)%MOD)+MOD)%MOD;
	return res;
}
int getbit(int x,int pos)	//获取 x 的 pos 位内容 
{
	return (x>>pos)&1;
}
int setbit(int x,int pos,int v)
{
	if(getbit(x,pos)!=v)
	{
		x^=(1<<pos);
	}
	return x;
}
struct Tree
{
	int lc,rc;
	Data data[2];
	long long res;
	void clear()
	{
		lc=rc=0;
		res=0ll;
		data[0]=data[1]=Data();
	}
}tree[5000005];
int rt[MAXN+5];
int pcnt;
void update(int o)
{
	int lc=tree[o].lc,rc=tree[o].rc;	//权值线段树，左节点比右节点更小 
	for(int i=0;i<=1;i++)
	{
		tree[o].data[i]=tree[lc].data[i]+tree[rc].data[i];
	}
	tree[o].res=(tree[lc].res+tree[rc].res)%MOD;
	for(int i=0;i<=1;i++)
	{
		int j=i^getbit(c,nowbid)^1;	//j 代表能和 i 产生贡献的位的值 
		tree[o].res=(tree[o].res+(tree[lc].data[i].sum*tree[rc].data[j].sum%MOD))%MOD;
		tree[o].res=(tree[o].res-(tree[lc].data[i].sum2*tree[rc].data[j].cnt%MOD)+MOD)%MOD;
	}
}
void insert(int o,int x,int b,int tl,int tr)
{
	if(tl==tr)
	{
		tree[o].data[b]=tree[o].data[b]+Data(x);
		return;
	}
	int mid=(tl+tr)>>1;
	if(mid>=x)
	{
		if(tree[o].lc==0)
		{
			tree[o].lc=++pcnt;
			tree[pcnt].clear();
		}
		insert(tree[o].lc,x,b,tl,mid);
	}
	else
	{
		if(tree[o].rc==0)
		{
			tree[o].rc=++pcnt;
			tree[pcnt].clear();
		}
		insert(tree[o].rc,x,b,mid+1,tr);
	}
	update(o);
}
void combine(int o1,int o2,int tl,int tr)
{
	if(tl==tr)
	{
		for(int i=0;i<=1;i++)
		{
			tree[o1].data[i]=tree[o1].data[i]+tree[o2].data[i];
		}
		return;
	}
	int mid=(tl+tr)>>1;
	if(tree[o1].lc==0)
	{
		tree[o1].lc=tree[o2].lc;
	}
	else if(tree[o2].lc)
	{
		combine(tree[o1].lc,tree[o2].lc,tl,mid);
	}
	if(tree[o1].rc==0)
	{
		tree[o1].rc=tree[o2].rc;
	}
	else if(tree[o2].rc)
	{
		combine(tree[o1].rc,tree[o2].rc,mid+1,tr);
	}
	update(o1);
}
#ifdef debug
void debug_prt(int o,int tl,int tr)
{
	if(tree[o].data[0].cnt+tree[o].data[1].cnt==0)
	{
		return;
	}
	printf("o %d %d-%d cnt0 %d sum0 %lld cnt1 %d sum1 %lld res %lld\n",o,tl,tr,tree[o].data[0].cnt,tree[o].data[0].sum,tree[o].data[1].cnt,tree[o].data[1].sum,tree[o].res);
	if(tl==tr)
	{
		return;
	}
	int mid=(tl+tr)>>1;
	debug_prt(tree[o].lc,tl,mid);
	debug_prt(tree[o].rc,mid+1,tr);
}
#endif
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
void dfs(int u,int faa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			dfs(v,u);
			combine(rt[u],rt[v],1,dcnt);
		}
	}
	insert(rt[u],a[u],getbit(b[u],nowbid),1,dcnt);
	ans[nowbid][u]=tree[rt[u]].res;
}
int main()
{
	freopen("tree.in","r",stdin);
	#ifndef debug
	freopen("tree.out","w",stdout);
	#endif
	read(n);
	for(int i=1,u,v;i<n;i++)
	{
		read(u);read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		add_data(a[i]);
	}
	init_data();
	for(int i=1;i<=n;i++)
	{
		a[i]=get_dataid(a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		read(b[i]);
	}
	read(c);
	#ifdef debug_
	rt[0]=++pcnt;
	insert(rt[0],5,1,1,dcnt);
	insert(rt[0],1,1,1,dcnt);
	//printf("%lld\n",tree[rt[0]].res);
	debug_prt(rt[0],1,dcnt);
	#endif
	for(nowbid=0;nowbid<MAXBIT;nowbid++)
	{
		pcnt=0;
		for(int i=1;i<=n;i++)
		{
			rt[i]=++pcnt;
			tree[pcnt].clear();
		}
		dfs(1,0);
		#ifdef debug
		printf("pcnt %d\n",pcnt);
		#endif
	}
	for(int i=1;i<=n;i++)
	{
		long long anssum=0;
		for(int j=0;j<MAXBIT;j++)
		{
			anssum=(anssum+(ans[j][i]*(1ll<<j)%MOD))%MOD;	//计算每一位的总和 
		}
		//printf("%lld\n",anssum*2%MOD);
		#ifndef debug
		write(anssum*2%MOD);	//别忘了乘 2 
		putchar('\n');
		#endif
	}
	return 0;
}
