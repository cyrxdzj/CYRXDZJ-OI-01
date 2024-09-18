#include "testlib.h"

using namespace std;

const int MAXN=5e4,MAXC=4e5;
int n,m,csum;
void check_input()
{
	n=inf.readInt(1,MAXN);
	for(int i=1;i<=n;i++)
	{
		int c=inf.readInt(1,MAXC);
		csum+=c;
		if(csum>MAXC)
		{
			quitf(_fail,"C > %d",MAXC);
		}
		for(int j=1;j<=c;j++)
		{
			int d=inf.readInt(1,1e9);
		}
		for(int j=1;j<=c;j++)
		{
			int p=inf.readInt(1,998244353-1);
		}
	}
	m=inf.readInt(1,MAXN);
	while(m--)
	{
		int op=inf.readInt(1,2);
		if(op==1)
		{
			int l,r,v;
			l=inf.readInt(1,n);
			r=inf.readInt(l,n);
			v=inf.readInt(1,1e9);
		}
		else
		{
			int x=inf.readInt(1,n);
			int c=inf.readInt(1,MAXC);
			csum+=c;
			if(csum>MAXC)
			{
				quitf(_fail,"C > %d",MAXC);
			}
			for(int j=1;j<=c;j++)
			{
				int d=inf.readInt(1,1e9);
			}
			for(int j=1;j<=c;j++)
			{
				int p=inf.readInt(1,998244353-1);
			}
		}
	}
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
