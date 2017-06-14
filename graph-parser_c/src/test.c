/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.c
 * Author: principale
 *
 * Created on January 25, 2017, 5:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../prince/src/parser.h"
#include "graph_parser.h"

char* read_file_content(char *filename)
{
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");
    
    if (handler)
    {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);
        
        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
        
        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);
        
        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';
        
        if (string_size != read_size)
        {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }
        
        // Always remember to close the file.
        fclose(handler);
    }
    
    return buffer;
}

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
#include <sys/time.h>
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
double run_test( bool heuristic, bool thread,struct graph * g) {
    multithread=thread;
   
    double * bc;
    int s = time(NULL);
clock_t t = clock();
struct timeval tv;
gettimeofday(&tv,NULL);
    unsigned long int time = getMicrotime();
    if(heuristic){
        bc=(double*)betwenness_heuristic(g,recursive);
    }else{
        bc=betweeness_brandes(g,true,0);
    }
    t = clock() - t;
    time =getMicrotime()-time;
    printf("realtime  %lu\n",time);
    return ((double)t)/CLOCKS_PER_SEC;
}

int main(int argc, char** argv) {
if(argc<3){
        printf("Usage a.out heu thredead. E.g. ./a.out 1 1. Exiting.\n");
        return 0;
    }
bool h,t;
h=atoi(argv[1])==1;
t=atoi(argv[2])==1;
struct graph * g=read_graph_from_file("input.edgelist");
double res=0;
int repetitions=10;
double *values=(double*)malloc(sizeof(double)*repetitions);
int i=0;
for(;i<repetitions;i++){
double r=run_test(h,t,g);
printf("exe %d %f \n",i,r);
values[i]=r;
res+=r;
}
double m=res/repetitions;
double var=0;
for(i=0;i<repetitions;i++){
double std=m-values[i];
var+=std*std;
}
var/=repetitions;
printf("res %f +-(%f)\n",m,var);
free(values);
}
/*
int main(int argc, char** argv) {
    if(argc==1){
        printf("I need to know if i have to use heuristic. Exiting.\n");
        return 0;
    }
    int heuristic=atoi(argv[1]);
    //to remove in case of different test
    multithread=false;
    if(argc==3){
	multithread=atoi(argv[2])==1;
        //stop_computing_if_unchanged=atoi(argv[2])==1;
    }
    c_graph_parser* cgp=new_graph_parser(1, heuristic);
    char * file_content=read_file_content("input.json");
    struct topology *topo=parse_netjson(file_content);
    free(file_content);
    graph_parser_parse_simplegraph(cgp,topo);
    graph_parser_calculate_bc(cgp);
    map_id_degree_bc * bc_degree_map = (map_id_degree_bc *) malloc(sizeof(map_id_degree_bc));
    
    graph_parser_compose_degree_bc_map(cgp,bc_degree_map);
    
    int i;
    // printf("[\n");
    printf("{\n");
    for(i=0; i<bc_degree_map->size; i++){
        //if(strcmp(bc_degree_map->map[i].id, node_name)==0){
        printf("%s:%1.50f",bc_degree_map->map[i].id,bc_degree_map->map[i].bc);
        //   break;
        //  }
        if(i<bc_degree_map->size-1)
            printf(",");
        printf("\n");
    }
    printf("}\n");
    delete_graph_parser(cgp);
    return (EXIT_SUCCESS);
}*/
