/* 
 * File:   biconnected.h
 * Author: mb03
 *
 * Created on January 18, 2017, 12:19 PM
 */

#ifndef BICONNECTED_H
#define BICONNECTED_H
#include "graph/graph.h"
#ifdef __cplusplus
extern "C" {
#endif
    struct graph;
    
    struct connected_component{
        struct graph g;
        uint8_t * mapping;
        int16_t * weights;
        struct node_graph * cutpoint;
        int16_t cutpoint_index;
    };
    
    struct sub_graph{
        struct list connected_components;
        uint8_t size;
    };
    
    //These function returns the list of list of connected components
    //i.e. a list of connected components for each connected subgraph
    struct list*  tarjan_rec_undir(struct graph * g, 
            bool * is_articulation_point, int16_t * component_indexes);
    struct list*  tarjan_iter_undir(struct graph * g, 
            bool * is_articulation_point, int16_t * component_indexes);
    
    
#ifdef __cplusplus
}
#endif

#endif /* BICONNECTED_H */

