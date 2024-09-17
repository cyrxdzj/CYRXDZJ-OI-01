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
    min_d=10000000000
    def __init__(self):
        self.c=0
        self.d=self.p=[]
    def gen(self,cnt:int,difficulty_repeat:bool,difficulty_min:int,difficulty_max:int):
        rest_p=max(1000000,cnt)
        deno=rest_p
        self.c=cnt
        self.d=[]
        self.p=[]
        if difficulty_min>0:
            self.d.append(difficulty_min)
        elif not difficulty_repeat:
            self.d.append(random.randint(1,difficulty_max-cnt+1))
        else:
            self.d.append(random.randint(1,difficulty_max))
        try:
            if difficulty_repeat:
                for i in range(1,cnt):
                    self.d.append(random.randint(max(difficulty_min,1),difficulty_max))
                for i in range(10):
                    x=random.randint(0,cnt-1)
                    y=random.randint(0,cnt-1)
                    t=self.d[x]
                    self.d[x]=self.d[y]
                    self.d[y]=t
            else:
                if difficulty_max-self.d[0]+1<cnt:
                    #print("will out",cnt,difficulty_max,self.d[0])
                    self.c=cnt=difficulty_max-self.d[0]+1
                for i in range(1,cnt):
                    if difficulty_max-self.d[i-1]<=cnt-i:
                        left=right=self.d[i-1]+1
                    else:
                        left=self.d[i-1]+1
                        right=max(left,difficulty_min+((difficulty_max-difficulty_min)*(i+1)//cnt))
                    if right>difficulty_max:
                        print(left,right,cnt,i)
                        raise Exception("Out of limit")
                    #print(i+1,cnt,difficulty_min,difficulty_max,left,right)
                    self.d.append(random.randint(left,right))
                for i in range(max(1,cnt//5)):
                    x=random.randint(0,cnt-1)
                    y=random.randint(0,cnt-1)
                    t=self.d[x]
                    self.d[x]=self.d[y]
                    self.d[y]=t
            for i in range(0,cnt):
                self.min_d=min(self.min_d,self.d[i])
        except Exception as e:
            #print(self.d)
            raise e
        for i in range(1,cnt+1):
            if i==cnt:
                now_p=rest_p
            else:
                if 1>rest_p-(cnt-i):
                    print(rest_p,cnt,i)
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
    elif ((subid==1) and (4<=ptid and ptid<=9)) or ((subid==2) and (3<=ptid and ptid<=3)):
        n=50000
        m=30000
    elif ((subid==1) and (10<=ptid and ptid<=25)) or ((subid==2) and (4<=ptid and ptid<=5)):
        n=50000
        m=50000
    elif ((subid==2) and (ptid==1)):
        n=3
        m=6
    if ((subid==1) and (4<=ptid and ptid<=9)) or((subid==2) and (2<=ptid and ptid<=3)):
        m1=m
    elif (subid==2 and ptid==1):
        m1=5
        m2=1
    else:
        m1=random.randint(1,int(m//1.5))
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
    elif ((subid==2) and (ptid==2)):
        C=300
    elif ((subid==1) and (4<=ptid and ptid<=9)) or (subid==2 and (ptid==3)):
        C=n*2
    elif ((subid==1) and (10<=ptid<=11)):
        C=n+m2
    elif ((subid==1) and (12<=ptid and ptid<=25)) or (subid==2 and (4<=ptid and ptid<=5)):
        C=400000
    elif (subid==2 and ptid==1):
        m1=5
        m2=1
    if ((subid==1) and (ptid<=5)) or ((subid==2) and (ptid<=2)):
        difficulty_max=10
    elif ((subid==1) and ((6<=ptid and ptid<=7) or (14<=ptid and ptid<=17))):
        difficulty_max=int(1e5)
    else:
        difficulty_max=int(1e9)
    if ((subid==1) and (ptid in ([7,9]+list(range(15,17+1))+list(range(19,25+1))))) or ((subid==2) and (ptid in [2,4,5])):
        difficulty_min=0
    else:
        difficulty_min=1
    if ((subid==1) and (ptid in ([9]+list(range(16,17+1))+list(range(19,25+1))))):
        difficulty_repeat=True
    if (subid==2 and ptid==1):
        pass
    elif (subid==1 and (4<=ptid and ptid<=9)) or (subid==2 and ptid==3):
        cs=[]
        for i in range(n):
            cs.append(2)
    elif (subid==1 and (12<=ptid and ptid<=13)):
        mx_pt=random.randint(1,n)
        cs=[]
        for i in range(1,n+m2+1):
            if i==mx_pt:
                cs.append(C-n-m2+1)
            else:
                cs.append(1)
    else:
        cs=gen_array(n+m2,C)
        for i in range(n+m2):
            if cs[i]>difficulty_max-max(difficulty_min,1)+1 and not difficulty_repeat:
                C-=cs[i]
                cs[i]=difficulty_max-max(difficulty_min,1)-difficulty_min+1
                C+=cs[i]
        #print(n,m2,len(cs))
    #print("Gen array done")
    print("    n %d m %d m1 %d m2 %d difficulty_min %d difficulty_max %d difficulty_repeat %d"%(n,m,m1,m2,difficulty_min,difficulty_max,difficulty_repeat))
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
        raw_book_min_d=difficulty_max+5
        changed_book_min_d=difficulty_max+5
        changed_book_min_d_id=0
        for i in range(n):
            book=Book()
            book.gen(cs[0],difficulty_repeat,int(difficulty_max//2.5) if difficulty_min==0 else difficulty_min,difficulty_max)
            raw_book_min_d=min(raw_book_min_d,book.min_d)
            if (i+1)%10000==0:
                print("    book %d cs %d min_d %d"%(i+1,cs[0],book.min_d))
            del(cs[0])
            books.append(book)
        for i in range(m1):
            if subid==1 and (12<=ptid and ptid<=13) and random.randint(1,3)<=2:
                l.append(mx_pt)
            else:
                l.append(random.randint(1,max(1,n*(i+1)//m1)))
            if subid==1 and (12<=ptid and ptid<=13):
                r.append(l[i])
            else:
                r.append(random.randint(max(l[i],n-n*(i+1)//m1),n))
            v.append(random.randint(max(difficulty_min,1),difficulty_max))
        for i in range(m2):
            x.append(random.randint(1,n))
            book=Book()
            book.gen(cs[0],difficulty_repeat,difficulty_min,raw_book_min_d if difficulty_min==0 else difficulty_max)
            del(cs[0])
            change_books.append(book)
        assert len(cs)==0
    #print(books[0].d,books[0].p)
    with open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"w") as fobj:
        fobj.write("%d\n"%n)
        for i in range(n):
            books[i].write(fobj)
        fobj.write("%d\n"%m)
        hack0_times=0
        for i in range(m):
            if ops[i]==1:
                if not(subid==2 and ptid==1):
                    if difficulty_min==0 and changed_book_min_d<raw_book_min_d and changed_book_min_d_id!=0 and (hack0_times<=5 or random.randint(1,20)==1):
                        l[0]=max(1,changed_book_min_d_id-n//100)
                        r[0]=min(n,changed_book_min_d_id+n//100)
                        v[0]=changed_book_min_d
                        hack0_times+=1
                        if hack0_times %100==0:
                            print("Hack 0 %d times"%hack0_times)
                fobj.write("1 %d %d %d\n"%(l[0],r[0],v[0]))
                del(l[0])
                del(r[0])
                del(v[0])
            elif ops[i]==2:
                fobj.write("2 %d\n"%(x[0]))
                change_books[0].write(fobj)
                if (not(subid==2 and ptid==1)):
                    if difficulty_min==0 and len(change_books)%10000==0:
                        print(change_books[0].min_d)
                    if changed_book_min_d>change_books[0].min_d:
                        changed_book_min_d=change_books[0].min_d
                        changed_book_min_d_id=x[0]
                del x[0]
                del change_books[0]
    assert len(l)==0
    assert len(r)==0
    assert len(v)==0
    assert len(x)==0
    assert len(change_books)==0
    if not (subid==2 and ptid==1):
        print("Raw book min d",raw_book_min_d,"Change book min_d",changed_book_min_d)
    if subid==2:
        with open("../../down/library/library%d.in"%ptid,"w") as fobj:
            fobj.write(open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
    if target!="":
        with open("library.in","w") as fobj:
            fobj.write(open("data/library_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
        os.system(target)
        with open("data/library_sub%02d_pt%02d.ans"%(subid,ptid),"w") as fobj:
            fobj.write(open("library.out").read())
        if subid==2:
            with open("../../down/library/library%d.ans"%ptid,"w") as fobj:
                fobj.write(open("data/library_sub%02d_pt%02d.ans"%(subid,ptid),"r").read())
#gen(1,4,"library_sol2.exe")
#exit(0)
for i in range(1,3+1):
    gen(1,i,"library_sol1.exe")
    pass
for i in range(4,9+1):
    gen(1,i,"library_sol2.exe")
    pass
for i in range(10,25+1):
    gen(1,i,"library_sol3.exe")
    pass
for i in range(1,2+1):
    gen(2,i,"library_sol1.exe")
    pass
for i in range(3,3+1):
    gen(2,i,"library_sol2.exe")
    pass
for i in range(4,5+1):
    gen(2,i,"library_sol3.exe")
    pass
