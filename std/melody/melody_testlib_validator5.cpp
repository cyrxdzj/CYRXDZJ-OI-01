#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n=inf.readInt(1,4e5,"n");
	inf.readSpace();
	long long m=inf.readLong(1ll,(long long)1e12,"m");
	inf.readSpace();
	long long x;
	x=inf.readLong(0ll,(long long)1e9,"a");
	inf.readSpace();
	x=inf.readLong(0ll,(long long)1e9,"b");
	inf.readEoln();
	for(int i=1;i<=n;i++)
	{
		x=inf.readLong(0ll,(long long)1e9,string("c_")+to_string(i));
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
