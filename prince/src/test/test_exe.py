#!/usr/bin/env python
import os,json,time,math,types
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt
from numpy import var,mean
from graph_lib.graph_generator import Gen
from random import Random
import networkx as nx
r=Random(1234)


def gen_graph(N):
    ge = Gen()
    ge.genGraph("PLAW", N)
    graph = ge.graph
    graph2=nx.Graph()
    for e in graph.edges():
        graph2.add_edge(e[0],e[1],weight=r.uniform(0,10))
    graph=graph2
    netjson = ge.composeNetJson(graph)
    #print(netjson)
    json_netjson = json.dumps(netjson)
    text_file = open("input.json", "w+")
    text_file.write(json_netjson)
    text_file.close()
    return graph

def time_exe(is_c,heu,d=None):
    heu=str(heu)
    exe="./c++.out "
    if is_c:
        exe="./c.out"
        heu=" "+heu+" 0"
    start = time.time()
    exe=exe+heu
    if d:
        exe+=" 1"
    p = Popen(exe,shell=True,stdout=PIPE,stderr=PIPE)
    #os.wait4(p.pid, 0)
    out, err = p.communicate()
    elapsed = time.time() - start
    title=""
    if is_c:
        title+="C "
    else:
        title+="C++ "
    if heu:
        title+=" with heu"
    else:
        title+=" without heu"
    if out:
        #print(out)
        out=eval(out)
        global rounding
        out= {k:round(v,rounding) for k,v in out.iteritems()}
        #out= {k:v for k,v in out.iteritems()}
    return elapsed,out

rounding=50
start,end,jump=2001,2000+1,100
repetitions=10
max=int(math.ceil(float(end-start)/jump))*repetitions

res={}
res["x"]=[]
res["c_var"]=[]
res["c_mean"]=[]
res["c_eu_var"]=[]
res["c_eu_mean"]=[]
res["c_eu_var_t"]=[]
res["c_eu_mean_t"]=[]
res["c++_var"]=[]
res["c++_mean"]=[]
res["c++_eu_var"]=[]
res["c++_eu_mean"]=[]
res["c++_eu_var"]=[]
res["c++_eu_mean"]=[]
index=1

for i in range(start,end,jump):
    #g=nx.read_weighted_edgelist()
    c_eu=[]
    c=[]
    cpp_eu=[]
    cpp=[]
    c_t=[]
    for j in xrange(repetitions):
        print(str(round(100*float(index)/max,2))+"%")
        index+=1
        g=nx.read_weighted_edgelist("data/"+str(i)+"/"+str(j))
        netjson = Gen().composeNetJson(g)
        #print(netjson)
        json_netjson = json.dumps(netjson)
        text_file = open("input.json", "w+")
        text_file.write(json_netjson)
        text_file.close()
        timer,val1=time_exe(1,0)
        c.append(timer)
        timer,val2=time_exe(1,1)
        c_eu.append(timer)
        timer,val3=time_exe(0,0)
        cpp.append(timer)
        timer,val4=time_exe(0,1)
        cpp_eu.append(timer)
        timer,val5=time_exe(1,1,d=True)
        c_t.append(timer)
        actual_res=nx.betweenness_centrality(g,endpoints=True,weight='weight')
        actual_res= {int(k):round(v,rounding) for k,v in actual_res.iteritems()}
        if (not (actual_res==val1 and val1==val2)):
            print("val1",val1)
            print("val2",val2)
            print("actual_res",actual_res)
            for e in g.edges(data='weight'):
                print('add_edge_graph(&g1,"'+str(e[0])+'","'+str(e[1])+'",'+str(e[2])+',0);')
    res["c_var"].append(var(c))
    res["c_mean"].append(mean(c))
    res["c_eu_var"].append(var(c_eu))
    res["c_eu_mean"].append(mean(c_eu))
    res["c++_var"].append(var(cpp))
    res["c++_mean"].append(mean(cpp))
    res["c++_eu_var"].append(var(cpp_eu))
    res["c++_eu_mean"].append(mean(cpp_eu))
    res["c_eu_var_t"].append(var(c_t))
    res["c_eu_mean_t"].append(mean(c_t))
    res["x"].append(i)

