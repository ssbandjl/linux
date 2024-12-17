#!/usr/bin/python3
import shutil
import time

print("删除空行和回车(压缩段落)")
while True:
  f_output=open('output', 'w', encoding='utf8')
  with open('input_en', 'r', encoding='utf8') as f:
    line = "\n" + f.read().replace("\n", " ") + "\n"
    mylist=[c for c in line if ord(c)!=10]
    if(len(mylist) == 0):
      continue
    # delete last space
    mylist[len(mylist)-1]=mylist[len(mylist)-1].rstrip()
    # print(mylist)
    if mylist[len(mylist)-2] == ".":
      mylist=mylist[0:len(mylist)-2]
    if mylist:
      # print("".join(mylist))
      f_output.write("".join(mylist)+'\n')
  f_output.close()
  shutil.move("output", "input_en")
  time.sleep(1)
