#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>
#include "../include/utils.h"
#include <time.h>
#include <omp.h>




int main(int argc, char **argv){

   int t;

    int N = atoi(argv[1]);
    int k = atoi(argv[2]);

    if(argc < 4){
        t=1;
        
    }else t = atoi(argv[3]);


    double itime, ftime, exec_time;
    itime = omp_get_wtime();


    float *amostrasx = malloc(N * sizeof(float)); // coordenadas x das amostras
    float *amostrasy = malloc(N * sizeof(float)); // coordenadas y das amostras
    float *clustersx = malloc(k * sizeof(float)); // coordenadas x dos clusters
    float *clustersy = malloc(k * sizeof(float)); // coordenadas y dos clusters 
    int *clusters = malloc(N * sizeof(int)); // cluster de cada amostra 
    float *somax= malloc(k * sizeof(float)); // soma das coordenadas x de cada cluster
    float *somay= malloc(k * sizeof(float));// soma das coordenadas y de cada cluster
    int *total= malloc(k * sizeof(int)); // total de amostras de cada cluster

   

    //Amostra *amostras= malloc (N * sizeof *amostras);
    //Cluster *clusters= malloc (k * sizeof *clusters);
    

    inicializa(amostrasx,amostrasy, clustersx,clustersy,clusters,somax,somay,total, N, k);
    int iteracoes=0, stop = 0;

    while(stop != 1){
        stop = findClosestCentroids(amostrasx,amostrasy, clustersx,clustersy,clusters,somax,somay,total, N, k,t);
        iteracoes++;
        if(iteracoes==21) break;
    }

    printCentroides(clustersx, clustersy,total, N, k);
    printf("Iterations: %d\n",iteracoes-1);

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    //end = clock();
	//double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("TIME SPENT: %f\n",exec_time);
    return 0;
}


