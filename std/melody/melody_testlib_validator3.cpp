#include "testlib.h"
#include<string>
#include<cstdio>
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n=inf.readInt(1,4e5,"n");
	inf.readSpace();
	long long m=inf.readLong(1ll,(long long)1e5,"m");
	inf.readSpace();
	long long x;
	x=inf.readLong(0ll,(long long)1e9,"a");
	inf.readSpace();
	x=inf.readLong(0ll,(long long)1e9,"b");
	inf.readEoln();
	long long c=0;
	for(int i=1;i<=n;i++)
	{
		x=inf.readLong(0ll,(long long)1e9,string("c_")+to_string(i));
		if(i==1)
		{
			c=x;
		}
		else if(c!=x)
		{
			quitf(_fail,"c_%d value %s is not equal to %s",i,vtos(x).c_str(),vtos(c).c_str());
		}
		if(i<n)
		{
			inf.readSpace();
		}
		else
		{
			inf.readEof();
		}
	}
}
