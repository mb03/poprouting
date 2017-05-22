#include <stdio.h>
#include <stdlib.h>
#include "brandes.h"
#include "local_exe.h"
#include <time.h>
extern bool multithread;
extern bool recursive;
struct graph * read_graph_from_file(char * source_file){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(source_file, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    struct graph * g=(struct graph *)malloc(sizeof(struct graph));
    init_graph(g);
    while ((read = getline(&line, &len, fp)) != -1) {
        char source[256], target[256];
        float cost;
        int n=sscanf( line, "%s %s %f", source, target, &cost);
        if(n==2){
            add_edge_graph(g,source,target, 1,false);
        }else if(n==3){
            add_edge_graph(g,source,target, cost,false);
        }
    }
    
    fclose(fp);
    if (line)
        free(line);
    return g;
}


double run_test(int argc, char** argv) {
     if(argc<3){
        return -1;
    }
    bool heuristic=atoi(argv[1])==1;
    multithread=false;
    if(argc==3){
	multithread=atoi(argv[2])==1;
    }
    if(argc==4){
	recursive=atoi(argv[3])==1;
    }
    struct graph * g=read_graph_from_file("input.edgelist");
    double * bc;
    clock_t t = clock();
    if(heuristic){
        bc=(double*)betwenness_heuristic(g,recursive);
    }else{
        bc=betweeness_brandes(g,true,0);
    }
    t = clock() - t;
    return ((double)t)/CLOCKS_PER_SEC;
}

void run_tests(int argc, char** argv,double* mean, double *var){
double t=0;
int i=0;
double vals[10];
for(;i<10;i++){
double tmp=run_test(argc, argv);
t+=tmp;
vals[i]=tmp;
}
(*mean)=t/10;
double v=0;
for(;i<10;i++){
double tmp=(*mean)-vals[i];
v+=tmp*tmp;
}
(*var)=v/10;
}
