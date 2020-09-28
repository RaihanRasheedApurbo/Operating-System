#include<iostream>
#include<cstdio>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include <time.h>

using namespace std;

#define number_of_producers 2
#define number_of_consumers 5
#define arr_size 1

int ind = 0;
sem_t full_array, empty_array;
pthread_mutex_t mutex;

void* produce_item(void* arg){
    while(true){
        sem_wait(&empty_array);
        pthread_mutex_lock(&mutex);
        sleep(3);
        printf("%s producer has produced %d th item\n",(char*)arg,ind);
        ind++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full_array);
    }
    //pthread_exit((void*)strcat((char*)arg," producer is finishing\n"));
}

void* consume_item(void* arg){
    while(true){
        sem_wait(&full_array);
        pthread_mutex_lock(&mutex);
        sleep(1);
        printf("%s consumer has consumed %d th item\n",(char*)arg,ind-1);
        ind--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_array);
    }
    //pthread_exit((void*)strcat((char*)arg," consumer is finishing\n"));
}

int main(int argc, char* argv[])
{
    int res;

    res = sem_init(&empty_array,0,arr_size);
    if(res != 0){
        printf("Failed\n");
    }

    res = sem_init(&full_array,0,0);
    if(res != 0){
        printf("Failed\n");
    }

    res = pthread_mutex_init(&mutex,NULL);
    if(res != 0){
        printf("Failed\n");
    }

    pthread_t producers[number_of_producers], consumers[number_of_consumers];
    for(int i = 0; i < number_of_producers; i++){
        char *id = new char[3];
        strcpy(id,to_string(i+1).c_str());

        res = pthread_create(&producers[i],NULL,produce_item,(void *)id);

        if(res != 0){
            printf("Thread creation failed\n");
        }
    }

    for(int i = 0; i < number_of_consumers; i++){
        char *id = new char[3];
        strcpy(id,to_string(i+1).c_str());

        res = pthread_create(&consumers[i],NULL,consume_item,(void *)id);

        if(res != 0){
            printf("Thread creation failed\n");
        }
    }

    for(int i = 0; i < number_of_producers; i++){
        void *result;
        pthread_join(producers[i],&result);
        printf("%s",(char*)result);
    }

    for(int i = 0; i < number_of_consumers; i++){
        void *result;
        pthread_join(consumers[i],&result);
        printf("%s",(char*)result);
    }

    res = sem_destroy(&full_array);
    if(res != 0){
        printf("Failed\n");
    }
    res = sem_destroy(&empty_array);
    if(res != 0){
        printf("Failed\n");
    }

    res = pthread_mutex_destroy(&mutex);
    if(res != 0){
        printf("Failed\n");
    }

    return 0;
}
