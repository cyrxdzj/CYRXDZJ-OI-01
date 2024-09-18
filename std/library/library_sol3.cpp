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
const int MAXN=5e4,MAXM=5e4,MAXC=4e5+1;
const long long MOD=998244353;
//离散化
int dcnt[250];  //按照分块进行离散化
int data[250][MAXC+5];
//在 oiClass 上，如果没有访问这块区域，不会计算空间。
//但正赛按照申请的空间计算，换句话说这里会用掉 381MB。
//当然解决方案也不难，用 vector 即可。 
void add_data(int id,int x)
{
	data[id][++dcnt[id]]=x;
}
void init_data()
{
	for(int i=1;i<=249;i++)
	{
		if(dcnt[i]==0)  //每一块至少有一个数（因为主程序那边把 0 也加了进来）
		{
			return;
		}
		sort(data[i]+1,data[i]+1+dcnt[i]);
		dcnt[i]=unique(data[i]+1,data[i]+1+dcnt[i])-data[i]-1;
	}
}
int get_dataid(int id,int x)
{
	return lower_bound(data[id]+1,data[id]+1+dcnt[id],x)-data[id];
}
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
int id2bid[MAXN+5];
struct Book
{
	int c;
	vector<pair<int,long long>>pages;	//输入数据 
	vector<pair<int,long long>>pfx;		//前缀和，意义为，达到第一个数的难度，看懂这本书的概率为第二个数 
	void read_book_abort()
	{
		pages.clear();
		scanf("%d",&c);
		for(int i=0;i<c;i++)
		{
			int d;
			scanf("%d",&d);
			pages.push_back(make_pair(d,0));
		}
		for(int i=0;i<c;i++)
		{
			scanf("%lld",&pages[i].second);
		}
		sort(pages.begin(),pages.end());
		return;
	}
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
	}
	void register_dataid(int bid)	//向离散化数据列表注册书页难度 
	{
		for(int i=0;i<c;i++)
		{
			add_data(bid,pages[i].first);
		}
	}
	void fetch_dataid(int bid)	//离散化数据列表初始化完成后获得离散化后的数据，同时计算前缀和 
	{
		long long nowsum=0;
		pfx.clear();
		pfx.push_back(make_pair(0,0ll));
		for(int i=0;i<(int)pages.size();i++)
		{
			pages[i].first=get_dataid(bid,pages[i].first);
			nowsum=(nowsum+pages[i].second)%MOD;
			pfx.push_back(make_pair(pages[i].first,nowsum));
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
//树状数组
vector<Num>tree[250];
int lowbit(int x)
{
	return x&-x;
}
void change(int bid,int x,Num v)
{
	while(x<=dcnt[bid])
	{
		tree[bid][x]=(tree[bid][x]*v);
		x+=lowbit(x);
	}
}
Num query(int bid,int x)
{
	Num res=Num();
	while(x)
	{
		res=res*tree[bid][x];
		x-=lowbit(x);
	}
	return res;
}
void change(int bid,int l,int r,Num v)	//差分 
{
	change(bid,l,v);
	if(r+1<=dcnt[bid])
	{
		change(bid,r+1,Num()/v);
	}
}
int BLOCK;	//块长 
struct Qry  //先存好操作，以便离散化
{
	int id;
	int op;
	int l,r,v;
	Book book;
}qry[MAXM+5];
void add_book(int id)	//将一本书加入线段树中 
{
	int bid=id2bid[id];	//这本书所在的分块 
	int last=get_dataid(id2bid[id],0);
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(nowsum));
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
	//最后不用考虑 last，因为 nowsum=1 时，任何数乘 1 都为 1，不必修改 
}
void del_book(int id)	//让一本书离开线段树，几乎是上面的镜像 
{
	int bid=id2bid[id];
	int last=get_dataid(id2bid[id],0);
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(1)/Num(nowsum));
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
	for(int i=1;i<=id2bid[n];i++)
	{
		add_data(i,0);
	}
	for(int i=1;i<=n;i++)
	{
		a[i].read_book();
		a[i].register_dataid(id2bid[i]);
	}
	read(m); 
	for(int qid=1;qid<=m;qid++)
	{
		qry[qid].id=qid;
		read(qry[qid].op);
		if(qry[qid].op==1)
		{
			read(qry[qid].l);read(qry[qid].r);read(qry[qid].v);
		}
		else
		{
			read(qry[qid].l);
			qry[qid].book.read_book();
			qry[qid].book.register_dataid(id2bid[qry[qid].l]);
		}
	}
	init_data();
	for(int i=1;i<=id2bid[n];i++)
	{
		tree[i].resize(dcnt[i]+3,Num());	//按需开点树状数组 
	}
	for(int i=1;i<=n;i++)
	{
		a[i].fetch_dataid(id2bid[i]);
	}
	for(int i=1;i<=n;i++)
	{
		add_book(i);
	}
	for(int qid=1;qid<=m;qid++)
	{
		if(qry[qid].op==2)
		{
			qry[qid].book.fetch_dataid(id2bid[qry[qid].l]);
		}
	}
	for(int qid=1;qid<=m;qid++)
	{
		if(qry[qid].op==2)
		{
			del_book(qry[qid].l);
			a[qry[qid].l]=qry[qid].book;
			add_book(qry[qid].l);
		}
		else
		{
			Num res=Num();
			int l=qry[qid].l,r=qry[qid].r;
			int lbid=(l-1)/BLOCK+1;
			int rbid=(r-1)/BLOCK+1;
			if(lbid==rbid)
			{
				int vid=upper_bound(data[lbid]+1,data[lbid]+1+dcnt[lbid],qry[qid].v)-data[lbid]-1;	//每一个块都要获得，最后一个小于等于头脑清醒度的难度值 
				if((lbid-1)*BLOCK+1==qry[qid].l&&min(rbid*BLOCK,n)==qry[qid].r)
				{
					res=query(lbid,vid);
				}
				else
				{
					for(int i=l;i<=r;i++)
					{
						res=res*Num(a[i].get_probability(vid));
					}
				}
			}
			else
			{
				int vid=upper_bound(data[lbid]+1,data[lbid]+1+dcnt[lbid],qry[qid].v)-data[lbid]-1;
				if((lbid-1)*BLOCK+1==l)	//l 恰好在整块中 
				{
					res=res*query(lbid,vid);
				}
				else
				{
					for(int i=l;i<=lbid*BLOCK;i++)
					{
						res=res*Num(a[i].get_probability(vid));
					}
				}
				vid=upper_bound(data[rbid]+1,data[rbid]+1+dcnt[rbid],qry[qid].v)-data[rbid]-1;
				if(min(rbid*BLOCK,n)==r)	//r 恰好在整块中 
				{
					res=res*query(rbid,vid);
				}
				else
				{
					for(int i=(rbid-1)*BLOCK+1;i<=r;i++)
					{
						res=res*Num(a[i].get_probability(vid));
					}
				}
				for(int i=lbid+1;i<=rbid-1;i++)	//计算中间的整块 
				{
					vid=upper_bound(data[i]+1,data[i]+1+dcnt[i],qry[qid].v)-data[i]-1;
					res=res*query(i,vid);
				}
			}
			write((long long)res);
			putchar('\n');
		}
	}
	return 0;
}
