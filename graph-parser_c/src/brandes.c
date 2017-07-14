/*
 * File:   brandes.c
 * Author: principale
 *
 * Created on January 18, 2017, 12:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "brandes.h"
#include "biconnected.h"


//parameter initialization
bool recursive=true;



/**
 * This function implements brandes algorithm. Given a weighted graph,
 * it returns an array of value, in which for every node identifier there is
 * its betwenness centrality value. For each node, it computes all routes to all
 * other node, and since it is weighted, uses Dijkstra algorithm.
 * After this, it computes for each link the contribute to the current node.
 * As last operation, a normalization is compute in the number of nodes ( see
 * http://algo.uni-konstanz.de/publications/b-vspbc-08.pdf)
 *
 * @param g A (undirected) graph for which we want to compute centrality
 * of nodes.
 * @param endpoints Whether we want to include endpoints in final value. It is
 * always used as true when calling this function with next parameter null.
 * @param articulation_point_val It is either 0 or an array of integers. In first case,
 * normal brandes algorithm run, in second the heuristic one, considering
 *  intra-component and  inter-component traffic
 * @return An array with betwenness centrality for each node
 */
float * betweeness_brandes(struct graph * g, bool endpoints,uint8_t * articulation_point_val){
    struct priority_queue q;
    struct list S;
    init_priority_queue(&q);
    init_list(&S);
    uint8_t node_num=g->nodes.size;
    float * dist=( float *)malloc(node_num*sizeof(float));
    struct list * pred=(struct list *)malloc(node_num*sizeof( struct list));
    uint8_t * sigma=( uint8_t *)malloc(node_num*sizeof(uint8_t));
    float * delta=( float *)malloc(node_num*sizeof(float));
    float * ret_val=( float *)malloc(node_num*sizeof(float));
    uint8_t i;
    for( i =0;i<node_num;i++){
        ret_val[i]=0;
        init_list(pred +i);
    }
    struct node_list * n=0;
    
    for(n=g->nodes.head;n!=0; n=n->next){
        struct node_graph* s=(struct node_graph*) n->content;
        for( i =0;i<node_num;i++){
            clear_list(pred +i);
            dist[i]=(float)FLT_MAX;
            sigma[i]=0;
            delta[i]=0;
        }
        dist[s->node_graph_id]=0;
        sigma[s->node_graph_id]=1;
        insert_priority_queue(&q,(void*)s,0);
        /**
         * weighted shortest path (dijkstra)
         */
        while(!is_empty_priority_queue(&q)){
            struct node_graph* v=(struct node_graph*)dequeue_priority_queue(&q);
            enqueue_list(&S,v);
            if(v->neighbours.size>0){
                struct node_list * edge_iterator;
                for(edge_iterator=v->neighbours.head;edge_iterator!=0;edge_iterator=edge_iterator->next){
                    struct edge_graph * edge=(struct edge_graph*)edge_iterator->content;
                    struct node_graph * w=edge->to;
                    float weight=edge->value;
                    if(dist[w->node_graph_id]>(dist[v->node_graph_id]+weight)){
                        dist[w->node_graph_id]=dist[v->node_graph_id]+weight;
                        insert_or_update_priority_queue(&q,w,dist[w->node_graph_id]);
                        sigma[w->node_graph_id]=0;
                        clear_list(pred +w->node_graph_id);
                    }if(dist[w->node_graph_id]==(dist[v->node_graph_id]+weight)){
                        sigma[w->node_graph_id]+= sigma[v->node_graph_id];
                        enqueue_list( pred+w->node_graph_id,v);
                    }
                }
            }
        }
        
        //accumulation
        if(articulation_point_val!=0){//traffic_matrix!=0){
            //endpoints included by default
            while(!is_empty_list(&S)){
                struct node_graph * w=(struct node_graph * )pop_list(&S);
                // float communication_intensity=(float)traffic_matrix[w->node_graph_id][s->node_graph_id];
                //new
                uint8_t new_val=0;
                if(w->node_graph_id!=s->node_graph_id){
                    uint8_t w_val=articulation_point_val[w->node_graph_id],s_val=articulation_point_val[s->node_graph_id];
                    if(w_val==0 && s_val==0){
                        new_val=1;
                    }else if(w_val>0 && s_val>0){
                        new_val=w_val*s_val;
                    }else if(w_val>0){
                        new_val=w_val;
                    }else{
                        new_val=s_val;
                    }
                }
                //new end
                //float communication_intensity=(float)traffic_matrix[w->node_graph_id][s->node_graph_id];
                float communication_intensity=(float)new_val;
                ret_val[s->node_graph_id]+=communication_intensity;
                struct node_list * node_iterator;
                for(node_iterator =pred[w->node_graph_id].head;node_iterator!=0;node_iterator=node_iterator->next){
                    struct node_graph * v=(struct node_graph*)node_iterator->content;
                    delta[v->node_graph_id]+=((delta[w->node_graph_id]+communication_intensity)*(((float)sigma[v->node_graph_id])/ ((float)sigma[w->node_graph_id])));
                }
                if(w!=s){
                    ret_val[w->node_graph_id]+=delta[w->node_graph_id]+communication_intensity;
                }
            }
            
        }else if(endpoints){
            ret_val[s->node_graph_id]+=(S.size-1);
            while(!is_empty_list(&S)){
                struct node_graph * w=(struct node_graph * )pop_list(&S);
                struct node_list * node_iterator;
                float coeff=(1+delta[w->node_graph_id])/((float)sigma[w->node_graph_id]);
                for(node_iterator =pred[w->node_graph_id].head;node_iterator!=0;node_iterator=node_iterator->next){
                    struct node_graph * v=(struct node_graph*)node_iterator->content;
                    delta[v->node_graph_id]+=((float)sigma[v->node_graph_id])*coeff;
                }
                if(w!=s){
                    ret_val[w->node_graph_id]+=delta[w->node_graph_id]+1;
                }
            }
        }else{
            while(!is_empty_list(&S)){
                struct node_graph * w=(struct node_graph * )pop_list(&S);
                struct node_list * node_iterator;
                for(node_iterator =pred[w->node_graph_id].head;node_iterator!=0;node_iterator=node_iterator->next){
                    struct node_graph * v=(struct node_graph*)node_iterator->content;
                    delta[v->node_graph_id]= delta[v->node_graph_id]+((((float)sigma[v->node_graph_id])/ ((float)sigma[w->node_graph_id]))*(1+delta[w->node_graph_id]));
                }
                if(w!=s){
                    ret_val[w->node_graph_id]=ret_val[w->node_graph_id]+delta[w->node_graph_id];
                }
            }
        }
    }
    free(dist);
    for( i =0;i<node_num;i++){
        clear_list(&pred[i]);
    }
    //clear_list(pred);
    free(pred);
    free(sigma);
    free(delta);
    struct node_list * nl=g->nodes.head;
    if(node_num>2&&articulation_point_val==0){//traffic_matrix==0){
        float scale=1/(((float)(node_num-1))*((float)(node_num-2)));
        for( i =0;i<node_num;i++){
            struct node_graph* ng=(struct node_graph*)nl->content;
            ret_val[ng->node_graph_id]*=scale;
            //ret_val[ng->node_graph_id]=round_decimal(ret_val[ng->node_graph_id]);
            nl=nl->next;
        }
        
    }
    return ret_val;
}


