#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>
#include "../include/utils.h"
#include <omp.h>


int K = 4;

void inicializa(float *amostrasx,float* amostrasy,float* clustersx,float* clustersy,int *clusters,float *somax,float *somay,int *total,int N,int k) {
    
    srand(10);
    for(int i = 0; i < N; i++) {    
        amostrasx[i]= (float) rand() / RAND_MAX;
        amostrasy[i] = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i <k; i++){
        clustersx[i]= amostrasx[i];
        clustersy[i] = amostrasy[i];   
        somax[i]=0.0;
        somay[i]=0.0;
        total[i]=0;       
    }
    
}




int findClosestCentroids(float *amostrasx,float *amostrasy,float *clustersx,float *clustersy,int *clusters,float *somax,float *somay,int *total,int N,int k, int t){
   


   for(int i=0; i< k ; i++){
        somay[i]=0.0;
        somax[i]=0.0;
        total[i]=0;
    }    

    #pragma omp parallel for schedule(static) num_threads(t) 
    for(int i = 0; i<N ;i++){

        int cluster = 0;

        float bestdist=((amostrasx[i]-clustersx[0])*(amostrasx[i]-clustersx[0]))+((amostrasy[i]-clustersy[0])*(amostrasy[i]-clustersy[0]));
         
      //  printf("best dist = %d \n", bestdist);

      //  float bestdist=(( amostras[i]->ponto_i_coordenada_x-clusters[0]->cluster_i_coordenada_x ))*(( amostras[i]->ponto_i_coordenada_x-clusters[0]->cluster_i_coordenada_x ))+(( amostras[i]->ponto_i_coordenada_y-clusters[0]->cluster_i_coordenada_y))*(( amostras[i]->ponto_i_coordenada_y-clusters[0]->cluster_i_coordenada_y));
        for(int j=1;j<k;j++){

            float dist = ((amostrasx[i]-clustersx[j])*(amostrasx[i]-clustersx[j]))+((amostrasy[i]-clustersy[j])*(amostrasy[i]-clustersy[j]));
            //float dist = (( amostras[i]->ponto_i_coordenada_x-clusters[j]->cluster_i_coordenada_x ))*(( amostras[i]->ponto_i_coordenada_x-clusters[j]->cluster_i_coordenada_x ))+(( amostras[i]->ponto_i_coordenada_y-clusters[j]->cluster_i_coordenada_y))*(( amostras[i]->ponto_i_coordenada_y-clusters[j]->cluster_i_coordenada_y)) ;
            if(dist<bestdist){
                cluster = j;
                bestdist = dist;  
            }   

        }

        clusters[i]=cluster;
        
    }
    int a;
    // #pragma omp parallel for //reduction(+:somax) reduction(+:somay) reduction(+:somay)
    for(a=0;a<N;a++){
         int z=clusters[a]; // identifica cluster
         somax[z]+=amostrasx[a];
         somay[z]+=amostrasy[a];
         total[z]++;       
    }

    #pragma omp parallel for num_threads(t)
    for(int i=0;i<k;i++){
        clustersx[i]=somax[i]/total[i];
        clustersy[i]=somay[i]/total[i];
    }


}


void printCentroides(float *clustersx,float *clustersy,int *total,int N,int k){
    printf("N = %d, k = %d\n",N,k);
    for(int i = 0; i<k;i++){
        printf("Center : (%.3f , %.3f) Size: %d\n",clustersx[i],clustersy[i],total[i]);
    }

}

