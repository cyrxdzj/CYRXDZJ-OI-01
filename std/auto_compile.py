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
        if file.endswith(".cpp"):
            inroot=int(i[0]!=".")
            cpp_list.append(i[0][len(".")+inroot:]+"/"*inroot+file)
print(cpp_list)
for cpp in cpp_list:
    print("\033[34m"+cpp+"\033[0m")
    exe=cpp.replace(".cpp",".exe")
    os.system("g++ {cpp} -fdiagnostics-color=always -lm -O2 -Wall -Wl,-stack=134217728 -std=c++14 -static -o {exe}".format(cpp=cpp,exe=exe))
    #input("Enter to continue")