res={'c_var': [3.079045109757317e-06, 3.2284803970128452e-05, 0.00035855644576315621, 0.0018633352917709089, 0.0017084892814756361, 0.0087269819302719046, 0.023566170913159112, 0.010420066823406271, 0.072539292494741406, 0.023545214061178397, 0.066710114420280325, 0.082635186403231267, 0.078437865373660431, 0.30225191725149669, 0.28781583283440343, 0.56737657331278168, 1.0210478961569627, 1.5441287437432265, 2.8344599856725243], 'c_mean': [0.027782130241394042, 0.061741232872009277, 0.14532949924468994, 0.27109937667846679, 0.4726168394088745, 0.77682662010192871, 1.226423978805542, 1.1698153734207153, 1.7319459915161133, 2.367231011390686, 3.0297657251358032, 3.7128457069396972, 4.7579834222793576, 5.9415364742279051, 7.0694287300109862, 8.6788706541061398, 13.832569932937622, 16.959306240081787, 19.78138608932495], 'c++_var': [2.9266556534821572e-05, 0.00057685992350343441, 0.00029640789013058106, 0.0041563564658309814, 0.015221266203027994, 0.0016755655312300631, 0.0026230839716959052, 0.0033144091218923672, 0.0072663723130227701, 0.0058873152564757449, 0.0030628490610547484, 0.034006430722513414, 0.0039793102253611323, 0.027446659231443394, 0.031656148916883918, 0.024852760634630613, 0.019933522599627055, 1.4905783359141704, 0.17113348264934075], 'c_eu_var_t': [1.891434030767414e-06, 2.9908945953138753e-06, 4.8160784126594088e-06, 9.0302926315644067e-06, 6.6776720819916599e-06, 6.7841055403050625e-06, 3.5642247075884372e-06, 3.7786674289463911e-06, 3.699795536817873e-06, 9.639698453725031e-06, 4.7688667115153292e-06, 9.1945094169432195e-06, 4.0391778475168392e-06, 3.4691794007812867e-06, 5.7855417480823233e-06, 1.3830845853135543e-05, 9.2825558505182931e-06, 5.3779252817776062e-06, 8.3290346196918105e-06], 'c++_eu_var': [4.613164531406256e-06, 7.270785315540707e-06, 3.6371057285577995e-06, 1.5854193773066072e-05, 2.4048334699386944e-05, 1.1182773608311436e-05, 9.9817620485964665e-06, 1.4142089455617679e-05, 3.3326440748169263e-05, 3.13303680223953e-05, 0.00010711481909822851, 4.374295332127077e-05, 9.9281287032795278e-05, 9.564891263892151e-05, 4.586335688884447e-05, 0.00013760207512461873, 9.8746734429369093e-05, 0.00013280468045877568, 2.9719906362970507e-05], 'c_eu_mean_t': [0.0088977336883544929, 0.011555480957031249, 0.016652679443359374, 0.017162489891052245, 0.021706986427307128, 0.023713898658752442, 0.029404354095458985, 0.032223296165466306, 0.037597012519836423, 0.041629958152770999, 0.045457291603088382, 0.052385687828063965, 0.057448434829711917, 0.064859056472778315, 0.072672367095947266, 0.080348491668701172, 0.097455286979675287, 0.10942413806915283, 0.11883354187011719], 'c++_eu_mean': [0.055230116844177245, 0.077481317520141604, 0.10095033645629883, 0.12779607772827148, 0.15116240978240966, 0.17535607814788817, 0.2063056707382202, 0.23210520744323732, 0.26115932464599612, 0.29163954257965086, 0.32323172092437746, 0.36245756149291991, 0.40064232349395751, 0.43731644153594973, 0.4781277894973755, 0.51492950916290281, 0.54900093078613277, 0.60560011863708496, 0.63968830108642583], 'x': [200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000], 'c_eu_var': [1.1693793686617935e-06, 2.3631416121361326e-06, 1.9657994471344865e-06, 1.2014816459213762e-05, 6.2363254579622669e-06, 7.9003996938809001e-06, 9.5569585118937554e-06, 1.1144995688141534e-05, 4.3848344398611513e-06, 4.2811899766093121e-06, 1.3343245964847483e-05, 9.8154244938086783e-06, 2.9264503274362141e-06, 6.4333852384379492e-06, 3.7493368517971255e-06, 1.0018973721912516e-05, 6.7855338579647646e-06, 1.1394419641987951e-05, 5.1025912762270304e-06], 'c++_mean': [0.4487277030944824, 1.0546749591827393, 1.9847837209701538, 3.1622558355331423, 4.5336397886276245, 6.1805221319198607, 8.2619941234588623, 10.59183897972107, 13.345622277259826, 16.42150866985321, 19.725582027435301, 23.37342357635498, 27.397682666778564, 32.012427425384523, 36.584758090972898, 41.6774619102478, 47.009242606163028, 53.805213665962221, 59.10912380218506], 'c_eu_mean': [0.008884024620056153, 0.011310601234436035, 0.013976812362670898, 0.018319225311279295, 0.019821619987487792, 0.02554640769958496, 0.028730583190917969, 0.034122395515441897, 0.037007713317871095, 0.041736650466918948, 0.046199917793273926, 0.052502870559692383, 0.056015324592590329, 0.064590382575988772, 0.072520828247070318, 0.080020689964294428, 0.098456048965454096, 0.11005575656890869, 0.118446683883667]}

plt.errorbar(res["x"], res["c++_mean"], yerr=res["c++_var"], label="C++ w/o h")
plt.errorbar(res["x"], res["c++_eu_mean"], yerr=res["c++_eu_var"], label="C++ w h")
plt.errorbar(res["x"], res["c_mean"], yerr=res["c_var"], label="C w/o h")
plt.errorbar(res["x"], res["c_eu_mean"], yerr=res["c_eu_var"], label="C w h")
#plt.errorbar(res["x"], res["c_eu_mean_t"], yerr=res["c_eu_var_t"], label="C w h")
plt.xlabel('size of graph (nodes)')
plt.ylabel('execution time (s)')
plt.yscale('log')
plt.legend(loc='upper center', shadow=True)
#plt.axhline(1,color='k')
for var in (res["c_mean"], res["c_eu_mean"],res["c++_mean"],res["c++_eu_mean"]):
    plt.annotate('%0.2f' % var[-1], xy=(1, var[-1]), xytext=(8, 0),
                 xycoords=('axes fraction', 'data'), textcoords='offset points')
plt.savefig('res.png')
plt.show()
