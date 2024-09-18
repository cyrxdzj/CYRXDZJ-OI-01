#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
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
//#define debug
const int MAXN=5e4,MAXM=5e4,MAXC=4e5+1;
const int MIND=0,MAXD=1e9;
const long long MOD=998244353;
//基本
long long qpow(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)
		{
			res=res*a%MOD;
		}
		a=a*a%MOD;
		b>>=1;
	}
	return res;
} 
int n,m;
int id2bid[MAXN+5];	//这个点所在块的编号？以减少除法使用。 
struct Book
{
	int c;
	vector<pair<int,long long>>pages;	//输入数据 
	vector<pair<int,long long>>pfx;		//前缀和，意义为，达到第一个数的难度，看懂这本书的概率为第二个数 
	void read_book()
	{
		vector<pair<int,long long>>repeat_pages;	//可能重复难度的书页 
		read(c);		//输入页数 
		for(int i=0;i<c;i++)
		{
			int d;
			read(d);	//输入各页码难度 
			repeat_pages.push_back(make_pair(d,0));
		}
		for(int i=0;i<c;i++)
		{
			read(repeat_pages[i].second);	//输入各页码概率 
		}
		sort(repeat_pages.begin(),repeat_pages.end());	//排序以准备去重 
		pages.clear();
		pages.reserve(c);	//不加这句可能会未知原因地 Segment Fault，或许申请空间太多次会出错 
		for(auto page:repeat_pages)	//去重 
		{
			if(pages.empty())
			{
				pages.push_back(page);
			}
			else if(pages[int(pages.size())-1].first==page.first)
			{
				pages[int(pages.size())-1].second=(pages[int(pages.size())-1].second+page.second)%MOD;
			}
			else
			{
				pages.push_back(page);
			}
		}
		long long nowsum=0;	//计算前缀和 
		pfx.clear();
		pfx.push_back(make_pair(0,0ll));	//这里加个0，这样查询时就不用特判，降低代码复杂度 
		for(int i=0;i<(int)pages.size();i++)
		{
			nowsum=(nowsum+pages[i].second)%MOD;
			if(i==(int(pages.size())-1)||(pages[i].first!=pages[i+1].first))
			{
				pfx.push_back(make_pair(pages[i].first,nowsum));
			}
		}
	}
	long long get_probability(int x)	//当头脑清醒度为 x 时，有多大的概率看懂这本书？ 
	{
		vector<pair<int,long long>>::iterator it=upper_bound(pfx.begin(),pfx.end(),make_pair(x,(long long)0x3fffffffffff));
		it--;
		return it->second;
	}
}a[MAXN+5];
//特制数
struct Num
{
	int data;
	int cnt0;
	Num()
	{
		data=1;
		cnt0=0;
	}
	Num(long long v)
	{
		if(v==0)
		{
			data=1;
			cnt0=1;
		}
		else
		{
			data=v;
			cnt0=0;
		}
	}
	Num(long long v,int c)
	{
		data=v;
		cnt0=c;
	}
	operator long long()
	{
		if(cnt0>0)
		{
			return 0;
		}
		else
		{
			return data;
		}
	}
};
Num operator *(Num a,Num b)
{
	return (Num){a.data*1ll*b.data%MOD,a.cnt0+b.cnt0};
}
Num operator /(Num a,Num b)
{
	return (Num){a.data*1ll*qpow(b.data,MOD-2)%MOD,a.cnt0-b.cnt0};
}
struct Tree
{
	int lc,rc;		//左右儿子 
	Num lazy,val;	//当这个节点没有左右儿子时，val 即为这个区间下所有头脑清醒度对应的概率；若有左右儿子，则 val 无意义。 
}tree[30000000];	//这个大小很难定，定太高爆空间，定太低会 RE 
int pcnt;	//动态开点的点数 
int rt[250];	//每一块对应哪棵线段树 
void handle(int o,Num v)	//本节点修改操作统一封装为handle 
{
	tree[o].lazy=(tree[o].lazy*v);
	tree[o].val=(tree[o].val*v);
}
int new_node(int o,int tl,int tr)//新建一个节点。这个函数用于减少之后代码中的判断。 
{
	if(o)	//已有节点 
	{
		return o;
	}
	o=++pcnt;
	tree[o].lc=tree[o].rc=0;
	tree[o].lazy=Num();
	tree[o].val=Num();
	return o;
}
void pushdown(int o,int tl,int tr)	//下传标记函数 
{
	if(tl==tr)
	{
		return;
	}
	int mid=(tl+tr)>>1;
	tree[o].lc=new_node(tree[o].lc,tl,mid);
	tree[o].rc=new_node(tree[o].rc,mid+1,tr);
	if(tree[o].lazy!=1)
	{
		handle(tree[o].lc,tree[o].lazy);
		handle(tree[o].rc,tree[o].lazy);
		tree[o].lazy=Num();
	}
}
void change(int o,int l,int r,Num v,int tl,int tr)
{
	if(tl==l&&tr==r)
	{
		handle(o,v);
		return;
	}
	pushdown(o,tl,tr);
	int mid=(tl+tr)>>1;
	if(mid>=r)
	{
		change(tree[o].lc,l,r,v,tl,mid);
	}
	else if(mid<l)
	{
		change(tree[o].rc,l,r,v,mid+1,tr);
	}
	else
	{
		change(tree[o].lc,l,mid,v,tl,mid);
		change(tree[o].rc,mid+1,r,v,mid+1,tr);
	}
}
Num query(int o,int x,int tl,int tr)
{
	if(tl==tr||(tree[o].lc==0&&tree[o].rc==0))//已到最深的子节点 
	{
		return tree[o].val;
	}
	pushdown(o,tl,tr);
	int mid=(tl+tr)>>1;
	if(mid>=x)
	{
		return query(tree[o].lc,x,tl,mid);
	}
	else
	{
		return query(tree[o].rc,x,mid+1,tr);
	}
}
int BLOCK;	//块长 
void add_book(int id)	//将一本书加入线段树中 
{
	int bid=id2bid[id];	//这本书所在的分块 
	int last=MIND;
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(nowsum),MIND,MAXD);
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
	//最后不用考虑 last，因为 nowsum=1 时，任何数乘 1 都为 1，不必修改 
}
void del_book(int id)	//让一本书离开线段树，几乎是上面的镜像 
{
	int bid=id2bid[id];
	int last=MIND;
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(1)/Num(nowsum),MIND,MAXD);
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
}
int main()
{
	freopen("library.in","r",stdin);
	#ifndef debug
	freopen("library.out","w",stdout);
	#endif
	//scanf("%d",&n);
	read(n);
	BLOCK=sqrt(n);
	for(int i=1;i<=BLOCK;i++)
	{
		id2bid[i]=1;
	}
	for(int i=BLOCK+1;i<=n;i++)	//计算id2bid的算法，无需使用除法 
	{
		id2bid[i]=id2bid[i-BLOCK]+1;
	}
	for(int i=1;i<=n;i++)
	{
		a[i].read_book();
	}
	for(int i=1;i<=id2bid[n];i++)
	{
		rt[i]=new_node(rt[i],MIND,MAXD);
	}
	for(int i=1;i<=n;i++)
	{
		add_book(i);
	}
	read(m);
	for(int qid=1;qid<=m;qid++)
	{
		int op;
		scanf("%d",&op);
		if(op==2)
		{
			int x;
			read(x);
			del_book(x);
			a[x].read_book();
			add_book(x);
		}
		else
		{
			int l,r,v;
			read(l);read(r);read(v);
			Num res=Num();
			int lbid=id2bid[l];
			int rbid=id2bid[r];
			if(lbid==rbid)
			{
				if((lbid-1)*BLOCK+1==l&&min(rbid*BLOCK,n)==r)	//l 到 r 恰好在一个整块中 
				{
					res=query(rt[lbid],v,MIND,MAXD);
				}
				else
				{
					for(int i=l;i<=r;i++)	//散块 
					{
						res=res*Num(a[i].get_probability(v));
					}
				}
			}
			else
			{
				if((lbid-1)*BLOCK+1==l)	//l 恰好在整块中 
				{
					res=res*query(rt[lbid],v,MIND,MAXD);
				}
				else
				{
					for(int i=l;i<=lbid*BLOCK;i++)
					{
						res=res*Num(a[i].get_probability(v));
					}
				}
				if(min(rbid*BLOCK,n)==r)	//r 恰好在整块中 
				{
					res=res*query(rt[rbid],v,MIND,MAXD);
				}
				else
				{
					for(int i=(rbid-1)*BLOCK+1;i<=r;i++)
					{
						res=res*Num(a[i].get_probability(v));
					}
				}
				for(int i=lbid+1;i<=rbid-1;i++)	//计算中间的整块 
				{
					res=res*query(rt[i],v,MIND,MAXD);
				}
			}
			write((long long)res);
			putchar('\n');
		}
	}
	return 0; 
}
