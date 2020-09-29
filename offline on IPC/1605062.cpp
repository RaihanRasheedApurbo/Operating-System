#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include <bits/stdc++.h>
using namespace std;

int numberOfBiker = 10;
int numberOfServiceMen = 3;
int numberOfCashier = 3;
pthread_mutex_t *serviceMen = new pthread_mutex_t[numberOfServiceMen];
void *bikerFunction(void *arg);



int main() 
{
    srand (static_cast <unsigned> (time(0)));
    int res;
    pthread_t *bikers = new pthread_t[numberOfBiker];
    for(int i=0;i<numberOfServiceMen;i++)
    {
        res = pthread_mutex_init(serviceMen+i,NULL);
        if(res!=0)
        {
            printf("Mutex for serviceMen, creation failed!");
        }
    }
    for(int i=0;i<numberOfBiker;i++)
    {
        printf("sending %d\n",i);
        int *t = new int;
        *t = i;
        res=pthread_create(bikers+i,NULL,bikerFunction,t);
        if(res!=0)
        {
            printf("error while creating threads\n");
            return -1;
        }
    }
    printf("waiting for the end to come\n");
    for(int i=0;i<numberOfBiker;i++)
    {   
        void **t;
        res = pthread_join(bikers[i],t);
        if(res!=0)
        {
            printf("error while joining threads\n");
            return -1;
        }
    }
    cout<<"exiting from main"<<endl;

    return 0;
}

void *bikerFunction(void *arg)
{
    int currentBikerNumber = *(int *)arg;
    delete (int *)arg;
    pthread_mutex_lock(serviceMen+0);
    for(int i=0;i<numberOfServiceMen;i++)
    {
        
        printf("%dth biker is working with %dth service man\n",currentBikerNumber,i);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // generates 0.0 to 1.0 inclusive
        r = r*2; // generate 0.0 to 2.0 inclusive
        sleep(r);
        //printf("%dth biker has completed working with %dth service man. it took %f mili seconds\n",
        //currentBikerNumber,i,r);
        if(i+1<numberOfServiceMen)
        {
            pthread_mutex_lock(serviceMen+i+1);
        }
        pthread_mutex_unlock(serviceMen+i);
    }
    printf("work completed of biker %d\n",currentBikerNumber);
    pthread_exit(0);
    
    
}
