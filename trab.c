#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct farmacia{
    int virus_morto;
    int seringa;
    int insumo_secreto;
} farmacia;

typedef struct crakudo{
    int virus_morto;
    int seringa;
    int insumo_secreto;
    int curas;
} crakudo;

typedef struct dados{
    int mesa[6];
    sem_t reposicao[3]; //Um semaforo para cada farmacia
    crakudo usuario[3];
} dados;

void* consumidor (void* data){
    dados *data_cons = (dados *) data;
    printf("%d\n",data_cons->mesa[0]);

    return 0;
}

void* produtor (void* data){
    dados *data_prod = (dados *) data;
    printf("%d\n",data_prod->mesa[0]);

    return 0;
}

int main(){
    // [vm1,se1,se2,is1,vm2,is2]
    dados data;
    int i;
    data.mesa[0] = 666;

    pthread_t t_crack[3];
    pthread_t t_farm[3];

    for (i=0;i<3;i++)
        pthread_create(&t_crack[i],NULL,consumidor, (void *) &data);
        pthread_create(&t_farm[i],NULL,produtor, (void *) &data);
    

    for (i=0;i<3;i++)
        pthread_join(t_crack[i],NULL);
        pthread_join(t_farm[i],NULL);

    return 0;
}