// normal defines whether the pair is (B,v) (if false, (v,B)). Since ordering
// would be a major computational effort, a boolean ("normal") indicates that.
struct cc_node_edge{
    struct connected_component * from;
    struct node_graph * to;
    int16_t * weight;
    bool normal;
};

/**
 * Algorithm for heuristic  (not described explicitly in the paper)
 * It initializes a link from a cutpoint to a component.
 *
 * @param from The connected component on the end of the link
 * @param to The node (in the connected component) originating the link
 * @param weight The edge weight
 * @param normal Whether in the computation represent a normal couple
 * node-component or a component-node one. Used in compute_component_tree_weights
 * @return the newly created link
 */
struct cc_node_edge * init_cc_node_edge(struct connected_component * from,struct node_graph * to,int16_t * weight,bool normal){
    struct cc_node_edge * cne=(struct cc_node_edge * )malloc(sizeof(struct cc_node_edge ));
    cne->from=from;
    cne->to=to;
    cne->weight=weight;
    cne->normal=normal;
    return cne;
}
/**
 * Algorithm for heuristic  (not described explicitly in the paper)
 * It initializes a link from a cutpoint to a component from a given one.
 * Since they are used as normal and reversed, we need to clone them to avoid
 * changing already collected link.
 *
 * @param cne A base link to clone
 * @return a clone of the original link
 */
struct cc_node_edge * clone_cc_node_edge(struct cc_node_edge * cne){
    struct cc_node_edge * cne_n=(struct cc_node_edge * )malloc(sizeof(struct cc_node_edge ));
    cne_n->from=cne->from;
    cne_n->to=cne->to;
    cne_n->weight=cne->weight;
    cne_n->normal=cne->normal;
    return cne_n;
}

