/* 
 * File:   graph.h
 * Author: mb03
 *
 * Created on December 7, 2016, 3:48 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "list.h" 
#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
    /**
     * Structs and functions used to represent a graph. Further detail in grap.c
     */
    
    struct node_graph {
        struct list neighbours;
        uint8_t name;
        uint8_t node_graph_id;
    }; 
    struct edge_graph {
        struct node_graph * to;
        float value;
        
    }; 
    struct graph {
        struct list nodes;
    };
    
    void init_graph(struct graph * g);
    void add_edge_graph(struct graph * g,  uint8_t name_from,  uint8_t name_to, float value, bool directed);
    void add_edge_graph_return_node_indexes(struct graph * g,  uint8_t name_from,  uint8_t name_to, float value, bool directed,uint8_t  * nodefrom, uint8_t * nodeto);
    void free_graph(struct graph * g);
    

    
    
#ifdef __cplusplus
}
#endif

#endif /* GRAPH_H */

