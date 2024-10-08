#include "testlib.h"
#include<algorithm>
using namespace std;
int data[100005],dcnt;
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n=inf.readInt(1,1e5,"n");
	inf.readSpace();
	int m=inf.readInt(1,5e4,"m");
	inf.readEoln();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=inf.readInt(1,n);
		inf.readSpace();
		y=inf.readInt(1,n);
		inf.readEoln();
		data[++dcnt]=x;
		data[++dcnt]=y;
	}
	inf.readEof();
	sort(data+1,data+1+dcnt);
	dcnt=unique(data+1,data+1+dcnt)-data-1;
	quitif(dcnt!=2*m,_fail,"x y repeated");
}