/**
 * Algorithm for heuristic  (not described explicitly in the paper)
 * Given a connected components list in graph and the list of articulation
 * point it creates a tree representing the inter-component traffic. It will be
 * used to remove redundant traffic from cutpoints in final centrality value.
 *
 * @param g A weighted graph. It needs to be connected or either you have to
 * call this function for every connected component (i.e. for every subgraph)
 * @param connected_components The list of the connected components inside
 * the graph (or either a subgraph of it)
 * @param is_articulation_point Array of boolean which tells if node with given
 * id is an articulation point
 * @return A tree representing the flow of routes
 */
struct list*  connected_components_to_tree(struct graph * g, struct list* connected_components, bool * is_articulation_point){
    struct list* tree_edges=(struct list*)malloc(sizeof(struct list));
    init_list(tree_edges);
    struct node_list * ccs_iterator;
    struct node_graph ** nodes=(struct node_graph **)malloc(sizeof( struct node_graph *)*g->nodes.size);
    uint8_t i;
    struct node_list * node_iterator=g->nodes.head;
    for(i=0;i<g->nodes.size;i++){
        nodes[i]=(struct node_graph *)node_iterator->content;
        node_iterator=node_iterator->next;
    }
    for(ccs_iterator=connected_components->head;ccs_iterator!=0;ccs_iterator=ccs_iterator->next){
        struct connected_component * cc= ( struct connected_component *)ccs_iterator->content;
        uint8_t art_points=0;
        struct node_graph * ng_cutpoint=0;
        int16_t index=-1;
        
        struct node_list *n;
        i=0;
        for(n=cc->g.nodes.head;n!=0;n=n->next){
            if(is_articulation_point[cc->mapping[i]]){
                uint8_t new_index=cc->mapping[i];
                ng_cutpoint=nodes[new_index];
                art_points++;
                index=i;
                struct cc_node_edge * cne=init_cc_node_edge(cc,nodes[new_index],cc->weights+i,true);
                enqueue_list(tree_edges,cne);
            }
            i++;
        }
        if(art_points==1){
            cc->cutpoint=ng_cutpoint;
            cc->cutpoint_index=index;
        }else{
            cc->cutpoint=0;
            cc->cutpoint_index=-1;
        }
    }
    free(nodes);
    return tree_edges;
}


//From http://algo.uni-konstanz.de/publications/pzedb-hsbcc-12.pdf
/**
 * Algorithm for heuristic
 * Computes the inter components (biconnected) traffic and removes the redundant
 * one from the final values. For each cutpoint every component value is
 * assessed in order to retrieve the traffic that is computed more than once on
 * it.
 * The implementation is slightly different from original, for two values, which
 * are
 *      size+=(v_num-(*cne_i->weight) - 1);
 * and
 *      int16_t size= 0;
 * in which first value should be 0 and the latter should be 1.
 *
 *
 * @param g A weighted graph. It needs to be connected or either you have to
 * call this function for every connected component (i.e. for every subgraph)
 * @param tree_edges The tree of the biconnected components, result of
 * connected_components_to_tree
 * @param v_num number of vertex in the given graph (or connected subgraph)
 */
