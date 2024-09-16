#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
//#define debug
const int MAXN=50;
const long long MOD=998244353;
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
int main()
{
	freopen("library.in","r",stdin);
	freopen("library.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i].read_book();
	}
	scanf("%d",&m);
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int l,r;
			int v;
			scanf("%d%d%d",&l,&r,&v);
			long long ans=1;
			for(int i=l;i<=r;i++)
			{
				long long nowsum=0;
				for(pair<int,long long>page:a[i].pages)
				{
					if(v>=page.first)
					{
						nowsum=(nowsum+page.second)%MOD;
					}
					else
					{
						break;
					}
				}
				ans=(ans*nowsum)%MOD;
			}
			printf("%lld\n",ans);
		}
		else
		{
			int x;
			scanf("%d",&x);
			a[x].read_book();
		}
	}
	return 0;
}

