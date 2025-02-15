#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=4e5;
const long long MOD=998244353;
int n;
long long m;
long long c[MAXN+5];
long long a,b;
long long qpow(long long a,long long b)//快速幂，用于求 2 的逆元 
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
const long long INV2=qpow(2,MOD-2);
int main()
{
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	scanf("%d%lld%lld%lld",&n,&m,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
	}
	m%=MOD;//加法和乘法中随便取模 
	a=(a+(b*n%MOD*m%MOD))%MOD;
	for(int i=1;i<=n;i++)
	{
		long long st=n-i,ed=n*m-i;//等差数列首项与末项 
		st%=MOD;
		ed%=MOD;
		a=(a+(c[i]*(((st+ed)%MOD*((long long)m)%MOD*INV2%MOD))%MOD))%MOD;
	}
	printf("%lld",a);
	return 0;
}