void compute_component_tree_weights(struct graph * g, struct list* tree_edges,uint8_t v_num){
    struct list q;
    init_list(&q);
    struct node_list * edge_iterator;
    for(edge_iterator=tree_edges->head;edge_iterator!=0;edge_iterator=edge_iterator->next){
        struct cc_node_edge * cne=(struct cc_node_edge *)edge_iterator->content;
        if(cne->from->cutpoint!=0){
            cne=clone_cc_node_edge(cne);
            enqueue_list(&q,cne);
        }
    }
    while(!is_empty_list(&q)){
        struct cc_node_edge * cne=(struct cc_node_edge *)dequeue_list(&q);
        if(cne->normal){
            uint8_t size=cne->from->g.nodes.size-1;
            struct node_list * edge_iterator;
            for(edge_iterator=tree_edges->head;edge_iterator!=0;edge_iterator=edge_iterator->next){
                struct cc_node_edge * cne_i=(struct cc_node_edge*)edge_iterator->content;
                if(cne_i->from==cne->from&&(*cne_i->weight)!=-1&&cne_i->to!=cne->to){
                    size+=(v_num-(*cne_i->weight) - 1);
                }
            }
            (*cne->weight)=size;
            uint8_t count=0;
            struct cc_node_edge * t;
            for(edge_iterator=tree_edges->head;edge_iterator!=0;edge_iterator=edge_iterator->next){
                struct cc_node_edge * cne_i=(struct cc_node_edge*)edge_iterator->content;
                if((cne_i->to->name==cne->to->name)&&(*cne_i->weight)==-1){
                    count++;
                    t=cne_i;
                    
                }
            }
            if(count==1){
                t=clone_cc_node_edge(t);
                t->normal=false;
                enqueue_list(&q,t);
            }
        }else{
            uint8_t size= 0;
            struct node_list * edge_iterator;
            for(edge_iterator=tree_edges->head;edge_iterator!=0;edge_iterator=edge_iterator->next){
                struct cc_node_edge * cne_i=(struct cc_node_edge*)edge_iterator->content;
                if((cne_i->to->name==cne->to->name)&&(*cne_i->weight)!=-1&&cne_i->from!=cne->from){
                    size+=(*cne_i->weight);
                }
            }
            (*cne->weight)=v_num-1-size;
            uint8_t count=0;
            struct cc_node_edge * t;
            for(edge_iterator=tree_edges->head;edge_iterator!=0;edge_iterator=edge_iterator->next){
                struct cc_node_edge * cne_i=(struct cc_node_edge*)edge_iterator->content;
                if(cne_i->from==cne->from&&(*cne_i->weight)==-1){
                    count++;
                    t=cne_i;
                }
            }
            if(count==1){
                t=clone_cc_node_edge(t);
                t->normal=true;
                enqueue_list(&q,t);
            }
        }
        free(cne);
    }
}



/**
 * Algorithm for heuristic (not described explicitly in the paper)
 * Given a biconnected component in the graph it computes the traffic matrix and
 * finally returns the gross centrality (the redundancy of traffic is present).
 * This function runs concurrently on all biconnected components, if they are
 * more than 1.
 *
 * @param cc The connected component
 * @param node_num The total number of node in the whole graph (not only
 * the connected subgraph amount)
 * @param is_articulation_point Array of boolean which tells if node with given
 * id is an articulation point
 * @return The gross centrality of the biconnected component.
 */
float * compute_traffic_matrix_and_centrality(  struct connected_component * cc,uint8_t node_num,bool *is_articulation_point){
    uint8_t cc_node_num=cc->g.nodes.size;
    uint8_t i;
    uint8_t* art_point_val=(uint8_t *)malloc(sizeof(uint8_t)*cc_node_num);

    for(i=0;i<cc_node_num;i++){
        uint8_t new_i=cc->mapping[i];
        bool is_i_ap=is_articulation_point[new_i];
        if(is_i_ap){
            art_point_val[i]=(node_num-(cc->weights[i]));
        }else{
            art_point_val[i]=0;
        }
    }
    //float * ret_val=betweeness_brandes(&(cc->g),true,comm_matrix);
    float * ret_val=betweeness_brandes(&(cc->g),true,art_point_val);
    /*for(i=0;i<cc_node_num;i++){
     free(comm_matrix[i]);
     }
     free(comm_matrix);*/
    free(art_point_val);
    return ret_val;
}



/**
 *  Algorithm for heuristic (not described explicitly in the paper)
 *  It computes the centrality for every connected subgraph.
 *  Given the connected subgraph, it performs the tree decomposition of
 *  biconnected components. Then computes the BC_inter, i.e. the inter
 *  biconnected components traffic. Then concurrently, if possible, computes
 *  the traffic matrix for each component and the precise brandes value.
 *  It may run concurrently.
 *
 * @param g A weighted graph
 * @param connected_components List of connected components for a specific
 * connected subgraph
 * @param is_articulation_point Array of boolean which tells if node with given
 * id is an articulation point
 * @param bc The final centrality, an array whose indexes are node id
 * @param connected_component_index an array that specifies to which connected
 * component a node belongs
 * @param cc_node_num the number of nodes in the connected subgraph
 * @param cc_index an identifier (index) of the connected subgraph
 */
