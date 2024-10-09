import os
import sys
import time
validated=[]
def validate(subid,ptid,target,add=True):
    print("Validate sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    res=os.system("%s < data/tree_sub%02d_pt%02d.in"%(target,subid,ptid))
    if res==0:
        if add:
            validated.append((subid,ptid))
        print("\033[1;32mok\033[0m")
def check(subid,ptid,target):
    print("Check sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    if not (subid,ptid) in validated:
        print("\033[1;31mValidation not passed.\033[0m")
        sys.stdout.flush()
        return
    with open("tree.in","w") as fobj:
        fobj.write(open("data/tree_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("tree_testlib_checker.exe tree.in tree.out data/tree_sub%02d_pt%02d.ans"%(subid,ptid))
for subid in range(1,5+1):
    for i in range(1,[None,3,6,6,7,7][subid]+1):
        validate(subid,i,"tree_testlib_validator{subid}.exe".format(subid=subid))
        if subid<5:
            validate(subid,i,"tree_testlib_validator{subid}.exe".format(subid=5),False)
for i in range(1,3+1):
    check(1,i,"tree_sol1.exe")
for i in range(1,3+1):
    check(1,i,"tree_sol2.exe")
for i in range(1,6+1):
    check(2,i,"tree_sol2.exe")
    check(2,i,"tree_sol5.exe")
check(4,7,"tree_sol2.exe")
check(4,7,"tree_sol5.exe")
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
for i in range(1,3+1):
    check(1,i,"tree_sol6.exe")
for i in range(1,6+1):
    check(2,i,"tree_sol6.exe")
for i in range(1,6+1):
    check(3,i,"tree_sol6.exe")
for i in range(1,7+1):
    check(4,i,"tree_sol6.exe")
for i in range(1,7+1):
    check(5,i,"tree_sol6.exe")
