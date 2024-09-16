#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
//#define debug
const int MAXN=5e4,MAXM=2e4,MAXC=2e5+1;
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
	vector<pair<int,long long>>pfx;
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
		pages.shrink_to_fit();
		return;
	}
	void register_dataid()
	{
		for(int i=0;i<c;i++)
		{
			add_data(pages[i].first);
		}
	}
	void fetch_dataid()
	{
		long long nowsum=0;
		pfx.clear();
		pfx.push_back(make_pair(0,0ll));
		for(int i=0;i<(int)pages.size();i++)
		{
			pages[i].first=get_dataid(pages[i].first);
			nowsum=(nowsum+pages[i].second)%MOD;
			pfx.push_back(make_pair(pages[i].first,nowsum));
		}
		pfx.shrink_to_fit();
	}
	long long get_probability(int x)
	{
		vector<pair<int,long long>>::iterator it=upper_bound(pfx.begin(),pfx.end(),make_pair(x,(long long)0x3fffffffffff));
		it--;
		return it->second;
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
//树状数组
Num tree[200][MAXC+5];
int lowbit(int x)
{
	return x&-x;
}
void change(int id,int x,Num v)
{
	#ifdef debug
	printf("change_tree bid %d pos %d %lld %d\n",id,x,v.data,v.cnt0);
	#endif
	while(x<=dcnt)
	{
		tree[id][x]=(tree[id][x]*v);
		x+=lowbit(x);
	}
}
Num query(int bid,int x)
{
	Num res=Num();
	#ifdef debug
	printf("query_tree %d %d ",bid,x);
	#endif
	while(x)
	{
		res=res*tree[bid][x];
		x-=lowbit(x);
	}
	#ifdef debug
	printf("%lld %d\n",res.data,res.cnt0);
	#endif
	return res;
}
void change(int bid,int l,int r,Num v)
{
	change(bid,l,v);
	if(r+1<=dcnt)
	{
		change(bid,r+1,Num()/v);
	}
}
int BLOCK;
struct Qry
{
	int id;
	int op;
	int l,r,v;
	Book book;
}qry[MAXM+5];
void add_book(int id)
{
	int bid=(id-1)/BLOCK+1;
	int last=get_dataid(0);
	long long nowsum=0;
	#ifdef debug
	printf("add_block id %d bid %d\n",id,bid);
	#endif
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(nowsum));
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
}
void del_book(int id)
{
	int bid=(id-1)/BLOCK+1;
	int last=get_dataid(0);
	long long nowsum=0;
	#ifdef debug
	printf("del_book id %d bid %d\n",id,bid);
	#endif
	for(pair<int,long>page:a[id].pages)
	{
		#ifdef debug
		//printf("%d %d %lld\n",last,page.first-1,nowsum);
		//fflush(stdout);
		#endif
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
	scanf("%d",&n);
	BLOCK=sqrt(n)*1.5;
	//BLOCK=2;
	add_data(0);
	for(int i=1;i<=n;i++)
	{
		#ifdef debug
		nowread=i;
		#endif
		a[i].read_book();
		a[i].register_dataid();
		#ifdef debug
		if(i%100==0)
		{
			printf("i %d c %d\n",i,a[i].c);
			fflush(stdout);
		}
		#endif
	}
	scanf("%d",&m);
	for(int qid=1;qid<=m;qid++)
	{
		qry[qid].id=qid;
		scanf("%d",&qry[qid].op);
		if(qry[qid].op==1)
		{
			scanf("%d%d%d",&qry[qid].l,&qry[qid].r,&qry[qid].v);
		}
		else
		{
			scanf("%d",&qry[qid].l);
			qry[qid].book.read_book();
			qry[qid].book.register_dataid();
		}
	}
	init_data();
	for(int i=1;i<=n;i++)
	{
		a[i].fetch_dataid();
	}
	for(int i=1;i<=n;i++)
	{
		add_book(i);
		#ifdef debug
		//printf("%lld\n",(long long)query(1,2));
		#endif
	}
	for(int qid=1;qid<=m;qid++)
	{
		if(qry[qid].op==2)
		{
			qry[qid].book.fetch_dataid();
		}
	}
	#ifdef debug
	printf("dcnt %d\n",dcnt);
	for(int i=1;i<=dcnt;i++)
	{
		printf("%d ",data[i]);
	}
	printf("\n");
	#endif
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
			int vid=upper_bound(data+1,data+1+dcnt,qry[qid].v)-data-1;
			Num res=Num();
			int l=qry[qid].l,r=qry[qid].r;
			int lbid=(l-1)/BLOCK+1;
			int rbid=(r-1)/BLOCK+1;
			#ifdef debug
			printf("l %d r %d lbid %d rbid %d vid %d\n",l,r,lbid,rbid,vid);
			#endif
			if(lbid==rbid)
			{
				if((lbid-1)*BLOCK+1==qry[qid].l&&min(rbid*BLOCK,n)==qry[qid].r)
				{
					#ifdef debug
					printf("full block\n");
					#endif
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
				if((lbid-1)*BLOCK+1==l)
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
				for(int i=(rbid-1)*BLOCK+1;i<=r;i++)
				{
					res=res*Num(a[i].get_probability(vid));
				}
				for(int i=lbid+1;i<=rbid-1;i++)
				{
					res=res*query(i,vid);
				}
			}
			/*for(int i=l;i<=r;i++)
			{
				res=res*Num(a[i].get_probability(vid));
			}*/
			printf("%lld\n",(long long)res);
			/*#ifdef debug
			for(int i=1;i<=6;i++)
			{
				printf("i %d data %d query %lld %d\n",i,data[i],query(1,i).data,query(1,i).cnt0);
			}
			#endif
			return 0;*/
		}
	}
	return 0;
}
