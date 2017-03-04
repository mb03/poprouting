/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   performance.h
 * Author: mb03
 *
 * Created on March 4, 2017, 10:44 PM
 */

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stddef.h>
    
    struct data_last{
        long time_micros;
        unsigned long long int last_cpu_ticks;
    };
    
    char logger(char * pid, int interval);
    void set_last_val(struct  data_last * dl);
    int get_percentage(struct  data_last * dl);
    void log_cpu_info(double percentage,char *filename,int nodenum);
    void log_start(char *filename);
    
    
    
    
#ifdef __cplusplus
}
#endif

#endif /* PERFORMANCE_H */

