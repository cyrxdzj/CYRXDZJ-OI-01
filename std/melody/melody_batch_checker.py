import os
import sys
import time
validated=[]
def validate(subid,ptid,target):
    print("Validate sub %2d pt %2d with %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    res=os.system("%s < data/melody_sub%02d_pt%02d.in"%(target,subid,ptid))
    if res==0:
        validated.append((subid,ptid))
        print("\033[1;32mok\033[0m")
    sys.stdout.flush()
def check(subid,ptid,target):
    if not (subid,ptid) in validated:
        return
    print("Check sub %2d pt %2d with %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    with open("melody.in","w") as fobj:
        fobj.write(open("data/melody_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("melody_testlib_checker.exe melody.in melody.out data/melody_sub%02d_pt%02d.ans"%(subid,ptid))
'''
for ptid in range(1,5+1):
    validate(3,ptid,"melody_testlib_validator1.exe")
'''
for subid in range(1,5+1):
    for ptid in range(1,5+1):
        validate(subid,ptid,"melody_testlib_validator{subid}.exe".format(subid=subid))
        if subid<5:
            validate(subid,ptid,"melody_testlib_validator5.exe")
for i in range(1,5+1):
    check(1,i,"melody_sol1.exe")
for i in range(1,5+1):
    check(2,i,"melody_sol1.exe")
for i in range(1,5+1):
    check(3,i,"melody_sol2.exe")
for bid in range(1,4+1):
    for i in range(1,5+1):
        check(bid,i,"melody_sol3.exe")
for bid in range(1,5+1):
    for i in range(1,5+1):
        check(bid,i,"melody_sol4.exe")
for bid in range(1,5+1):
    for i in range(1,5+1):
        check(bid,i,"melody_sol5.exe")
