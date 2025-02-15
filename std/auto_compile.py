import os
import progress_bar
import sys,getopt
opts, args = getopt.getopt(sys.argv[1:],"c")
clean_exe=False
cpp_list=[]
exe_list=[]
for opt in opts:
    if opt[0]=="-c":
        clean_exe=True
for i in os.walk("."):
    for file in i[2]:
        if not clean_exe:
            if file.endswith(".cpp"):
                inroot=int(i[0]!=".")
                cpp_list.append(i[0][len(".")+inroot:]+"/"*inroot+file)
        else:
            if file.endswith(".exe"):
                inroot=int(i[0]!=".")
                exe_list.append(i[0][len(".")+inroot:]+"/"*inroot+file)
#print(cpp_list)
if not clean_exe:
    for cpp in cpp_list:
        print("\033[1;34m"+cpp+"\033[0m")
        exe=cpp.replace(".cpp",".exe")
        os.system("g++ {cpp} -fdiagnostics-color=always -lm -O2 -Wno-unused-but-set-variable -Wno-unused-variable -Wall -Wl,-stack=134217728 -std=c++14 -static -o {exe}".format(cpp=cpp,exe=exe))
        #input("Enter to continue")
else:
    for exe in exe_list:
        print("\033[1;31m"+exe+"\033[0m")
        os.remove(exe)
