#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
//#define debug
const int MAXN=5e4,MAXM=2e4,MAXC=2e5+1;
const long long MOD=998244353;
//»ù±¾
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
		long long nowsum=0;
		pfx.clear();
		pfx.push_back(make_pair(0,0ll));
		for(int i=0;i<(int)pages.size();i++)
		{
			nowsum=(nowsum+pages[i].second)%MOD;
			pfx.push_back(make_pair(pages[i].first,nowsum));
		}
	}
	long long get_probability(int x)
	{
		vector<pair<int,long long>>::iterator it=upper_bound(pfx.begin(),pfx.end(),make_pair(x,(long long)0x3fffffffffff));
		it--;
		return it->second;
	}
}a[MAXN+5];
int main()
{
	freopen("library.in","r",stdin);
	#ifndef debug
	freopen("library.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i].read_book();
	}
	scanf("%d",&m);
	for(int qid=1;qid<=m;qid++)
	{
		int op;
		scanf("%d",&op);
		if(op==2)
		{
			int x;
			scanf("%d",&x);
			a[x].read_book();
		}
		else
		{
			int l,r,v;
			scanf("%d%d%d",&l,&r,&v);
			long long res=1;
			for(int i=l;i<=r;i++)
			{
				res=res*a[i].get_probability(v)%MOD;
			}
			printf("%lld\n",(long long)res);
		}
	}
	return 0; 
}
