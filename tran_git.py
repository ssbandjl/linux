#!/usr/bin/python3
import shutil
import time
import hashlib
import os
import time

print("删除空行和回车(压缩段落)")

# md5_new = ""
# md5_old = ""
while True:
    mylist = []
    file_mtime = os.path.getmtime('input_en')
    if(time.time() - file_mtime > 5):
        # print(f"same_file, file_mtime:{file_mtime}, now:{time.time()}")
        time.sleep(2)
        continue
    # with open('input_en','rb') as f:
    #     md5_new = hashlib.md5(f.read()).hexdigest()
    #     if md5_new == md5_old:
    #         # print(f"same file, md5={md5_new}")
    #         time.sleep(3)
    #         continue
    
    # md5_old = md5_new
    with open('input_en', 'r', encoding='utf8') as f:
        # replace first return to ','
        content = (f.readlines())
        total_line = len(content)
        if (total_line == 1):
             continue
        content = ("".join(content)).replace("\n", ",", 1)
        # replace all
        # print(content)
        content = "\n" + content.replace("\n", " ") + "\n"
        # print("content", content)
        # if line_no == 1 and len(line) == 0:
        #     line = ","
        mylist=[c for c in content if ord(c)!=10]
        # print(mylist)
        if(len(mylist) == 0):
                continue
        # delete last space
        mylist[len(mylist)-1]=mylist[len(mylist)-1].rstrip()
        if mylist[len(mylist)-1] == "":
            mylist = mylist[0:(len(mylist)-2)]
        # print(mylist)
        last_item = mylist[len(mylist)-1]
        # print("last_item", last_item)
        if last_item == "." or last_item == "。":
            mylist=mylist[0:len(mylist)-1]

    if mylist:
        # print("".join(mylist))
        f_output=open('output', 'w', encoding='utf8')
        f_output.write("".join(mylist)+'\n')
        f_output.close()
    shutil.move("output", "input_en")
    time.sleep(2)
    # break

