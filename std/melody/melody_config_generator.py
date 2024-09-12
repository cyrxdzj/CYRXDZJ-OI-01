import sys
pre=\
'''type: default
time: 1s
memory: 256m
filename: melody
checker_type: default
'''
def prt_subtask(subid,tcnt,score):
    print("  - score: %d\n    type: min\n    cases:"%score)
    for ptid in range(1,tcnt+1):
        print("      - input:  melody_sub%02d_pt%02d.in"%(subid,ptid))
        print("        output: melody_sub%02d_pt%02d.ans"%(subid,ptid))
print(pre)
print("subtasks:")
prt_subtask(1,5,10)
prt_subtask(2,5,10)
prt_subtask(3,5,20)
prt_subtask(4,5,20)
prt_subtask(5,5,40)
