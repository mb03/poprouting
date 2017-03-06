/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   performance.c
 * Author: principale
 *
 * Created on March 4, 2017, 6:04 PM
 */

//from http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
//http://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat

#include "performance.h"
long frequency=0;
char cpu_file[80];
int parse_line(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

void get_memory_info(char * c, int *real, int *virtual_s){ 
    FILE* file = fopen(c, "r");
    int result = -1;
    char line[128];
    int i=0;
    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            (*virtual_s) = parse_line(line);
            i+=1;
            if(i==2)
                break;
        }
        if (strncmp(line, "VmRSS:", 6) == 0){
            (*real) = parse_line(line);
            i+=1;
            if(i==2)
                break;
        }
    }
    fclose(file);
}

void get_cpu_info(char * c, unsigned long long int * utime, unsigned long long int * stime){ //Note: this value is in KB!
    FILE* file = fopen(c, "r");
    char line[2048];
    int d;
    while (fgets(line, 2048, file) != NULL){
    }
    d=strlen(line);
    int i=0,t=0;
    long int x=0;
    for(;i<d;i++){
        if(line[i]==' '){
            t++;
            if(t==13){
                sscanf(line+i, "%llu ", utime);
            }
            if(t==14){
                sscanf(line+i, "%llu ", stime);
                
                break;
            }
        }
    }
    
    fclose(file);
}

unsigned long  current_time_millis(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000 * tv.tv_sec + tv.tv_usec/1000;
}

char log_memory_info(char * status){
    int real=-1,virtual_s=-1;
    get_memory_info(status,&real,&virtual_s);
    if( access( "log_mem.txt", F_OK ) == -1 ) {
        FILE *f = fopen("log_mem.txt", "w+");
        fprintf(f, "time\t\t\treal\tvirtual_s\n");
        fclose(f);
    }
    FILE *f = fopen("log_mem.txt", "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%lu\t%d\t%d\n", current_time_millis(),real,virtual_s);
    
    fclose(f);
    
}
void init_log_cpu_info(char * pid){
    strcpy(cpu_file, "/proc/");
    strcat(cpu_file, pid);
    strcat(cpu_file, "/stat");
}
void log_cpu_info(double percentage,char *filename,int nodenum){
    if( access( filename, F_OK ) == -1 ) {
        FILE *f = fopen(filename, "w+");
        fprintf(f, "time\t\t\tnodenum\tcpu\n");
        fclose(f);
    }
    FILE *f = fopen(filename, "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%lu\t%d\t%f\n",current_time_millis(),nodenum,percentage);
    fclose(f);
    
}
void log_start(char *filename){
    if( access( filename, F_OK ) == -1 ) {
        FILE *f = fopen(filename, "w+");
        fprintf(f, "time\t\t\tnodenum\tcpu\n");
        fclose(f);
    }
    FILE *f = fopen(filename, "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%lu\ttstart\n",current_time_millis());
    fclose(f);
    
}

char logger(char * pid, int interval){
    char status[80];
    strcpy(status, "/proc/");
    strcat(status, pid);
    strcat(status, "/status");
    while(1){
        log_memory_info(status);
        usleep(interval);
    }
}

void set_last_val(struct  data_last * dl){
    init_log_cpu_info("self");
    unsigned long long int utime=0,stime=0;
    get_cpu_info(cpu_file,&utime,&stime);
    dl->time_millis=current_time_millis();
    dl->last_cpu_ticks=utime+stime;
    if(frequency==0)
        frequency=sysconf(_SC_CLK_TCK);;
}

int get_percentage(struct  data_last * dl){
    unsigned long long int utime=0,stime=0;
    get_cpu_info(cpu_file,&utime,&stime);
    long time=current_time_millis();
    long ticks=utime+stime-dl->last_cpu_ticks;
    double time_exe=((double)(time-dl->time_millis))/1000;
    //printf("frequency %f %ld\n",time_exe,ticks);
    dl->time_millis=time;
    dl->last_cpu_ticks=utime+stime;
    int percent=(100*ticks/(time_exe*frequency));
    return percent>100?100:percent;
    
}
