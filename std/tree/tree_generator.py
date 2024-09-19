import random
import math
import os
import shutil
from cyaron import Graph,Edge,IO
seed=[15326548,132312,235697,2035689,1235684,23568983,24568953,125688945]
def gen(subid,ptid,target=""):
    print("Gen sub %2d pt %2d"%(subid,ptid))
    random.seed(seed[(subid*17+ptid)%len(seed)])
    n=0
    m=0
    tree=None
    tree_str=""
    if subid==1:
        if ptid==1:
            n=5
        else:
            n=200
    elif subid==2 or (subid==4 and ptid==7):
        n=random.randint(1100,1200)
    else:
        n=random.randint(90000,100000)
    if ptid==2 or subid==4:
        tree=Graph.chain(n)
    elif ptid==1:
        tree=Graph.tree(n)
    elif ptid==2:
        tree=Graph.chain(n)
    elif ptid==3:
        tree=Graph.binary_tree(n)
    elif ptid==4:
        tree=Graph.tree(n,0.2,0.6)
    elif ptid==5:
        tree=Graph.tree(n,0.4,0.4)
    elif ptid==6:
        tree=Graph.tree(n,0.6,0.2)
    tree_str=tree.to_str(output=Edge.unweighted_edge,shuffle=(not (subid==4 or ptid>=4)))
    '''if subid==2:
        print(tree_str)'''
    a=[]
    a_max=20 if (subid==1 and ptid==1) else 1000000000
    b_max=7 if (subid==1 and ptid==1) else 63
    for i in range(n):
        a.append(random.randint(1,a_max))
    b=[]
    c=random.randint(0,b_max)
    b.append(random.randint(0,b_max))
    for i in range(1,n):
        if subid==3 or (subid==4 and ptid==7):
            b.append(b[0])
        else:
            b.append(random.randint(0,b_max))
            '''
    io=IO("data/tree_sub%02d_pt%02d.in"%(subid,ptid),disable_output=True)
    io.input_writeln(n)
    io.input_writeln(tree_str)
    io.input_writeln(a)
    io.input_writeln(b)
    io.input_write(c)
    '''
    with open("data/tree_sub%02d_pt%02d.in"%(subid,ptid),"w") as fobj:
        fobj.write("%d\n"%n)
        fobj.write(tree_str+"\n")
        for i in range(n):
            fobj.write("%d"%a[i])
            if i<n-1:
                fobj.write(" ")
            else:
                fobj.write("\n")
        for i in range(n):
            fobj.write("%d"%b[i])
            if i<n-1:
                fobj.write(" ")
            else:
                fobj.write("\n")
        fobj.write("%d"%c)
    if target!="":
        with open("tree.in","w") as fobj:
            fobj.write(open("data/tree_sub%02d_pt%02d.in"%(subid,ptid),"r").read())
        os.system(target)
        with open("data/tree_sub%02d_pt%02d.ans"%(subid,ptid),"w") as fobj:
            fobj.write(open("tree.out").read())
for i in range(1,3+1):
    gen(1,i,"tree_sol1.exe")
    #pass
shutil.copy("data/tree_sub01_pt01.in","../../down/tree/tree1.in")
shutil.copy("data/tree_sub01_pt01.ans","../../down/tree/tree1.ans")
for i in range(1,6+1):
    gen(2,i,"tree_sol2.exe")
    #pass
for i in range(1,6+1):
    gen(3,i,"tree_sol3.exe")
    #pass

for i in range(1,7+1):
    gen(4,i,"")
    pass
shutil.copy("data/tree_sub04_pt07.in","../../down/tree/tree2.in")
#shutil.copy("data/tree_sub04_pt07.ans","../../down/tree/tree2.ans")
for i in range(1,6+1):
    #gen(5,i,"")
    pass
shutil.copy("data/tree_sub05_pt06.in","../../down/tree/tree3.in")
