#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=4e5;
const long long MOD=998244353;
int n,m;
long long c[MAXN+5];
long long a,b;
int main()
{
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	scanf("%d%d%lld%lld",&n,&m,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
	}
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			a=(a+b)%MOD;
			b=(b+c[i])%MOD;
		}
	}
	printf("%lld",a);
	return 0;
}
