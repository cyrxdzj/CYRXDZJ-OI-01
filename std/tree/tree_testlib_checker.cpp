#include "testlib.h"

using namespace std;

const int MAXN=1e5;
int n,m,csum;
void check_input()
{
	n=inf.readInt(1,MAXN);
	for(int i=1;i<n;i++)
	{
		int u=inf.readInt(1,n),v=inf.readInt(1,n);
		if(u==v)
		{
			quitf(_fail,"edge %d u==v %d",i,u);
		}
	}
	for(int i=1;i<=n;i++)
	{
		int a=inf.readInt(1,1000000000);
	}
	for(int i=1;i<=n;i++)
	{
		int b=inf.readInt(0,64-1);
	}
	int c=inf.readInt(0,64-1);
}

int main(int argc, char *argv[]) {
    setName("compare ordered sequences of signed int%d numbers", 8 * int(sizeof(long long)));

    registerTestlibCmd(argc, argv);
    
    check_input();

    int n = 0;
    string firstElems;

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        long long j = ans.readLong();
        long long p = ouf.readLong();
        if (j != p)
            quitf(_wa, "%d%s numbers differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(),
                  vtos(j).c_str(), vtos(p).c_str());
        else if (n <= 5) {
            if (firstElems.length() > 0)
                firstElems += " ";
            firstElems += vtos(j);
        }
    }

    int extraInAnsCount = 0;

    while (!ans.seekEof()) {
        ans.readLong();
        extraInAnsCount++;
    }

    int extraInOufCount = 0;

    while (!ouf.seekEof()) {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements",
              n + extraInAnsCount, n);

    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements",
              n + extraInOufCount, n);

    if (n <= 5)
        quitf(_ok, "%d number(s): \"%s\"", n, compress(firstElems).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
