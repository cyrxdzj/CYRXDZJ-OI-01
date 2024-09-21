#include<cstdio>
#include<algorithm>
using namespace std;
//#define debug
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
const int MAXBIT=6;	//��� 6 λ 
const long long MOD=998244353;
//��ɢ��
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
//�������� 
int n;
int a[MAXN+5];
int b[MAXN+5],c;
long long ans[MAXBIT][MAXN+5];	//�ֿ�ÿһλ�洢 
int nowbid;	//��ǰ��ö�ٵڼ�λ�� 
long long nowans;	//��ǰ�Ĺ����ܺͣ���Ҫע������������˼�Ĵ𰸲���һ����˼ 
//��״����
struct Data
{
	int cnt;
	long long sum,sum2;	//sum2 ��Ϊƽ���� 
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
}tree[2][MAXN+5];	//����������״���� 
Data operator +(Data a,Data b)	//����������Է��������д���� 
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
void change(int tid,int x,Data val)	//tid Ϊ���ʵ���״������ 
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
int getbit(int x,int pos)	//��ȡ x �� pos λ���� 
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
void add(int u,int val)	//����/ɾ�� a[u]��val=1 ������룬-1����ɾ�� 
{
	int my=getbit(b[u],nowbid);	//b[u] �ڵ� nowbid λ�ϵ�ֵ 
	int to=my^getbit(c,nowbid)^1;	//ֻ�� b[v] �ڵ� nowbid λ��ֵΪ to ʱ�����ܺ� b[u] �������� 
	Data dv=Data(a[u],val);	//�������/ɾ���� Data 
	Data lower=query(to,a[u]-1),upper=query(to,dcnt)-query(to,a[u]);	//lower ����С�� a[u] �ģ�upper ������� a[v] �� 
	long long diff=0;	//diff �ǹ��׵ı仯�������߻��Ǽ���ȡ���� val 
	diff=(diff+(data[a[u]]*lower.sum%MOD))%MOD;
	diff=(diff+(upper.sum*data[a[u]]%MOD))%MOD;
	diff=(diff-lower.sum2)%MOD;
	diff=(diff-(data[a[u]]*data[a[u]]%MOD*upper.cnt%MOD))%MOD;
	diff=(diff%MOD+MOD)%MOD;
	nowans=(nowans+val*diff+MOD)%MOD;
	change(my,a[u],dv);	//ִ�м���/ɾ�� 
	#ifdef debug
	printf("add %d %d v %d %lld diff %lld\n",u,val,a[u],data[a[u]],diff);
	printf("my %d to %d\n",my,to);
	printf("lower cnt %d sum %lld\n",lower.cnt,lower.sum);
	printf("upper cnt %d sum %lld\n",upper.cnt,upper.sum);
	#endif
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
void pre(int u,int faa)	//Ԥ�����ض��� 
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
void dfs_add(int u,int faa,int val)	//�ݹ����/ɾ����������ֱ�Ӽ���� 
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
void dfs(int u,int faa,bool keep)	//����𰸣�keep �����Ƿ������� 
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
	//scanf("%d",&n);
	read(n);
	for(int i=1,u,v;i<n;i++)
	{
		//scanf("%d%d",&u,&v);
		read(u);read(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		//scanf("%d",&a[i]);
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
		//scanf("%d",&b[i]);
		read(b[i]);
	}
	//scanf("%d",&c);
	read(c);
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
		dfs(1,0,false);
	}
	for(int i=1;i<=n;i++)
	{
		long long anssum=0;
		for(int j=0;j<MAXBIT;j++)
		{
			anssum=(anssum+(ans[j][i]*(1ll<<j)%MOD))%MOD;	//����ÿһλ���ܺ� 
		}
		//printf("%lld\n",anssum*2%MOD);
		write(anssum*2%MOD);	//�����˳� 2 
		putchar('\n');
	}
	return 0;
}
