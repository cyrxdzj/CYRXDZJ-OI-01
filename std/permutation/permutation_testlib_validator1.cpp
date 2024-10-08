#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n=inf.readInt(1,10,"n");
	inf.readSpace();
	int m=inf.readInt(1,5,"m");
	inf.readEoln();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=inf.readInt(1,n);
		inf.readSpace();
		y=inf.readInt(1,n);
		inf.readEoln();
	}
	inf.readEof();
}
