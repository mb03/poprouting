#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "brandes.h"
#include "local_exe.h"
//#include <ti/sysbios/knl/Clock.h>
#include <sys/time.h>
extern bool recursive;

void create_graph(struct graph * g,int choice){
    switch (choice) {
        case 0:
            add_edge_graph(g,2,8,1.0, 0);
            add_edge_graph(g,2,4,0.98, 0);
            add_edge_graph(g,2,14,1.0, 0);
            add_edge_graph(g,2,7,1.0, 0);
            add_edge_graph(g,3,3,1.0, 0);
            add_edge_graph(g,4,8,0.86, 0);
            add_edge_graph(g,4,4,0.96, 0);
            add_edge_graph(g,4,6,0.86, 0);
            add_edge_graph(g,4,7,0.94, 0);
            add_edge_graph(g,5,8,0.98, 0);
            add_edge_graph(g,5,9,0.92, 0);
            add_edge_graph(g,5,5,0.94, 0);
            add_edge_graph(g,5,7,0.98, 0);
            add_edge_graph(g,6,8,1.0, 0);
            add_edge_graph(g,6,9,0.94, 0);
            add_edge_graph(g,6,6,0.98, 0);
            add_edge_graph(g,7,9,1.0, 0);
            add_edge_graph(g,7,7,1.0, 0);
            add_edge_graph(g,8,8,1.0, 0);
            add_edge_graph(g,9,9,1.0, 0);
            add_edge_graph(g,13,15,0.94, 0);
            add_edge_graph(g,14,14,1.0, 0);
            add_edge_graph(g,16,16,1.0, 0);
            add_edge_graph(g,17,17,1.0, 0);
            add_edge_graph(g,19,24,1.0, 0);
            add_edge_graph(g,19,26,0.94, 0);
            add_edge_graph(g,19,19,1.0, 0);
            add_edge_graph(g,19,21,0.94, 0);
            add_edge_graph(g,20,26,0.98, 0);
            add_edge_graph(g,20,20,1.0, 0);
            add_edge_graph(g,20,23,1.0, 0);
            add_edge_graph(g,21,24,0.84, 0);
            add_edge_graph(g,21,25,1.0, 0);
            add_edge_graph(g,21,23,1.0, 0);
            add_edge_graph(g,22,22,0.98, 0);
            add_edge_graph(g,23,23,0.98, 0);
            add_edge_graph(g,24,24,1.0, 0);
            add_edge_graph(g,24,26,0.98, 0);
            add_edge_graph(g,25,25,0.98, 0);
            add_edge_graph(g,26,26,1.0, 0);
            add_edge_graph(g,28,33,1.0, 0);
            add_edge_graph(g,28,28,1.0, 0);
            add_edge_graph(g,28,30,1.0, 0);
            add_edge_graph(g,29,29,1.0, 0);
            add_edge_graph(g,30,32,0.8, 0);
            add_edge_graph(g,30,30,0.94, 0);
            add_edge_graph(g,31,33,0.96, 0);
            add_edge_graph(g,31,31,0.9, 0);
            add_edge_graph(g,32,32,1.0, 0);
            add_edge_graph(g,34,34,0.94, 0);
            add_edge_graph(g,36,36,0.92, 0);
            add_edge_graph(g,36,38,0.8, 0);
            add_edge_graph(g,37,37,1.0, 0);
            add_edge_graph(g,37,39,0.94, 0);
            add_edge_graph(g,38,42,1.0, 0);
            add_edge_graph(g,38,38,1.0, 0);
            add_edge_graph(g,39,39,1.0, 0);
            add_edge_graph(g,42,42,0.94, 0);
            add_edge_graph(g,43,46,0.98, 0);
            add_edge_graph(g,44,48,1.0, 0);
            add_edge_graph(g,44,44,0.98, 0);
            add_edge_graph(g,44,47,0.88, 0);
            add_edge_graph(g,45,45,0.98, 0);
            add_edge_graph(g,45,47,1.0, 0);
            add_edge_graph(g,46,48,1.0, 0);
            add_edge_graph(g,46,46,0.98, 0);
            add_edge_graph(g,47,47,0.98, 0);
            add_edge_graph(g,49,49,1.0, 0);
            break;
        case 1:
            add_edge_graph(g,3,16,0.958333333333333, 0);
            add_edge_graph(g,3,18,0.958333333333333, 0);
            add_edge_graph(g,5,19,0.916666666666667, 0);
            add_edge_graph(g,6,16,0.958333333333333, 0);
            add_edge_graph(g,6,12,0.875, 0);
            add_edge_graph(g,6,13,0.8125, 0);
            add_edge_graph(g,7,15,1.0, 0);
            add_edge_graph(g,7,14,1.0, 0);
            add_edge_graph(g,7,7,1.0, 0);
            add_edge_graph(g,9,9,0.895833333333333, 0);
            add_edge_graph(g,10,10,0.958333333333333, 0);
            add_edge_graph(g,12,12,1.0, 0);
            add_edge_graph(g,12,14,1.0, 0);
            add_edge_graph(g,13,13,0.916666666666667, 0);
            add_edge_graph(g,14,18,0.8125, 0);
            add_edge_graph(g,14,14,1.0, 0);
            add_edge_graph(g,15,15,1.0, 0);
            add_edge_graph(g,16,19,1.0, 0);
            add_edge_graph(g,17,33,1.0, 0);
            add_edge_graph(g,22,33,0.916666666666667, 0);
            add_edge_graph(g,25,33,1.0, 0);
            add_edge_graph(g,31,33,1.0, 0);
            add_edge_graph(g,31,31,1.0, 0);
            add_edge_graph(g,32,34,1.0, 0);
            add_edge_graph(g,33,33,1.0, 0);
            add_edge_graph(g,34,34,1.0, 0);
            add_edge_graph(g,36,44,0.875, 0);
            add_edge_graph(g,36,42,0.979166666666667, 0);
            add_edge_graph(g,36,36,1.0, 0);
            add_edge_graph(g,36,45,0.875, 0);
            add_edge_graph(g,36,46,0.9375, 0);
            add_edge_graph(g,37,42,1.0, 0);
            add_edge_graph(g,39,44,1.0, 0);
            add_edge_graph(g,40,42,1.0, 0);
            add_edge_graph(g,40,43,0.979166666666667, 0);
            add_edge_graph(g,40,47,0.833333333333333, 0);
            add_edge_graph(g,41,41,0.895833333333333, 0);
            add_edge_graph(g,41,45,1.0, 0);
            add_edge_graph(g,42,44,0.916666666666667, 0);
            add_edge_graph(g,42,48,0.9375, 0);
            add_edge_graph(g,43,48,1.0, 0);
            add_edge_graph(g,43,43,1.0, 0);
            add_edge_graph(g,43,45,1.0, 0);
            add_edge_graph(g,43,47,0.9375, 0);
            add_edge_graph(g,44,44,0.979166666666667, 0);
            add_edge_graph(g,44,46,1.0, 0);
            add_edge_graph(g,44,47,1.0, 0);
            add_edge_graph(g,45,49,0.916666666666667, 0);
            add_edge_graph(g,45,45,0.979166666666667, 0);
            add_edge_graph(g,45,47,0.958333333333333, 0);
            add_edge_graph(g,46,48,1.0, 0);
            add_edge_graph(g,46,46,0.979166666666667, 0);
            add_edge_graph(g,46,49,0.895833333333333, 0);
            add_edge_graph(g,47,47,0.895833333333333, 0);
            add_edge_graph(g,49,49,1.0, 0);
            add_edge_graph(g,51,51,0.916666666666667, 0);
            add_edge_graph(g,53,60,0.979166666666667, 0);
            add_edge_graph(g,53,68,1.0, 0);
            add_edge_graph(g,55,57,0.895833333333333, 0);
            add_edge_graph(g,55,58,0.854166666666667, 0);
            add_edge_graph(g,56,64,1.0, 0);
            add_edge_graph(g,56,65,0.833333333333333, 0);
            add_edge_graph(g,56,66,0.958333333333333, 0);
            add_edge_graph(g,56,63,1.0, 0);
            add_edge_graph(g,56,56,1.0, 0);
            add_edge_graph(g,57,64,0.979166666666667, 0);
            add_edge_graph(g,57,66,0.895833333333333, 0);
            add_edge_graph(g,58,58,1.0, 0);
            add_edge_graph(g,58,60,0.979166666666667, 0);
            add_edge_graph(g,59,59,0.979166666666667, 0);
            add_edge_graph(g,63,66,1.0, 0);
            add_edge_graph(g,63,63,1.0, 0);
            add_edge_graph(g,64,64,1.0, 0);
            add_edge_graph(g,66,66,0.958333333333333, 0);
            add_edge_graph(g,73,80,1.0, 0);
            add_edge_graph(g,73,78,1.0, 0);
            add_edge_graph(g,74,83,1.0, 0);
            add_edge_graph(g,75,84,1.0, 0);
            add_edge_graph(g,75,87,1.0, 0);
            add_edge_graph(g,76,83,0.854166666666667, 0);
            add_edge_graph(g,76,86,1.0, 0);
            add_edge_graph(g,78,80,1.0, 0);
            add_edge_graph(g,78,78,0.9375, 0);
            add_edge_graph(g,79,81,1.0, 0);
            add_edge_graph(g,79,79,1.0, 0);
            add_edge_graph(g,80,80,1.0, 0);
            add_edge_graph(g,81,81,1.0, 0);
            add_edge_graph(g,83,87,0.958333333333333, 0);
            break;
        case 2:
            add_edge_graph(g,64,56,1.0, 0);
            add_edge_graph(g,64,64,0.938775510204082, 0);
            add_edge_graph(g,64,66,0.816326530612245, 0);
            add_edge_graph(g,65,63,0.857142857142857, 0);
            add_edge_graph(g,66,63,0.857142857142857, 0);
            add_edge_graph(g,8,14,0.96, 0);
            add_edge_graph(g,9,9,0.96, 0);
            add_edge_graph(g,10,10,1.0, 0);
            add_edge_graph(g,75,84,0.979591836734694, 0);
            add_edge_graph(g,75,87,0.877551020408163, 0);
            add_edge_graph(g,76,83,1.0, 0);
            add_edge_graph(g,76,86,1.0, 0);
            add_edge_graph(g,13,13,0.9, 0);
            add_edge_graph(g,77,77,0.959183673469388, 0);
            add_edge_graph(g,80,73,0.918367346938776, 0);
            add_edge_graph(g,81,81,1.0, 0);
            add_edge_graph(g,78,73,0.979591836734694, 0);
            add_edge_graph(g,89,85,0.897959183673469, 0);
            add_edge_graph(g,26,42,0.82, 0);
            add_edge_graph(g,79,79,0.959183673469388, 0);
            add_edge_graph(g,31,31,0.92, 0);
            add_edge_graph(g,32,32,0.92, 0);
            add_edge_graph(g,33,33,0.96, 0);
            add_edge_graph(g,36,36,0.98, 0);
            add_edge_graph(g,36,46,0.98, 0);
            add_edge_graph(g,39,44,0.94, 0);
            add_edge_graph(g,41,49,1.0, 0);
            add_edge_graph(g,41,45,1.0, 0);
            add_edge_graph(g,42,48,0.96, 0);
            add_edge_graph(g,42,44,0.86, 0);
            add_edge_graph(g,44,44,0.92, 0);
            add_edge_graph(g,44,46,1.0, 0);
            add_edge_graph(g,45,45,0.98, 0);
            add_edge_graph(g,46,48,1.0, 0);
            add_edge_graph(g,49,49,1.0, 0);
            add_edge_graph(g,51,51,1.0, 0);
            add_edge_graph(g,73,73,0.979591836734694, 0);
            add_edge_graph(g,56,56,1.0, 0);
            add_edge_graph(g,56,63,1.0, 0);
            add_edge_graph(g,58,58,0.938775510204082, 0);
            add_edge_graph(g,59,59,0.959183673469388, 0);
            add_edge_graph(g,63,63,0.979591836734694, 0);
            break;
        case 3:
            
            add_edge_graph(g,2,2,1.0, 0);
            add_edge_graph(g,2,4,1.0, 0);
            add_edge_graph(g,2,5,1.0, 0);
            add_edge_graph(g,2,7,1.0, 0);
            add_edge_graph(g,2,8,1.0, 0);
            add_edge_graph(g,2,9,1.0, 0);
            add_edge_graph(g,2,10,1.0, 0);
            add_edge_graph(g,2,13,1.0, 0);
            add_edge_graph(g,2,14,1.0, 0);
            add_edge_graph(g,2,15,1.0, 0);
            add_edge_graph(g,3,49,0.98, 0);
            add_edge_graph(g,3,3,0.98, 0);
            add_edge_graph(g,3,7,0.98, 0);
            add_edge_graph(g,3,8,0.98, 0);
            add_edge_graph(g,3,9,0.98, 0);
            add_edge_graph(g,3,14,0.98, 0);
            add_edge_graph(g,4,8,1.0, 0);
            add_edge_graph(g,4,4,1.0, 0);
            add_edge_graph(g,4,6,1.0, 0);
            add_edge_graph(g,4,7,1.0, 0);
            add_edge_graph(g,5,8,1.0, 0);
            add_edge_graph(g,5,9,1.0, 0);
            add_edge_graph(g,5,5,1.0, 0);
            add_edge_graph(g,5,7,1.0, 0);
            add_edge_graph(g,6,8,1.0, 0);
            add_edge_graph(g,6,9,1.0, 0);
            add_edge_graph(g,6,14,0.9, 0);
            add_edge_graph(g,6,6,1.0, 0);
            add_edge_graph(g,7,7,1.0, 0);
            add_edge_graph(g,7,9,1.0, 0);
            add_edge_graph(g,7,13,1.0, 0);
            add_edge_graph(g,7,14,1.0, 0);
            add_edge_graph(g,8,8,1.0, 0);
            add_edge_graph(g,8,14,1.0, 0);
            add_edge_graph(g,9,9,1.0, 0);
            add_edge_graph(g,9,14,1.0, 0);
            add_edge_graph(g,10,17,0.94, 0);
            add_edge_graph(g,10,13,1.0, 0);
            add_edge_graph(g,10,14,1.0, 0);
            add_edge_graph(g,11,40,1.0, 0);
            add_edge_graph(g,12,41,1.0, 0);
            add_edge_graph(g,12,27,1.0, 0);
            add_edge_graph(g,13,16,1.0, 0);
            add_edge_graph(g,13,17,1.0, 0);
            add_edge_graph(g,13,18,1.0, 0);
            add_edge_graph(g,13,13,1.0, 0);
            add_edge_graph(g,13,15,1.0, 0);
            add_edge_graph(g,14,16,1.0, 0);
            add_edge_graph(g,14,17,1.0, 0);
            add_edge_graph(g,14,14,1.0, 0);
            add_edge_graph(g,15,17,1.0, 0);
            add_edge_graph(g,15,15,1.0, 0);
            add_edge_graph(g,16,16,1.0, 0);
            add_edge_graph(g,17,17,1.0, 0);
            add_edge_graph(g,17,26,1.0, 0);
            add_edge_graph(g,18,25,1.0, 0);
            add_edge_graph(g,18,26,1.0, 0);
            add_edge_graph(g,19,19,1.0, 0);
            add_edge_graph(g,19,21,1.0, 0);
            add_edge_graph(g,19,22,1.0, 0);
            add_edge_graph(g,19,23,1.0, 0);
            add_edge_graph(g,19,24,1.0, 0);
            add_edge_graph(g,19,25,1.0, 0);
            add_edge_graph(g,19,26,1.0, 0);
            add_edge_graph(g,20,24,1.0, 0);
            add_edge_graph(g,20,26,1.0, 0);
            add_edge_graph(g,20,20,1.0, 0);
            add_edge_graph(g,20,22,1.0, 0);
            add_edge_graph(g,20,23,1.0, 0);
            add_edge_graph(g,21,25,1.0, 0);
            add_edge_graph(g,21,26,1.0, 0);
            add_edge_graph(g,21,21,0.98, 0);
            add_edge_graph(g,21,23,0.98, 0);
            add_edge_graph(g,22,34,1.0, 0);
            add_edge_graph(g,22,22,0.98, 0);
            add_edge_graph(g,22,24,1.0, 0);
            add_edge_graph(g,22,25,0.98, 0);
            add_edge_graph(g,23,27,1.0, 0);
            add_edge_graph(g,23,23,0.94, 0);
            add_edge_graph(g,24,24,1.0, 0);
            add_edge_graph(g,24,26,1.0, 0);
            add_edge_graph(g,25,25,1.0, 0);
            add_edge_graph(g,26,26,1.0, 0);
            add_edge_graph(g,28,32,1.0, 0);
            add_edge_graph(g,28,33,1.0, 0);
            add_edge_graph(g,28,34,1.0, 0);
            add_edge_graph(g,28,28,1.0, 0);
            add_edge_graph(g,28,30,1.0, 0);
            add_edge_graph(g,28,31,1.0, 0);
            add_edge_graph(g,29,32,1.0, 0);
            add_edge_graph(g,29,33,1.0, 0);
            add_edge_graph(g,29,34,1.0, 0);
            add_edge_graph(g,29,29,1.0, 0);
            add_edge_graph(g,29,31,1.0, 0);
            add_edge_graph(g,30,32,1.0, 0);
            add_edge_graph(g,30,33,1.0, 0);
            add_edge_graph(g,30,34,0.82, 0);
            add_edge_graph(g,30,37,0.86, 0);
            add_edge_graph(g,30,30,1.0, 0);
            add_edge_graph(g,31,33,0.98, 0);
            add_edge_graph(g,31,36,0.88, 0);
            add_edge_graph(g,31,37,0.86, 0);
            add_edge_graph(g,31,31,0.98, 0);
            add_edge_graph(g,32,32,1.0, 0);
            add_edge_graph(g,32,35,1.0, 0);
            add_edge_graph(g,32,36,1.0, 0);
            add_edge_graph(g,32,37,1.0, 0);
            add_edge_graph(g,32,38,1.0, 0);
            add_edge_graph(g,32,42,1.0, 0);
            add_edge_graph(g,33,33,1.0, 0);
            add_edge_graph(g,33,35,1.0, 0);
            add_edge_graph(g,34,34,1.0, 0);
            add_edge_graph(g,36,36,1.0, 0);
            add_edge_graph(g,36,38,1.0, 0);
            add_edge_graph(g,36,39,0.86, 0);
            add_edge_graph(g,36,42,0.84, 0);
            add_edge_graph(g,37,37,1.0, 0);
            add_edge_graph(g,37,39,1.0, 0);
            add_edge_graph(g,37,42,0.92, 0);
            add_edge_graph(g,37,46,0.92, 0);
            add_edge_graph(g,38,42,1.0, 0);
            add_edge_graph(g,38,38,1.0, 0);
            add_edge_graph(g,39,42,0.92, 0);
            add_edge_graph(g,39,39,1.0, 0);
            add_edge_graph(g,42,42,1.0, 0);
            add_edge_graph(g,42,46,1.0, 0);
            add_edge_graph(g,43,45,1.0, 0);
            add_edge_graph(g,43,46,0.9, 0);
            add_edge_graph(g,44,48,0.98, 0);
            add_edge_graph(g,44,49,1.0, 0);
            add_edge_graph(g,44,44,0.98, 0);
            add_edge_graph(g,44,46,0.86, 0);
            add_edge_graph(g,44,47,0.88, 0);
            add_edge_graph(g,45,48,0.98, 0);
            add_edge_graph(g,45,45,0.98, 0);
            add_edge_graph(g,45,47,0.98, 0);
            add_edge_graph(g,46,48,1.0, 0);
            add_edge_graph(g,46,49,1.0, 0);
            add_edge_graph(g,46,46,1.0, 0);
            add_edge_graph(g,47,47,1.0, 0);
            add_edge_graph(g,48,48,1.0, 0);
            add_edge_graph(g,49,49,1.0, 0);
            break;
        case 4:
            add_edge_graph(g,0,1,1.0, 0);
            add_edge_graph(g,0,2,1.0, 0);
            add_edge_graph(g,0,3,1.0, 0);
            add_edge_graph(g,0,4,1.0, 0);
            add_edge_graph(g,0,5,1.0, 0);
            add_edge_graph(g,0,6,1.0, 0);
            add_edge_graph(g,0,7,1.0, 0);
            add_edge_graph(g,0,8,1.0, 0);
            add_edge_graph(g,0,9,1.0, 0);
            add_edge_graph(g,0,10,1.0, 0);
            add_edge_graph(g,0,11,1.0, 0);
            add_edge_graph(g,0,12,1.0, 0);
            add_edge_graph(g,0,13,1.0, 0);
            add_edge_graph(g,0,14,1.0, 0);
            add_edge_graph(g,0,15,1.0, 0);
            add_edge_graph(g,0,16,1.0, 0);
            add_edge_graph(g,0,17,1.0, 0);
            add_edge_graph(g,0,18,1.0, 0);
            add_edge_graph(g,0,19,1.0, 0);
            add_edge_graph(g,0,20,1.0, 0);
            add_edge_graph(g,0,21,1.0, 0);
            add_edge_graph(g,0,22,1.0, 0);
            add_edge_graph(g,0,23,1.0, 0);
            add_edge_graph(g,0,24,1.0, 0);
            add_edge_graph(g,0,25,1.0, 0);
            add_edge_graph(g,0,26,1.0, 0);
            add_edge_graph(g,0,27,1.0, 0);
            add_edge_graph(g,0,28,1.0, 0);
            add_edge_graph(g,0,29,1.0, 0);
            add_edge_graph(g,0,30,1.0, 0);
            add_edge_graph(g,0,31,1.0, 0);
            add_edge_graph(g,0,32,1.0, 0);
            add_edge_graph(g,0,33,1.0, 0);
            break;
        case 5:
            add_edge_graph(g,0,1,1.0, 0);
                      add_edge_graph(g,1,2,1.0, 0);
                      add_edge_graph(g,2,3,1.0, 0);
                      add_edge_graph(g,3,4,1.0, 0);
                      add_edge_graph(g,4,5,1.0, 0);
                      add_edge_graph(g,5,6,1.0, 0);
                      add_edge_graph(g,6,7,1.0, 0);
                      add_edge_graph(g,7,8,1.0, 0);
                      add_edge_graph(g,8,9,1.0, 0);
                      add_edge_graph(g,9,10,1.0, 0);
                      add_edge_graph(g,10,11,1.0, 0);
                      add_edge_graph(g,11,12,1.0, 0);
                      add_edge_graph(g,12,13,1.0, 0);
                      add_edge_graph(g,13,14,1.0, 0);
                      add_edge_graph(g,14,15,1.0, 0);
                      add_edge_graph(g,15,16,1.0, 0);
                      add_edge_graph(g,16,17,1.0, 0);
                      add_edge_graph(g,17,18,1.0, 0);
                      add_edge_graph(g,18,19,1.0, 0);
                      add_edge_graph(g,19,0,1.0, 0);
                                add_edge_graph(g,0,20,1.0, 0);
                                add_edge_graph(g,20,21,1.0, 0);
                                add_edge_graph(g,22,21,1.0, 0);
                                add_edge_graph(g,22,23,1.0, 0);
                                add_edge_graph(g,23,24,1.0, 0);
                                add_edge_graph(g,24,25,1.0, 0);
                                add_edge_graph(g,25,26,1.0, 0);
                                add_edge_graph(g,26,27,1.0, 0);
                                add_edge_graph(g,27,28,1.0, 0);
                                add_edge_graph(g,28,29,1.0, 0);
                                add_edge_graph(g,29,30,1.0, 0);
                                add_edge_graph(g,30,31,1.0, 0);
                                add_edge_graph(g,31,32,1.0, 0);
                                add_edge_graph(g,32,33,1.0, 0);
                                add_edge_graph(g,33,34,1.0, 0);
                                add_edge_graph(g,34,35,1.0, 0);
                                add_edge_graph(g,35,36,1.0, 0);
                                add_edge_graph(g,36,37,1.0, 0);
                                add_edge_graph(g,37,38,1.0, 0);
                                add_edge_graph(g,38,20,1.0, 0);
            break;
        case 6:
            add_edge_graph(g,1,2,1.0,0);
            add_edge_graph(g,2,3,1.0,0);
            add_edge_graph(g,3,4,1.0,0);
            add_edge_graph(g,4,5,1.0,0);
            add_edge_graph(g,5,6,1.0,0);
            add_edge_graph(g,6,1,1.0,0);
            add_edge_graph(g,0,1,1.0,0);
            add_edge_graph(g,7,8,1.0,0);
            add_edge_graph(g,8,9,1.0,0);
            add_edge_graph(g,9,10,1.0,0);
            add_edge_graph(g,10,11,1.0,0);
            add_edge_graph(g,11,12,1.0,0);
            add_edge_graph(g,12,7,1.0,0);
            add_edge_graph(g,0,7,1.0,0);
            add_edge_graph(g,13,14,1.0,0);
            add_edge_graph(g,14,15,1.0,0);
            add_edge_graph(g,15,16,1.0,0);
            add_edge_graph(g,16,17,1.0,0);
            add_edge_graph(g,17,18,1.0,0);
            add_edge_graph(g,18,13,1.0,0);
            add_edge_graph(g,0,13,1.0,0);
            add_edge_graph(g,19,20,1.0,0);
            add_edge_graph(g,20,21,1.0,0);
            add_edge_graph(g,21,22,1.0,0);
            add_edge_graph(g,22,23,1.0,0);
            add_edge_graph(g,23,24,1.0,0);
            add_edge_graph(g,24,19,1.0,0);
            add_edge_graph(g,0,19,1.0,0);
            add_edge_graph(g,25,26,1.0,0);
            add_edge_graph(g,26,27,1.0,0);
            add_edge_graph(g,27,28,1.0,0);
            add_edge_graph(g,28,29,1.0,0);
            add_edge_graph(g,29,30,1.0,0);
            add_edge_graph(g,30,25,1.0,0);
            add_edge_graph(g,0,25,1.0,0);
            break;
    }
    printf("\ncreated\n");
}
/*
int run_test(struct graph * g,bool heuristic,bool rec) {
    recursive=rec;
    Uint32 time=0;
    if(heuristic){
        time=Clock_getTicks();
        betwenness_heuristic(g,recursive);
        time=Clock_getTicks()-time;
    }else{
        time=Clock_getTicks();
        betweeness_brandes(g,true,0);
        time=Clock_getTicks()-time;
    }
    return (int)time;
}

void run_tests(bool heu,bool rec, struct graph *g){
    float var, mean;
    float t=0;
    int i=0;
    float vals[5];
    for(;i<5;i++){
        float tmp=(float)run_test(g,heu,rec);
        t+=tmp;
        vals[i]=tmp;
        printf("Exe %d: %f\n",i,tmp);
    }
    mean=t/5;
    float v=0;
    i=0;
    for(;i<5;i++){
        float tmp=mean-vals[i];
        v+=tmp*tmp;
    }
    var=v/5;
    printf("mean\t%f+-(%f)\n",mean,var);

}

void battery_test(uint8_t choice) {
    struct graph g;
    init_graph(&g);

    switch (choice) {
          case 0: printf("fbk_c18_p15.txt");
              break;
          case 1: printf("indriya_c26_p31.txt");
              break;
          case 2: printf("indriya_c26_p07.txt");
              break;
          case 3: printf("fbk_c26_p31.txt");
              break;
          default:printf("synthetic");break;
    }
   
    create_graph(&g,choice);
   // run_tests(0,0, &g);
    //run_tests(1,1, &g);
    run_tests(1,0, &g);
    free_graph(&g);
}*/
/*
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/BIOS.h>
static inline Float CLK_cpuCyclesPerLtime()
{
    xdc_runtime_Types_FreqHz freq1;

    ti_sysbios_BIOS_getCpuFreq(&freq1);
    return ((((float)freq1.lo / 1000) * (float)ti_sysbios_knl_Clock_tickPeriod) / 1000);
}

void v(){
    UInt32 time1 = ti_sysbios_knl_Clock_getTicks();
       int j;
       for(j=0;j<10000000;j++){}
       UInt32 time2 = ti_sysbios_knl_Clock_getTicks();
       UInt32 CPUcycles = (time2 - time1) * CLK_cpuCyclesPerLtime();

       printf("%ld %ld\n", time1,time2);
       printf("System time in clk0Fxn = %lu\n", (ULong)CPUcycles);

}*/

