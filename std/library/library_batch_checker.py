import os
import sys
import time
def check(subid,ptid,target):
    print("Check sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    with open("library.in","w") as fobj:
        fobj.write(open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("library_testlib_checker.exe library.in library.out data/library_sub%02d_pt%02d.ans"%(subid,ptid))
for i in range(1,3+1):
    #check(1,i,"library_sol1.exe")
    pass
for i in range(4,9+1):
    #check(1,i,"library_sol2.exe")
    pass
for i in range(1,25+1):
    check(1,i,"library_sol3.exe")
    check(1,i,"library_sol5.exe")
    pass
for i in range(1,2+1):
    check(2,i,"library_sol1.exe")
for i in range(3,3+1):
    check(2,i,"library_sol2.exe")
for i in range(1,5+1):
    check(2,i,"library_sol3.exe")
    check(2,i,"library_sol5.exe")