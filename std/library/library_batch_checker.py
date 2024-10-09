import os
import sys
import time
validated=[]
def validate(subid,ptid,target,add=True):
    print("Validate sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    res=os.system("%s < data/library_sub%02d_pt%02d.in"%(target,subid,ptid))
    if res==0:
        if add:
            validated.append((subid,ptid))
        print("\033[1;32mok\033[0m")
    sys.stdout.flush()
def check(subid,ptid,target):
    print("Check sub %2d pt %2d with target %s"%(subid,ptid,target),end=' ')
    sys.stdout.flush()
    if not (subid,ptid) in validated:
        print("\033[1;31mValidation not passed.\033[0m")
        sys.stdout.flush()
        return
    with open("library.in","w") as fobj:
        fobj.write(open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    st=time.time()
    os.system(target)
    ed=time.time()
    print("%4dms"%(int(round((ed-st)*1000,0))),end=' ')
    sys.stdout.flush()
    os.system("library_testlib_checker.exe library.in library.out data/library_sub%02d_pt%02d.ans"%(subid,ptid))

for i in range(1,25+1):
    valid=0
    if i<=3:
        valid=1
    elif i<=5:
        valid=2
    elif i<=7:
        valid=3
    elif i<=9:
        valid=4
    elif i<=11:
        valid=5
    elif i<=13:
        valid=6
    elif i<=17:
        valid=7
    elif i<=25:
        valid=8
    validate(1,i,"library_testlib_validator{valid}.exe".format(valid=valid))
    if valid<8:
        validate(1,i,"library_testlib_validator{valid}.exe".format(valid=8),False)
for i in range(1,5+1):
    valid=[None,1,1,4,7,8][i]
    validate(2,i,"library_testlib_validator{valid}.exe".format(valid=valid))
    if valid<8:
        validate(2,i,"library_testlib_validator{valid}.exe".format(valid=8),False)
for i in range(1,3+1):
    check(1,i,"library_sol1.exe")
    pass
for i in range(4,9+1):
    check(1,i,"library_sol2.exe")
    #pass
for i in range(1,25+1):
    check(1,i,"library_sol3.exe")
    check(1,i,"library_sol5.exe")
    #pass
for i in range(1,2+1):
    check(2,i,"library_sol1.exe")
for i in range(3,3+1):
    check(2,i,"library_sol2.exe")
for i in range(1,5+1):
    check(2,i,"library_sol3.exe")
    check(2,i,"library_sol5.exe")
for i in range(1,25+1):
    #check(1,i,"library_sol4.exe")
    pass
for i in range(1,5+1):
    #check(2,i,"library_sol4.exe")
    pass
