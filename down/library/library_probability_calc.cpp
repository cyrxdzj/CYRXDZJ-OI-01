#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD=998244353;
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
int main()
{
	while(true)
	{
		long long a,b;
		printf("the A of A/B > ");
		fflush(stdout);
		scanf("%lld",&a);
		printf("the B of A/B > ");
		fflush(stdout);
		scanf("%lld",&b);
		printf("Probability is %lld\n",a*qpow(b,MOD-2)%MOD);
	}
	return 0;
}