void compute_heuristic_wo_scale(struct graph * g,
        struct list * connected_components,
        bool * is_articulation_point,float * bc,
        int16_t * connected_component_index,uint8_t cc_node_num, uint8_t cc_index){
    uint8_t node_num=g->nodes.size;
    uint8_t i;
    node_num=cc_node_num;
    
    struct list* tree_edges=connected_components_to_tree(g,connected_components,is_articulation_point);
    compute_component_tree_weights(g,tree_edges,node_num);
    i=0;
    struct node_list * graph_iterator;
    for(graph_iterator=g->nodes.head;graph_iterator!=0;graph_iterator=graph_iterator->next){
        struct node_graph * n= ( struct node_graph *)graph_iterator->content;
        if(connected_component_index[i]==cc_index){
            if(is_articulation_point[i]){
                struct node_list * tree_edge_iterator;
                float weight_sum=0;//-1;
                for(tree_edge_iterator=tree_edges->head;tree_edge_iterator!=0;tree_edge_iterator=tree_edge_iterator->next){
                    struct cc_node_edge * cne=(struct cc_node_edge *)tree_edge_iterator->content;
                    if(cne->to==n){
                        //give that DBV)+1+DBV(=|V|, BC^inter = (|V|-1+DBV( )*DBV(
                        // weight_sum+=tree_weights[cne->index]*(node_num-1-tree_weights[cne->index]);
                        // weight_sum+=(*cne->weight)*(node_num-1-(*cne->weight));
                        weight_sum+=(*cne->weight)*(node_num-1-(*cne->weight));
                    } 
                }
                bc[i]-=weight_sum;
            }
        }
        i++;
    }
    
    struct node_list * ccs_iterator;
        for(ccs_iterator=connected_components->head;ccs_iterator!=0;ccs_iterator=ccs_iterator->next){
            struct connected_component * cc= ( struct connected_component *)ccs_iterator->content;
            float * partial=compute_traffic_matrix_and_centrality( cc, node_num,is_articulation_point);
            uint8_t i;
            for(i=0;i<cc->g.nodes.size;i++){
                bc[cc->mapping[i]] += partial[i];
            }
            free(partial);
        }
    
    while(!is_empty_list(tree_edges)){
        struct cc_node_edge * cne=( struct cc_node_edge *)dequeue_list(tree_edges);
        free(cne);
    }
    free(tree_edges);
    while(!is_empty_list(connected_components)){
        struct connected_component * cc=(struct connected_component *)dequeue_list(connected_components);
        free_graph(&(cc->g));
        free(cc->mapping);
        free(cc->weights);
        free(cc);
    }
    free(connected_components);
}




/**
 * Algorithm for heuristic
 * Wrapper for all function above. It returns the correct centrality, it is
 * semantically the same as betweeness_brandes.
 *
 * @param g A weighted graph
 * @param recursive whether we want to use the recursive or iterative approach
 * @return  An array with betwenness centrality for each node
 */
float * betwenness_heuristic(struct graph * g, bool recursive){
    uint8_t node_num=g->nodes.size;
    bool * is_articulation_point=( bool * )malloc(sizeof(bool)*node_num);
    int16_t * connected_component_indexes=( int16_t * )malloc(sizeof(int16_t)*node_num);
    float * ret_val=(float *)malloc(sizeof(float)*node_num);
    uint8_t i;
    for(i=0;i<node_num;i++){
        ret_val[i]=0;
        connected_component_indexes[i]=-1;
    }
    struct list* connected_components_subgraphs;
	    if(recursive){
		connected_components_subgraphs=tarjan_rec_undir(g,is_articulation_point,connected_component_indexes);
	    }else {
		connected_components_subgraphs=tarjan_iter_undir(g,is_articulation_point,connected_component_indexes);
	}
;
   
	 uint8_t connected_component_index=0;
	uint8_t cc_num=connected_components_subgraphs->size;
        // struct sub_graph * sg=(struct sub_graph *)dequeue_list(connected_components_subgraphs);
            struct node_list * subgraph_iterator=connected_components_subgraphs->head;
            for(;subgraph_iterator!=0;subgraph_iterator=subgraph_iterator->next){
                struct sub_graph * sg=(struct sub_graph *)subgraph_iterator->content;
                compute_heuristic_wo_scale(g,&(sg->connected_components),
                        is_articulation_point,ret_val,connected_component_indexes,
                        sg->size,connected_component_index++);
            }

    
    if(node_num>2){
        float scale=1/(((float)(node_num-1))*((float)(node_num-2)));
        for( i =0;i<node_num;i++){
            ret_val[i]*=scale;
            // ret_val[i]=round_decimal(ret_val[i]);
            
        }
    }

    
    
    clear_list(connected_components_subgraphs);
    free(connected_components_subgraphs);
    free(is_articulation_point);
    free(connected_component_indexes);

    return ret_val;
}

