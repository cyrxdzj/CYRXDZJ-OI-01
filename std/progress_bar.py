import sys
import time
hint_len=30
progress_len=50
class ProgressBarException(Exception):
    pass
def get_bitlen(x,base=10):
    if x<0:
        raise ProgressBarException
    if base<2:
        raise ProgressBarException
    if x==0:
        return 1
    res=0
    while x>0:
        x/=base
        res+=1
    return res
last_res_len=0
def show(hint:str,already:int,total:int,ending:str=""):
    global last_res_len
    res=""
    res+=hint
    if len(hint)<hint_len:
        res+=" "*(hint_len-len(hint))
    print("\r", end="")
    already_len=progress_len*already//total
    if already_len>progress_len:
        already_len=progress_len
    res+="|"
    res+="—"*already_len
    res+=" "*(progress_len-already_len)
    res+="|"
    res+=" "
    already_str=str(already)
    total_str=str(total)
    if len(already_str)<len(total_str):
        res+=" "*(len(total_str)-len(already_str))
    res+=already_str
    res+="/"
    res+=total_str
    if len(ending)>0:
        res+=" "
        res+=ending
    now_len=len(res)
    if len(res)<last_res_len:
        res+=" "*(last_res_len-len(res))
    last_res_len=now_len
    print(res,end="")
    sys.stdout.flush()
def ending(clear=False,ending_text=""):
    global last_res_len
    if clear:
        print("\r"+" "*last_res_len,end="")
    else:
        print(ending_text)
    last_res_len=0
    sys.stdout.flush()
if __name__=="__main__":
    for i in range(0,50+1):
        show("test1",i,50,"test"+str(i//10))
        time.sleep(0.05)
    ending(True)
    for i in range(0,50+1):
        show("test2",i,50)
        time.sleep(0.05)
    ending(True)
