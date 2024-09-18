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
//����
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
int id2bid[MAXN+5];	//��������ڿ�ı�ţ��Լ��ٳ���ʹ�á� 
struct Book
{
	int c;
	vector<pair<int,long long>>pages;	//�������� 
	vector<pair<int,long long>>pfx;		//ǰ׺�ͣ�����Ϊ���ﵽ��һ�������Ѷȣ������Ȿ��ĸ���Ϊ�ڶ����� 
	void read_book()
	{
		vector<pair<int,long long>>repeat_pages;	//�����ظ��Ѷȵ���ҳ 
		read(c);		//����ҳ�� 
		for(int i=0;i<c;i++)
		{
			int d;
			read(d);	//�����ҳ���Ѷ� 
			repeat_pages.push_back(make_pair(d,0));
		}
		for(int i=0;i<c;i++)
		{
			read(repeat_pages[i].second);	//�����ҳ����� 
		}
		sort(repeat_pages.begin(),repeat_pages.end());	//������׼��ȥ�� 
		pages.clear();
		pages.reserve(c);	//���������ܻ�δ֪ԭ��� Segment Fault����������ռ�̫��λ���� 
		for(auto page:repeat_pages)	//ȥ�� 
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
		long long nowsum=0;	//����ǰ׺�� 
		pfx.clear();
		pfx.push_back(make_pair(0,0ll));	//����Ӹ�0��������ѯʱ�Ͳ������У����ʹ��븴�Ӷ� 
		for(int i=0;i<(int)pages.size();i++)
		{
			nowsum=(nowsum+pages[i].second)%MOD;
			if(i==(int(pages.size())-1)||(pages[i].first!=pages[i+1].first))
			{
				pfx.push_back(make_pair(pages[i].first,nowsum));
			}
		}
	}
	long long get_probability(int x)	//��ͷ�����Ѷ�Ϊ x ʱ���ж��ĸ��ʿ����Ȿ�飿 
	{
		vector<pair<int,long long>>::iterator it=upper_bound(pfx.begin(),pfx.end(),make_pair(x,(long long)0x3fffffffffff));
		it--;
		return it->second;
	}
}a[MAXN+5];
//������
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
	int lc,rc;		//���Ҷ��� 
	Num lazy,val;	//������ڵ�û�����Ҷ���ʱ��val ��Ϊ�������������ͷ�����Ѷȶ�Ӧ�ĸ��ʣ��������Ҷ��ӣ��� val �����塣 
}tree[30000000];	//�����С���Ѷ�����̫�߱��ռ䣬��̫�ͻ� RE 
int pcnt;	//��̬����ĵ��� 
int rt[250];	//ÿһ���Ӧ�Ŀ��߶��� 
void handle(int o,Num v)	//���ڵ��޸Ĳ���ͳһ��װΪhandle 
{
	tree[o].lazy=(tree[o].lazy*v);
	tree[o].val=(tree[o].val*v);
}
int new_node(int o,int tl,int tr)//�½�һ���ڵ㡣����������ڼ���֮������е��жϡ� 
{
	if(o)	//���нڵ� 
	{
		return o;
	}
	o=++pcnt;
	tree[o].lc=tree[o].rc=0;
	tree[o].lazy=Num();
	tree[o].val=Num();
	return o;
}
void pushdown(int o,int tl,int tr)	//�´���Ǻ��� 
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
	if(tl==tr||(tree[o].lc==0&&tree[o].rc==0))//�ѵ�������ӽڵ� 
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
int BLOCK;	//�鳤 
void add_book(int id)	//��һ��������߶����� 
{
	int bid=id2bid[id];	//�Ȿ�����ڵķֿ� 
	int last=MIND;
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(nowsum),MIND,MAXD);
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
	//����ÿ��� last����Ϊ nowsum=1 ʱ���κ����� 1 ��Ϊ 1�������޸� 
}
void del_book(int id)	//��һ�����뿪�߶���������������ľ��� 
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
	for(int i=BLOCK+1;i<=n;i++)	//����id2bid���㷨������ʹ�ó��� 
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
				if((lbid-1)*BLOCK+1==l&&min(rbid*BLOCK,n)==r)	//l �� r ǡ����һ�������� 
				{
					res=query(rt[lbid],v,MIND,MAXD);
				}
				else
				{
					for(int i=l;i<=r;i++)	//ɢ�� 
					{
						res=res*Num(a[i].get_probability(v));
					}
				}
			}
			else
			{
				if((lbid-1)*BLOCK+1==l)	//l ǡ���������� 
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
				if(min(rbid*BLOCK,n)==r)	//r ǡ���������� 
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
				for(int i=lbid+1;i<=rbid-1;i++)	//�����м������ 
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
