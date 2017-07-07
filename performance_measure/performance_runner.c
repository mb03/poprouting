/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   performance_runner.c
 * Author: principale
 *
 * Created on March 4, 2017, 10:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "performance.h"
/*
 * 
 */
int main(int argc, char** argv) {
    if (argc<2){
	return;
    }
    //logger(argv[1],2000); //smaller graphs
    logger(argv[1],20000); //bigger graphs
    return (EXIT_SUCCESS);
}

