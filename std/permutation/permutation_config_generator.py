import sys
pre=\
'''type: default
time: 1s
memory: 256m
filename: permutation
checker_type: testlib
checker: permutation_testlib_checker.cpp
'''
def prt_subtask(subid,tcnt,score):
    print("  - score: %d\n    type: min\n    cases:"%score)
    for ptid in range(1,tcnt+1):
        print("      - input:  permutation_sub%02d_pt%02d.in"%(subid,ptid))
        print("        output: permutation_sub%02d_pt%02d.ans"%(subid,ptid))
print(pre)
print("subtasks:")
prt_subtask(1,10,10)
prt_subtask(2,10,10)
prt_subtask(3,10,20)
prt_subtask(4,10,20)
prt_subtask(5,10,40)
