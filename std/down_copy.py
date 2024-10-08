import shutil
import zipfile
import os
import progress_bar
task_list=["permutation","melody","tree","library"]
print("Copy files to down")
shutil.copy("../std/permutation/permutation_testlib_checker.cpp","../down/permutation/checker.cpp")
shutil.copy("../std/permutation/testlib.h","../down/permutation/testlib.h")
shutil.copy("../std/library/library_probability_calc.cpp","../down/library/library_probability_calc.cpp")
def write_zip(fa_dir,tgt_zip_path,hint):
    with zipfile.ZipFile(tgt_zip_path,"w",compression=zipfile.ZIP_DEFLATED) as zipobj:
        file_list=[]
        #fa_dir="../down"
        for i in os.walk(fa_dir):
            for file in i[2]:
                inroot=int(i[0]!=fa_dir)
                file_list.append(i[0][len(fa_dir)+inroot:]+"/"*inroot+file)
            #print(i)
        #print(file_list)
        #return
        for i in range(len(file_list)):
            progress_bar.show(hint,i+1,len(file_list),file_list[i])
            zipobj.write(fa_dir+"/"+file_list[i],file_list[i])
        progress_bar.show(hint,len(file_list),len(file_list),"")
        progress_bar.ending()
write_zip("../down","../CYRXDZJ-OI-01_down.zip","Copy files to main zip")
for task in task_list:
    write_zip("../down/{task}".format(task=task),"../{task}_down.zip".format(task=task),"Copy files to {task} zip".format(task=task))
