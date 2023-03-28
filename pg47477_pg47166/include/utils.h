#ifndef KMEANS_H_
#define KMEANS_H_




typedef struct amostra{
    float ponto_i_coordenada_x;
    float ponto_i_coordenada_y;
    int cluster; 
    
} *Amostra;

//Estrutura que define um Cluster
typedef struct cluster{
    int size;
    float centroid_x;
    float centroid_y;

}*Cluster;

void inicializa(float *amostrasx,float *amostrasy,float *clustersx,float *clustersy,int *clusters,float *somax,float *somay,int *total,int N,int k);
int findClosestCentroids(float *amostrasx,float *amostrasy,float *clustersx,float *clustersy,int *clusters,float *somax,float *somay,int *total,int N,int k,int t);
void printCentroides(float *clustersx,float *clustersy,int *total,int N,int k);



#endif