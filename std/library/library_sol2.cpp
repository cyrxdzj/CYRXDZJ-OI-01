#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
//#define debug
const int MAXN=5e4,MAXM=2e4,MAXC=2e5;
const long long MOD=998244353;
//离散化
int dcnt;
int data[MAXC+5];
void add_data(int x)
{
	data[++dcnt]=x;
}
void init_data()
{
	sort(data+1,data+1+dcnt);
	dcnt=unique(data+1,data+1+dcnt)-data-1;
}
int get_dataid(int x)
{
	return lower_bound(data+1,data+1+dcnt,x)-data;
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
struct Book
{
	int c;
	vector<pair<int,long long>>pages;
	void read_book()
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
	}
}a[MAXN+5];
//特制数
struct Num
{
	long long data;
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
	return (Num){a.data*b.data%MOD,a.cnt0+b.cnt0};
}
Num operator /(Num a,Num b)
{
	return (Num){a.data*qpow(b.data,MOD-2)%MOD,a.cnt0-b.cnt0};
}
//线段树
struct Tree
{
	int l,r;
	Num lazy;
	Num val;//只有叶子节点的val才是有意义的 
}tree[MAXC*5+5];
void handle(int o,Num v)
{
	tree[o].lazy=(tree[o].lazy*v);
	tree[o].val=(tree[o].val*v);
}
void pushdown(int o)
{
	if((long long)(tree[o].lazy)!=1)
	{
		handle(o<<1,tree[o].lazy);
		handle(o<<1|1,tree[o].lazy);
		tree[o].lazy=Num();
	}
}
void build(int o,int l,int r)
{
	tree[o].l=l;
	tree[o].r=r;
	tree[o].lazy=Num();
	if(l==r)
	{
		tree[o].val=Num();
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
void change(int o,int l,int r,long long v)
{
	if(tree[o].l==l&&tree[o].r==r)
	{
		handle(o,Num(v));
		return;
	}
	pushdown(o);
	int mid=(tree[o].l+tree[o].r)>>1;
	if(mid>=r)
	{
		change(o<<1,l,r,v);
	}
	else if(mid<l)
	{
		change(o<<1|1,l,r,v);
	}
	else
	{
		change(o<<1,l,mid,v);
		change(o<<1|1,mid+1,r,v);
	}
}
Num query(int o,int x)
{
	if(tree[o].l==x&&tree[o].r==x)
	{
		return tree[o].val;
	}
	pushdown(o);
	int mid=(tree[o].l+tree[o].r)>>1;
	if(mid>=x)
	{
		return query(o<<1,x);
	}
	else
	{
		return query(o<<1|1,x);
	}
}
int BLOCK;
struct Qry
{
	int id;
	int l,r,v;
}qry[MAXM+5];
long long ans[MAXM+5];
int L=1,R;
void add_book(int id)
{
	#ifdef debug
	printf("add_book %d\n",id);
	#endif
	int last=get_dataid(0);
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		#ifdef debug
		printf("%d %d %lld\n",last,page.first-1,nowsum);
		fflush(stdout);
		#endif
		change(1,last,page.first-1,Num(nowsum));
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
}
void del_book(int id)
{
	#ifdef debug
	printf("del_book %d\n",id);
	#endif
	int last=get_dataid(0);
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		#ifdef debug
		printf("%d %d %lld\n",last,page.first-1,nowsum);
		fflush(stdout);
		#endif
		change(1,last,page.first-1,Num(1)/Num(nowsum));
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
}
int main()
{
	freopen("library.in","r",stdin);
	freopen("library.out","w",stdout);
	scanf("%d",&n);
	BLOCK=sqrt(n);
	add_data(0);
	for(int i=1;i<=n;i++)
	{
		a[i].read_book();
		for(pair<int,long long>page:a[i].pages)
		{
			add_data(page.first);
		}
	}
	init_data();
	#ifdef debug
	for(int i=1;i<=dcnt;i++)
	{
		printf("%lld ",data[i]);
	}
	printf("\n");
	#endif
	build(1,1,dcnt);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)a[i].pages.size();j++)
		{
			a[i].pages[j].first=get_dataid(a[i].pages[j].first);
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int op;
		scanf("%d%d%d%d",&op,&qry[i].l,&qry[i].r,&qry[i].v);
		//printf("%d %d %d\n",qry[i].l,qry[i].r,qry)
		qry[i].id=i;
	}
	sort(qry+1,qry+1+m,[](Qry qa,Qry qb){
		if((qa.l/BLOCK)==(qb.l/BLOCK))
		{
			return qa.r<qb.r;
		}
		return qa.l<qb.l;
	});
	for(int qid=1;qid<=m;qid++)
	{
		int vid=upper_bound(data+1,data+1+dcnt,qry[qid].v)-data-1;
		#ifdef debug
		printf("query %d %d %d(%d)\n",qry[qid].l,qry[qid].r,vid,qry[qid].v);
		#endif
		if(qry[qid].v>=data[dcnt])
		{
			ans[qry[qid].id]=1;
			continue;
		}
		while(R<qry[qid].r)
		{
			R++;
			add_book(R);
		}
		while(L>qry[qid].l)
		{
			L--;
			add_book(L);
		}
		while(R>qry[qid].r)
		{
			del_book(R);
			R--;
		}
		while(L<qry[qid].l)
		{
			del_book(L);
			L++;
		}
		ans[qry[qid].id]=query(1,vid);
	}
	for(int i=1;i<=m;i++)
	{
		printf("%lld\n",ans[i]);
	}
}
