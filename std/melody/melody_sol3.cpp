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
	long long sumc1=0,sumc2=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
		sumc1+=c[i];
		sumc2+=c[i]*(n-i);
		sumc1%=MOD;
		sumc2%=MOD;
	}
	while(m--)
	{
		a=(a+(b*n%MOD)+sumc2)%MOD;
		b=(b+sumc1)%MOD;
	}
	printf("%lld",a);
	return 0;
}

