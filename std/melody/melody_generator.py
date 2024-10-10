import random
import math
import os
import shutil
seed=[15326548,132312,235697,2035689,1235684]
def swap(x,y):
    return [y,x]
def gen(subid,ptid,target=""):
    print("Gen sub %2d pt %2d"%(subid,ptid))
    random.seed(seed[ptid%len(seed)])
    n=0
    m=0
    a=random.randint(0,int((1e9)//4*(ptid-1)))
    b=random.randint(0,int((1e9)//4*(ptid-1)))
    c=[]
    if subid==1:
        if ptid>=3:
            n=1000//5*ptid
            m=random.randint(n,1000)
        else:
            n=3*ptid
            m=2*ptid
        for i in range(n):
            c.append(random.randint(1,100))
    elif subid==2:
        n=random.randint(80000*ptid,400000)
        m=1
        for i in range(n):
            c.append(random.randint(1,100))
    elif subid==3:
        n=random.randint(80000*ptid,400000)
        m=random.randint(20000*ptid,100000)
        for i in range(n):
            c.append(1+(ptid-1)*13)
    elif subid==4:
        n=random.randint(80000*ptid,400000)
        m=random.randint(20000*ptid,100000)
    elif subid==5:
        n=random.randint(80000*ptid,400000)
        m=random.randint(200000000000*ptid,1000000000000)
    if subid>=4:
        for i in range(n):
            c.append(random.randint(1,1000000000))
    with open("data/melody_sub%02d_pt%02d.in"%(subid,ptid),"w") as fobj:
        fobj.write("%d %d %d %d\n"%(n,m,a,b))
        for i in range(n):
            fobj.write("%d"%(c[i]))
            if i<n-1:
                fobj.write(" ")
    if target!="":
        with open("melody.in","w") as fobj:
            fobj.write(open("data/melody_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
        os.system(target)
        with open("data/melody_sub%02d_pt%02d.ans"%(subid,ptid),"w") as fobj:
            fobj.write(open("melody.out").read())
    
for i in range(1,5+1):
    gen(1,i,"melody_sol4.exe")
    #pass
shutil.copy2("data/melody_sub01_pt01.in","../../down/melody/melody1.in")
shutil.copy2("data/melody_sub01_pt01.ans","../../down/melody/melody1.ans")
shutil.copy2("data/melody_sub01_pt05.in","../../down/melody/melody2.in")
shutil.copy2("data/melody_sub01_pt05.ans","../../down/melody/melody2.ans")
for i in range(1,5+1):
    gen(2,i,"melody_sol4.exe")
    #pass
for i in range(1,5+1):
    gen(3,i,"melody_sol4.exe")
    #pass
shutil.copy2("data/melody_sub03_pt01.in","../../down/melody/melody3.in")
shutil.copy2("data/melody_sub03_pt01.ans","../../down/melody/melody3.ans")
for i in range(1,5+1):
    gen(4,i,"melody_sol4.exe")
    #pass
for i in range(1,5+1):
    gen(5,i,"melody_sol4.exe")
    #pass
shutil.copy2("data/melody_sub05_pt03.in","../../down/melody/melody4.in")
shutil.copy2("data/melody_sub05_pt03.ans","../../down/melody/melody4.ans")
