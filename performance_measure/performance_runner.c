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
	printf("1 %d\n",argc);
    if (argc<2){
	return;
    }
printf("2 %d\n",argc);
    logger(argv[1],2000);
printf("3 %d\n",argc);
    return (EXIT_SUCCESS);
}

