import os
task_list=["permutation","melody","tree","library"]
for task in task_list:
    os.system("cd {task} && python {task}_batch_checker.py".format(task=task))
