import os
import PyPDF2
import time
task_list=["permutation","melody","tree","library"]
md_path="../std/{task}/{task}.md"
pdf_path="../down/{task}/{task}.pdf"
pdf_list=[]
pdf_list.append("../std/introduction.pdf")
if os.path.getmtime("../std/introduction.md")>os.path.getmtime("../std/introduction.pdf"):
    print("introduction","The modification time of PDF is earlier than that of Markdown.")
for task in task_list:
    md_time=os.path.getmtime(md_path.format(task=task))
    pdf_time=os.path.getmtime(pdf_path.format(task=task))
    pdf_list.append(pdf_path.format(task=task))
    #print(time.localtime(md_time),time.localtime(pdf_time))
    if md_time>pdf_time:
        print(task,"The modification time of PDF is earlier than that of Markdown.")
merger=PyPDF2.PdfMerger()
for pdf in pdf_list:
    merger.append(PyPDF2.PdfReader(pdf))
merger.write("../down/statements.pdf")
