#include <stdio.h>
int main(int argc, char** argv) {
double mean,var;
run_tests(argc,argv,&mean,&var);
printf("(%f,%f)\n",mean,var);
return 0;
}
