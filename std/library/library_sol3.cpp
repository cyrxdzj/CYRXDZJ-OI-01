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
//��ɢ��
int dcnt[250];  //���շֿ������ɢ��
int data[250][MAXC+5];
//�� oiClass �ϣ����û�з���������򣬲������ռ䡣
//��������������Ŀռ���㣬���仰˵������õ� 381MB��
//��Ȼ�������Ҳ���ѣ��� vector ���ɡ� 
void add_data(int id,int x)
{
	data[id][++dcnt[id]]=x;
}
void init_data()
{
	for(int i=1;i<=249;i++)
	{
		if(dcnt[i]==0)  //ÿһ��������һ��������Ϊ�������Ǳ߰� 0 Ҳ���˽�����
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
int id2bid[MAXN+5];
struct Book
{
	int c;
	vector<pair<int,long long>>pages;	//�������� 
	vector<pair<int,long long>>pfx;		//ǰ׺�ͣ�����Ϊ���ﵽ��һ�������Ѷȣ������Ȿ��ĸ���Ϊ�ڶ����� 
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
	}
	void register_dataid(int bid)	//����ɢ�������б�ע����ҳ�Ѷ� 
	{
		for(int i=0;i<c;i++)
		{
			add_data(bid,pages[i].first);
		}
	}
	void fetch_dataid(int bid)	//��ɢ�������б��ʼ����ɺ�����ɢ��������ݣ�ͬʱ����ǰ׺�� 
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
//��״����
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
void change(int bid,int l,int r,Num v)	//��� 
{
	change(bid,l,v);
	if(r+1<=dcnt[bid])
	{
		change(bid,r+1,Num()/v);
	}
}
int BLOCK;	//�鳤 
struct Qry  //�ȴ�ò������Ա���ɢ��
{
	int id;
	int op;
	int l,r,v;
	Book book;
}qry[MAXM+5];
void add_book(int id)	//��һ��������߶����� 
{
	int bid=id2bid[id];	//�Ȿ�����ڵķֿ� 
	int last=get_dataid(id2bid[id],0);
	long long nowsum=0;
	for(pair<int,long>page:a[id].pages)
	{
		change(bid,last,page.first-1,Num(nowsum));
		nowsum=(nowsum+page.second)%MOD;
		last=page.first;
	}
	//����ÿ��� last����Ϊ nowsum=1 ʱ���κ����� 1 ��Ϊ 1�������޸� 
}
void del_book(int id)	//��һ�����뿪�߶���������������ľ��� 
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
	for(int i=BLOCK+1;i<=n;i++)	//����id2bid���㷨������ʹ�ó��� 
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
		tree[i].resize(dcnt[i]+3,Num());	//���迪����״���� 
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
				int vid=upper_bound(data[lbid]+1,data[lbid]+1+dcnt[lbid],qry[qid].v)-data[lbid]-1;	//ÿһ���鶼Ҫ��ã����һ��С�ڵ���ͷ�����Ѷȵ��Ѷ�ֵ 
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
				if((lbid-1)*BLOCK+1==l)	//l ǡ���������� 
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
				if(min(rbid*BLOCK,n)==r)	//r ǡ���������� 
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
				for(int i=lbid+1;i<=rbid-1;i++)	//�����м������ 
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
