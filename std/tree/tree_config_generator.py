import sys
pre=\
'''type: default
time: 2000ms
memory: 512m
filename: tree
checker_type: default
'''
def prt_subtask(subid,tcnt,score,sub_type="min"):
    print("  - score: %d\n    type: %s\n    cases:"%(score,sub_type))
    for ptid in range(1,tcnt+1):
        print("      - input:  tree_sub%02d_pt%02d.in"%(subid,ptid))
        print("        output: tree_sub%02d_pt%02d.ans"%(subid,ptid))
print(pre)
print("subtasks:")
prt_subtask(1,3,4)
prt_subtask(2,6,12)
prt_subtask(3,6,18,"sum")
prt_subtask(4,6,24,"sum")
prt_subtask(5,6,42,"sum")
