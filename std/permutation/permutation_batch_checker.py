import os
import sys
import time
def check(subid,ptid,target):
    print("Check sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    with open("permutation.in","w") as fobj:
        fobj.write(open("data/permutation_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("permutation_testlib_checker.exe permutation.in permutation.out data/permutation_sub%02d_pt%02d.ans"%(subid,ptid))
for i in range(1,11):
    check(1,i,"permutation_sol1.exe")
for i in range(1,11):
    check(2,i,"permutation_sol2.exe")
for i in range(1,11):
    check(3,i,"permutation_sol3.exe")
for bid in range(1,5+1):
    for i in range(1,11):
        check(bid,i,"permutation_sol4.exe")
for bid in range(1,5+1):
    for i in range(1,11):
        check(bid,i,"permutation_sol5.exe")
