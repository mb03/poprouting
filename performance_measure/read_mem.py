import os.path,sys
import time
import commands
def parse_map_line(s):
    d=s.split(" ")
    d=[d for d in d if d]
    mem=(d[0].split("-"))
    mem=((int(mem[1],16)-int(mem[0],16))/1024)
    base=0
    if d[3]=="00:00":
        base=6
    name=(d[1][:-1])
    if name == "r-x" and base <6:
        base+=5
    elif name == "rwx":
        base+=0
    elif name == "r--":
        base+=1
    elif name == "rw-":
        base+=2
    elif name == "---":
        base+=3
    else:
        base+=4
    #"Write/Exec\tRO data\t\tData\tUnreadable\tUnknown\tExecutable\t#Unkwnown:Writable code\tRO data\tData\tUnreadable\tUnknown"
    return mem,base


s=commands.getstatusoutput('pstree -p  | grep prince_c')
s=s[1]
pid=s[s.find("prince_c(")+9:]
pid=pid[:pid.find(")")]
if not pid:
    print "prince_c not running"
    exit(0)



if len(sys.argv)>=2:
    pid=sys.argv[1]

f = open('log_mem_py.txt', 'w+')
f.write("Timestamp\tWrite/Exec\tRO data\t\tData\t\tUnreadable\tUnknown\t\tExecutable\t#Unkwnown:Writable code\t\tRO data\t\tData\tUnreadable\tUnknown\ttotal\n")
file="/proc/"+pid+"/maps"
sum = [0,0,0,0,0,0,0,0,0,0,0,0]
count = 0
while os.path.isfile(file):
    with open (file, "r") as myfile:
        data=myfile.readlines()
    data=[d.strip() for d in data]
    to_write=[0,0,0,0,0,0,0,0,0,0,0,0]
    total=0
    for d in data:
        mem,offset=parse_map_line(d)
        to_write[offset]+=mem
        total+=mem
    to_write[11]=total
    for idx, val in enumerate(to_write):
        sum[idx]+=val
    count+=1
    f.write(str('{0:.0f}'.format(time.time()*1000))+"\t"+
                str(to_write[0])+"\t\t"+str(to_write[1])+"\t\t"+str(to_write[2])+""
                "\t\t"+str(to_write[3])+"\t\t"+str(to_write[4])+"\t\t"+str(to_write[5])+"\t\t"+str(to_write[6])+"\t\t\t\t"
                 ""+str(to_write[7])+"\t\t"+str(to_write[8])+"\t"+str(to_write[9])+"\t\t"+str(to_write[10])+"\t"+
                  str(to_write[11])+"\t\n")
    time.sleep(0.002)
f.write("===============\n")
for idx, val in enumerate(sum):
    sum[idx]=val/count
f.write("Avarages \t"+
                str(sum[0])+"\t\t"+str(sum[1])+"\t\t"+str(sum[2])+""
                "\t\t"+str(sum[3])+"\t\t"+str(sum[4])+"\t\t"+str(sum[5])+"\t\t"+str(sum[6])+"\t\t\t\t"
                 ""+str(sum[7])+"\t\t"+str(sum[8])+"\t"+str(sum[9])+"\t\t"+str(sum[10])+"\t"+
                  str(sum[11])+"\t\n")
f.close()
print("avg",sum[11])

