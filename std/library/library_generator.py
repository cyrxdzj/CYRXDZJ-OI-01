import random
import math
import os
seed=[15326548,132312,235697,2035689,1235684]
MOD=998244353
def qpow(a,b):
    res=1
    while b:
        if b&1:
            res=res*a%MOD
        a=a*a%MOD
        b>>=1
    return res
def prob(numerator,deno):
    return numerator*qpow(deno,MOD-2)%MOD
class Book:
    c=0
    d=[]
    p=[]
    def __init__(self):
        self.c=0
        self.d=self.p=[]
    def gen(self,cnt:int,difficulty_repeat:bool,difficulty_min:int,difficulty_max:int):
        rest_p=100000
        deno=100000
        self.c=cnt
        self.d=[]
        self.p=[]
        self.d.append(difficulty_min)
        try:
            if difficulty_repeat:
                for i in range(1,cnt):
                    self.d.append(random.randint(difficulty_min,difficulty_max))
                for i in range(2):
                    x=random.randint(0,cnt-1)
                    y=random.randint(0,cnt-1)
                    t=self.d[x]
                    self.d[x]=self.d[y]
                    self.d[y]=t
            else:
                for i in range(1,cnt):
                    left=self.d[i-1]+1
                    right=difficulty_min+((difficulty_max-difficulty_min)*(i+1)//cnt)
                    #print(i+1,cnt,difficulty_min,difficulty_max,left,right)
                    self.d.append(random.randint(left,right))
                for i in range(max(1,cnt//5)):
                    x=random.randint(0,cnt-1)
                    y=random.randint(0,cnt-1)
                    t=self.d[x]
                    self.d[x]=self.d[y]
                    self.d[y]=t
        except Exception as e:
            print(self.d)
            raise e
        for i in range(1,cnt+1):
            if i==cnt:
                now_p=rest_p
            else:
                now_p=random.randint(1,rest_p-(cnt-i))
            self.p.append(prob(now_p,deno))
            rest_p-=now_p
        #print(cnt,self.d,self.p)
    def write(self,fobj):
        try:
            assert self.c==len(self.d)
            assert self.c==len(self.p)
        except Exception as e:
            print(self.c,len(self.d),len(self.p),self.d,self.p)
            raise e
        fobj.write("%d\n"%self.c)
        for i in range(self.c):
            fobj.write("%d"%self.d[i])
            if i!=self.c-1:
                fobj.write(" ")
            else:
                fobj.write("\n")
        for i in range(self.c):
            fobj.write("%d"%self.p[i])
            if i!=self.c-1:
                fobj.write(" ")
            else:
                fobj.write("\n")
def gen_array(n,sum):
    if (n>sum):
        raise Exception("It's impossible to gen such an array because the theoretical minimum value of its total sum is greater than the required total sum.")
    res=[]
    nowsum=0
    mx=sum//n
    for i in range(n):
        res.append(random.randint(max(mx//2,2 if n*2<=sum else 1),mx))
        nowsum+=res[i]
    t=n//3
    while nowsum<sum:
        pos=random.randint(0,n-1)
        addv=random.randint((sum-nowsum) if (t==1) else 1,sum-nowsum)
        res[pos]+=addv
        nowsum+=addv
    random.shuffle(res)
    return res
def gen(subid,ptid,target=""):
    print("Gen sub %2d pt %2d"%(subid,ptid))
    random.seed(seed[ptid%len(seed)])
    n=0
    m=0
    m1=0    #操作1总次数
    m2=0
    ops=[]  #操作编号
    C=0     #所有书本的页数总数
    difficulty_min=difficulty_max=0
    difficulty_repeat=False
    if (subid==1) and (ptid<=2) or ((subid==2) and (ptid==2)):
        n=random.randint(30,50)
        m=random.randint(80,100)
    elif (subid==1) and (ptid==3):
        n=50
        m=100
    elif ((subid==1) and (4<=ptid and ptid<=25)) or ((subid==2) and (3<=ptid and ptid<=5)):
        n=random.randint(20000+(ptid%2)*30000,50000)
        m=random.randint(15000+(ptid%2)*5000, 20000)
    elif ((subid==2) and (ptid==1)):
        n=3
        m=6
    if ((subid==1) and (4<=ptid and ptid<=9)) or((subid==2) and (2<=ptid and ptid<=3)):
        m1=m
    elif (subid==2 and ptid==1):
        m1=5
        m2=1
    else:
        m1=random.randint(1,m//1.5)
    m2=m-m1
    if not (subid==2 and ptid==1):
        for i in range(m1):
            ops.append(1)
        for i in range(m2):
            ops.append(2)
        random.shuffle(ops)
    else:
        ops=[1,1,1,2,1,1]
    if ((subid==1) and (ptid<=3)):
        C=random.randint(100*ptid,300)
    elif ((subid==1) and (4<=ptid and ptid<=9)) or (subid==2 and (2<=ptid and ptid<=3)):
        C=random.randint(50000*((ptid%2)+1),100000)
    elif ((subid==1) and (10<=ptid<=11)):
        C=n+m2
    elif ((subid==1) and (12<=ptid and ptid<=25)) or (subid==2 and (4<=ptid and ptid<=5)):
        C=random.randint(100000*((ptid%2)+1),300000)
    elif (subid==2 and ptid==1):
        m1=5
        m2=1
    if ((subid==1) and (ptid<=3)) or ((subid==2) and (ptid<=2)):
        difficulty_max=10
    elif ((subid==1) and ((6<=ptid and ptid<=7) or (14<=ptid and ptid<=17))):
        difficulty_max=int(1e5)
    else:
        difficulty_max=int(1e9)
    if ((subid==1) and (ptid in ([5,7,9]+list(range(15,17+1))+list(range(19,25+1))))):
        difficulty_min=difficulty_max//random.randint(2,100)
    else:
        difficulty_min=1
    if ((subid==1) and (ptid in ([9]+list(range(16,17+1))+list(range(19,25+1))))):
        difficulty_repeat=True
    if not (subid==2 and ptid==1):
        cs=gen_array(n+m2,C)
        for i in range(n+m2):
            if cs[i]>difficulty_max:
                C-=cs[i]
                cs[i]=difficulty_max
                C+=cs[i]
        #print(n,m2,len(cs))
    #print("Gen array done")
    print("    n %d m %d difficulty_min %d difficulty_max %d difficulty_repeat %d"%(n,m,difficulty_min,difficulty_max,difficulty_repeat))
    books=[]
    l=[]
    r=[]
    v=[]
    x=[]
    change_books=[]
        #print(cs[0],books[0].d,books[0].p)
    if (subid==2 and ptid==1):
        l.append(1),r.append(2),v.append(3)
        l.append(1),r.append(3),v.append(4)
        l.append(1),r.append(3),v.append(7)
        x.append(2)
        l.append(1),r.append(2),v.append(3)
        l.append(2),r.append(3),v.append(5)
        books=[Book(),Book(),Book()]
        books[0].c=3
        books[0].d=[1,3,5]
        books[0].p=[prob(1,5),prob(2,5),prob(2,5)]
        books[1].c=3
        books[1].d=[2,3,6]
        books[1].p=[prob(1,4),prob(3,8),prob(3,8)]
        books[2].c=2
        books[2].d=[5,7]
        books[2].p=[prob(2,3),prob(1,3)]
        change_books=[Book()]
        change_books[0].c=3
        change_books[0].d=[1,2,4]
        change_books[0].p=[prob(1,9),prob(5,9),prob(3,9)]
    else:
        for i in range(n):
            book=Book()
            if (i+1)%10000==0:
                print("    book %d cs %d"%(i+1,cs[0]))
            book.gen(cs[0],difficulty_repeat,difficulty_min,difficulty_max)
            del(cs[0])
            books.append(book)
        for i in range(m1):
            l.append(random.randint(1,max(1,n*(i+1)//m1)))
            r.append(random.randint(max(l[i],n-n*(i+1)//m1),n))
            v.append(random.randint(difficulty_min,difficulty_max))
        for i in range(m2):
            x.append(random.randint(1,n))
            book=Book()
            book.gen(cs[0],difficulty_repeat,difficulty_min,difficulty_max)
            del(cs[0])
            change_books.append(book)
        assert len(cs)==0
    #print(books[0].d,books[0].p)
    with open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"w") as fobj:
        fobj.write("%d\n"%n)
        for i in range(n):
            books[i].write(fobj)
        fobj.write("%d\n"%m)
        for i in range(m):
            if ops[i]==1:
                fobj.write("1 %d %d %d\n"%(l[0],r[0],v[0]))
                del(l[0])
                del(r[0])
                del(v[0])
            elif ops[i]==2:
                fobj.write("2 %d\n"%(x[0]))
                change_books[0].write(fobj)
                del x[0]
                del change_books[0]
    assert len(l)==0
    assert len(r)==0
    assert len(v)==0
    assert len(x)==0
    assert len(change_books)==0
    if target!="":
        with open("library.in","w") as fobj:
            fobj.write(open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
        os.system(target)
        with open("data/library_sub%02d_pt%02d.ans"%(subid,ptid),"w") as fobj:
            fobj.write(open("library.out").read())

for i in range(1,3+1):
    gen(1,i,"library_sol1.exe")
    #pass
for i in range(4,25+1):
    gen(1,i)
    #pass
for i in range(1,2+1):
    gen(2,i,"library_sol1.exe")
    #pass
for i in range(3,5+1):
    gen(2,i)
    #pass