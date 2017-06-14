/* 
 * File:   list.h
 * Author: mb03
 *
 * Created on December 6, 2016, 6:41 PM
 */


#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
    /**
     * Structs and functions used to represent a generic list and a priority 
     * queue. 
     * The list works both with LIFO and FIFO policies.
     * The priority queue offers all operation needed for dijkstra algorithm.
     * The underlying implementation for both is the float linked list.
     * Further detail in list.c
     */
    
    struct node_list {
        void * content;
        struct node_list * next;
        struct node_list * prev;
    };
    
    
    struct list {
        struct node_list * head;
        struct node_list * tail;
        uint8_t size;
    };
    
    struct node_priority_queue {
        void * content;
        struct node_priority_queue * next;
        struct node_priority_queue * prev;
        float value;
    };
    
    struct priority_queue {
        struct node_priority_queue * head;
        struct node_priority_queue * tail;
        uint8_t size;
    };
    
    void init_list(struct list * q);
    void enqueue_list(struct list * q,void * item);
    void * dequeue_list(struct list * q);
    void * peek_last_list(struct list * q);
    void * peek_first_list(struct list * q);
    void * pop_list(struct list * q);
    void print_list(struct list * q);
    void clear_list(struct list * q);
    bool is_empty_list(struct list * q);
    
    void init_priority_queue(struct priority_queue * q);
    void insert_priority_queue(struct priority_queue * q,void * item, float val);
    void insert_or_update_priority_queue(struct priority_queue * q,void * item, float val);
    void * dequeue_priority_queue(struct priority_queue * q);
    void print_priority_queue(struct priority_queue * q);
    bool is_empty_priority_queue(struct priority_queue * q);
    
#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