//local tests to infer where the heuristic performs better with very low nodes 
//count (10-150)
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int local_run_test(struct graph * g,bool heuristic,bool rec) {
    recursive=rec;
    long time=0;
    if(heuristic){
        time = getMicrotime();
        betwenness_heuristic(g,recursive);
        time = getMicrotime()-time;
    }else{
        time = getMicrotime();
        betweeness_brandes(g,true,0);
        time = getMicrotime()-time;
    }
    return (int)time;
}

void local_run_tests(bool heu,bool rec, struct graph *g){
    float var, mean;
    float t=0;
    int i=0;
    float vals[10];
    for(;i<10;i++){
        float tmp=(float)local_run_test(g,heu,rec);
        t+=tmp;
        vals[i]=tmp;
    }
    mean=t/10;
    float v=0;
    i=0;
    for(;i<10;i++){
        float tmp=mean-vals[i];
        v+=tmp*tmp;
    }
    var=v/10;
    if(heu){
    printf("heuristic\t");
    }else{
    printf("brandes\t\t");
    }
    printf("mean\t%f+-(%f)\n",mean,var);

}

int main(int argc, char** argv) {
    if (argc<2){
        printf("Missing args\n");
    }
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    struct graph g;
    init_graph(&g);

    while ((read = getline(&line, &len, fp)) != -1) {
        int s,t;
        sscanf( line,"%d %d {}", &s, &t);
        add_edge_graph(&g,(uint8_t)s,(uint8_t)t,1.0, 0);
    }
    local_run_tests(0,0, &g);
    local_run_tests(1,1, &g);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
