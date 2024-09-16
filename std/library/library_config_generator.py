import sys
pre=\
'''type: default
time: 3000ms
memory: 1024m
filename: library
checker_type: default
'''
def prt_subtask(subid,tcnt,score):
    print("  - score: %d\n    type: sum\n    cases:"%score)
    for ptid in range(1,tcnt+1):
        print("      - input:  library_sub%02d_pt%02d.in"%(subid,ptid))
        print("        output: library_sub%02d_pt%02d.ans"%(subid,ptid))
        if 4<=ptid and ptid<=9:
            print("        time: 4000ms")
print(pre)
print("subtasks:")
prt_subtask(1,25,100)