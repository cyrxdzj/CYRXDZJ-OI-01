import random
import math
import os
seed=[15326548,132312,235697,2035689,1235684]
def swap(x,y):
    return [y,x]
def gen(subid,ptid,target=""):
    #print("Gen sub %2d pt %2d"%(subid,ptid))
    n=0
    m=0
    op=[]
    random.seed(seed[ptid%len(seed)])
    if subid==1:
        n=random.randint(6,10)
        m=random.randint(3,5)
        for i in range(m):
            if ptid%4==0:
                x=random.randint(1,n-1)
                y=random.randint(x+1,n)
            else:
                x=random.randint(1,n)
                y=random.randint(1,n)
            if random.randint(0,ptid%2)==1:
                x,y=swap(x,y)
            op.append([x,y])
    elif subid==2:
        if ptid!=10:
            n=random.randint(10000,100000)
            m=random.randint(n//4,n//2)
        else:
            n=100000
            m=50000
        nxtm=[]
        for i in range(1,n+1):
            nxtm.append(i)
        random.shuffle(nxtm)
        for i in range(m):
            op.append([nxtm[0],nxtm[1]])
            del(nxtm[0])
            del(nxtm[0])
    elif subid==3:
        n=random.randint(10000*ptid,100000)
        m=n-1
        nxtm=[]
        for i in range(1,n+1):
            nxtm.append(i)
        random.shuffle(nxtm)
        for i in range(1,n):
            op.append([nxtm[random.randint(0,i-1)],nxtm[i]])
    elif subid==4:
        n=random.randint(100*ptid,1000)
        m=random.randint(300*ptid,3000)
        bcnt=random.randint(1,n//100)
        bsz=math.ceil(n/bcnt)
        nxtm=[]
        for i in range(1,n+1):
            nxtm.append(i)
        random.shuffle(nxtm)
        for i in range(m):
            bid=random.randint(1,bcnt)
            if ptid%5==0:
                x=nxtm[random.randint(0,n-1)]
                y=nxtm[random.randint(0,n-1)]
            else:
                l=(bid-1)*bsz
                r=min(n-1,bid*bsz-1)
                xi=random.randint(l,r-1)
                yi=random.randint(xi+1,r)
                x=nxtm[xi]
                y=nxtm[yi]
            op.append([x,y])
    elif subid==5:
        n=random.randint(10000*ptid,100000)
        m=random.randint(30000*ptid,300000)
        bcnt=random.randint(1,n//1000)
        bsz=math.ceil(n/bcnt)
        nxtm=[]
        for i in range(1,n+1):
            nxtm.append(i)
        random.shuffle(nxtm)
        for i in range(m):
            bid=random.randint(1,bcnt)
            if ptid%5==0:
                x=nxtm[random.randint(0,n-1)]
                y=nxtm[random.randint(0,n-1)]
            else:
                l=(bid-1)*bsz
                r=min(n-1,bid*bsz-1)
                xi=random.randint(l,r-1)
                yi=random.randint(xi+1,r)
                x=nxtm[xi]
                y=nxtm[yi]
            op.append([x,y])
    with open("data/permutation_sub%02d_pt%02d.in"%(subid,ptid),"w") as fobj:
        fobj.write("%d %d\n"%(n,m))
        for i in range(m):
            fobj.write("%d %d\n"%(op[i][0],op[i][1]))
    if target!="":
        with open("permutation.in","w") as fobj:
            fobj.write(open("data/permutation_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
        os.system(target)
        with open("data/permutation_sub%02d_pt%02d.ans"%(subid,ptid),"w") as fobj:
            fobj.write(open("permutation.out").read())
for i in range(1,10+1):
    gen(1,i,"permutation_sol5.exe")
    #pass
for i in range(1,10+1):
    gen(2,i,"permutation_sol5.exe")
    #pass
for i in range(1,10+1):
    gen(3,i,"permutation_sol5.exe")
    #pass
for i in range(1,10+1):
    gen(4,i,"permutation_sol5.exe")
    #pass
for i in range(1,10+1):
    gen(5,i,"permutation_sol5.exe")
    #pass
