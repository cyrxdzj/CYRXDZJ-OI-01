#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=4e5;
const long long MOD=998244353;
int n;
long long m;
long long c[MAXN+5];
long long a,b;
struct Matrix
{
	int r,c;
	long long data[3][3];
	Matrix()
	{
		r=c=0;
	}
	Matrix(int ir,int ic)
	{
		r=ir;
		c=ic;
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)
			{
				data[i][j]=0;
			}
		}
	}
}st,mc;
Matrix operator *(Matrix a,Matrix b)
{
	Matrix res(a.r,b.c);
	for(int i=0;i<a.r;i++)
	{
		for(int j=0;j<b.c;j++)
		{
			for(int k=0;k<a.c;k++)
			{
				res.data[i][j]=(res.data[i][j]+(a.data[i][k]*b.data[k][j]%MOD))%MOD;
			}
		}
	}
	return res;
}
Matrix qpow(Matrix a,long long b)
{
	Matrix res=Matrix(3,3);
	for(int i=0;i<3;i++)
	{
		res.data[i][i]=1;
	}
	while(b)
	{
		if(b&1)
		{
			res=res*a;
		}
		a=a*a;
		b>>=1;
	}
	return res;
}
int main()
{
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
	st=Matrix(1,3);
	st.data[0][2]=1;
	mc=Matrix(3,3);
	for(int i=0;i<3;i++)
	{
		mc.data[i][i]=1;
	}
	scanf("%d%lld%lld%lld",&n,&m,&st.data[0][0],&st.data[0][1]);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
		Matrix nowmc=Matrix(3,3);
		nowmc.data[0][0]=nowmc.data[1][0]=nowmc.data[1][1]=nowmc.data[2][2]=1;
		nowmc.data[2][1]=c[i];
		mc=mc*nowmc;
	}
	printf("%lld",(st*qpow(mc,m)).data[0][0]);
	return 0;
}

