import sys
pre=\
'''type: default
time: 5s
memory: 512m
filename: library
checker_type: default
'''
def prt_subtask(subid,tcnt,score):
    print("  - score: %d\n    type: sum\n    cases:"%score)
    for ptid in range(1,tcnt+1):
        print("      - input:  library_sub%02d_pt%02d.in"%(subid,ptid))
        print("        output: library_sub%02d_pt%02d.ans"%(subid,ptid))
print(pre)
print("subtasks:")
prt_subtask(1,9,100)