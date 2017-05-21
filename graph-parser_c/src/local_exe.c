#include <stdio.h>
#include <stdlib.h>
#include "brandes.h"
#include "local_exe.h"

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

void write_to_file(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "w+");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

int run(int argc, char** argv) {
     if(argc<3){
        return -1;
    }
    bool heuristic=atoi(argv[1])==1;
    char * id_node=argv[2];
    multithread=false;
    if(argc==4){
	multithread=atoi(argv[3])==1;
    }
    struct graph * g=read_graph_from_file("input.edgelist");
    double * bc;
    if(heuristic){
        bc=(double*)betwenness_heuristic(g,recursive);
    }else{
        bc=betweeness_brandes(g,true,0);
    }
    struct node_list * nl=g->nodes.head;
    double centrality=-1;
    for(;nl!=0;nl=nl->next){
        struct node_graph * ng=( struct node_graph*)nl->content;
        if(strcmp(id_node,ng->name)==0){
            centrality=bc[ng->node_graph_id];
            break;
        }
    }
    if(centrality<0){
        write_to_file("output.txt","Node id not found. %%s not matching. (string)\n");
        
    }else{
           FILE *fp;
	    fp = fopen("output.txt", "w+");
	    if (fp == NULL) {
		printf("I couldn't open results.dat for writing.\n");
		exit(0);
	    }
	    struct node_list * nl;
	    int i=0;
	    for(nl=g->nodes.head;nl!=0;nl=nl->next){
		struct node_graph* ng=( struct node_graph*)nl->content;
		fprintf(fp, "%f,%s\n",(float) bc[ng->node_graph_id], ng->name );
	    }
	    fclose(fp);
    }
    return (EXIT_SUCCESS);
}

