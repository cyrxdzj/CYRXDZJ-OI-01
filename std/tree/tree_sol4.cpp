#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug
const int MAXN=1e5,MAXF=18;
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
int n;
int a[MAXN+5];
int b[MAXN+5],c;
long long ans[MAXBIT][MAXN+5];
//树状数组
struct Data
{
	int cnt;
	long long sum,sum2;
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
}tree[2][MAXN+5];
Data operator +(Data a,Data b)
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
int lowbit(int x)
{
	return x&-x;
}
void change(int tid,int x,Data val)
{
	while(x<=dcnt)
	{
		tree[tid][x]=tree[tid][x]+val;
		x+=lowbit(x);
	}
}
Data query(int tid,int x)
{
	Data res;
	while(x)
	{
		res=res+tree[tid][x];
		x-=lowbit(x);
	}
	return res;
}
int getbit(int x,int pos)
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
struct Edge
{
	int to,next;
}edge[MAXN*2+5];
int edge_cnt;
int head[MAXN+5];
int sz[MAXN+5],hson[MAXN+5];
void add_edge(int u,int v)
{
	edge[++edge_cnt]=(Edge){v,head[u]};
	head[u]=edge_cnt;
}
long long nowans=0;
int nowbid;
void pre(int u,int faa)
{
	sz[u]=1;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			pre(v,u);
			sz[u]+=sz[v];
			if(sz[hson[u]]<sz[v])
			{
				hson[u]=v;
			}
		}
	}
}
void add(int u,int val)
{
	int my=getbit(b[u],nowbid);//自己的位
	int to=my^getbit(c,nowbid)^1;
	Data dv=Data(a[u],val);
	Data lower=query(to,a[u]-1),upper=query(to,dcnt)-query(to,a[u]);
	long long diff=0;
	diff=(diff+(data[a[u]]*lower.sum%MOD))%MOD;
	diff=(diff+(upper.sum*data[a[u]]%MOD))%MOD;
	diff=(diff-lower.sum2)%MOD;
	diff=(diff-(data[a[u]]*data[a[u]]%MOD*upper.cnt%MOD))%MOD;
	diff=(diff%MOD+MOD)%MOD;
	nowans=(nowans+val*diff+MOD)%MOD;
	change(my,a[u],dv);
	#ifdef debug
	printf("add %d %d v %d %lld diff %lld\n",u,val,a[u],data[a[u]],diff);
	printf("my %d to %d\n",my,to);
	printf("lower cnt %d sum %lld\n",lower.cnt,lower.sum);
	printf("upper cnt %d sum %lld\n",upper.cnt,upper.sum);
	#endif
}
void dfs_add(int u,int faa,int val)
{
	add(u,val);
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v!=faa)
		{
			dfs_add(v,u,val);
		}
	}
}
void dfs(int u,int faa,bool keep)
{
	if(hson[u])
	{
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(v!=faa&&v!=hson[u])
			{
				dfs(v,u,false);
			}
		}
		dfs(hson[u],u,true);
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(v!=faa&&v!=hson[u])
			{
				dfs_add(v,u,1);
			}
		}
	}
	add(u,1);
	#ifdef debug
	printf("calc %d nowans %lld\n",u,nowans);
	#endif
	ans[nowbid][u]=nowans; 
	if(!keep)
	{
		dfs_add(u,faa,-1);
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
		scanf("%d",&a[i]);
		add_data(a[i]);
	}
	init_data();
	for(int i=1;i<=n;i++)
	{
		a[i]=get_dataid(a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	scanf("%d",&c);
	pre(1,0);
	#ifdef debug
	for(int i=1;i<=n;i++)
	{
		printf("%d sz %d hson %d\n",i,sz[i],hson[i]);
	}
	#endif
	for(nowbid=0;nowbid<MAXBIT;nowbid++)
	{
		#ifdef debug
		printf("----- nowbid %d -----\n",nowbid);
		for(int i=1;i<=n;i++)
		{
			printf("%d",getbit(b[i],nowbid));
		}
		printf(" %d\n",getbit(c,nowbid));
		#endif
		dfs(1,0,true);
		nowans=0;
		for(int i=0;i<=n;i++)
		{
			tree[0][i]=Data();
			tree[1][i]=Data();
		}
		/*for(int i=1;i<=n;i++)
		{
			printf("%lld",(ans[i]*2ll*c)%MOD);
			if(i<n)
			{
				printf("\n");
			}
		}
		return 0;*/
	}
	for(int i=1;i<=n;i++)
	{
		long long anssum=0;
		for(int j=0;j<MAXBIT;j++)
		{
			anssum=(anssum+(ans[j][i]*(1ll<<j)%MOD))%MOD;
		}
		printf("%lld\n",anssum*2%MOD);
	}
}
