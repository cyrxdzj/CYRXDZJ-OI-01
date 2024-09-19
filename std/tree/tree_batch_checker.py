import os
import sys
import time
def check(subid,ptid,target):
    print("Check sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    with open("tree.in","w") as fobj:
        fobj.write(open("data/tree_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("tree_testlib_checker.exe tree.in tree.out data/tree_sub%02d_pt%02d.ans"%(subid,ptid))
for i in range(1,3+1):
    check(1,i,"tree_sol1.exe")
for i in range(1,3+1):
    check(1,i,"tree_sol2.exe")
for i in range(1,6+1):
    check(2,i,"tree_sol2.exe")
check(4,7,"tree_sol2.exe")
for i in range(1,6+1):
    check(3,i,"tree_sol3.exe")
check(4,7,"tree_sol3.exe")
for i in range(1,3+1):
    check(1,i,"tree_sol4.exe")
for i in range(1,6+1):
    check(2,i,"tree_sol4.exe")
for i in range(1,6+1):
    check(3,i,"tree_sol4.exe")
for i in range(1,7+1):
    check(4,i,"tree_sol4.exe")
for i in range(1,7+1):
    check(5,i,"tree_sol4.exe")
