#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include <bits/stdc++.h>
using namespace std;

unsigned int numberOfBiker = 10;
unsigned int numberOfServiceMen = 5;
unsigned int numberOfCashier = 1;
int wpn = 0; // wpn -> waiting people number
pthread_mutex_t *wpnMutex= new pthread_mutex_t;
pthread_mutex_t *enter = new pthread_mutex_t;
pthread_mutex_t *serviceMen = new pthread_mutex_t[numberOfServiceMen];
sem_t *cashier = new sem_t;
void *bikerFunction(void *arg);



int main() 
{
    srand (static_cast <unsigned> (time(0)));
    int res;
    res = sem_init(cashier,0,numberOfCashier);
    
    
    pthread_t *bikers = new pthread_t[numberOfBiker];
    for(int i=0;i<numberOfServiceMen;i++)
    {
        res = pthread_mutex_init(serviceMen+i,NULL);
        sleep(10);
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
    //pthread_mutex_lock(enter);
    
    pthread_mutex_lock(serviceMen+0);
    if(wpn>0)
    {
        pthread_yield();
        pthread_mutex_lock(serviceMen+0);
    }
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
        // if(i==0)
        // {
        //     pthread_mutex_unlock(enter);
        // }
        pthread_mutex_unlock(serviceMen+i);
    }
    printf("%dth biker's servicing is complted waiting for payment\n",currentBikerNumber);
    sem_wait(cashier);
    printf("%dth biker's is doing payment\n",currentBikerNumber);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // generates 0.0 to 1.0 inclusive
    r = r*1; // generate 0.0 to 1.0 inclusive
    //sleep(r);
    sem_post(cashier);
    printf("payment completed of bikar %d\n",currentBikerNumber);
    
    pthread_mutex_lock(wpnMutex);
    wpn++;
    printf("%d\n",wpn);
    if(wpn==1)
    {
        //pthread_mutex_lock(enter);
        printf("hi\n");
        for(int i=0;i<numberOfServiceMen-1;i++)
        {
            pthread_mutex_lock(serviceMen+i);
        }

        pthread_mutex_unlock(wpnMutex);
        for(int i=numberOfServiceMen-1;i>=0;i--)
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // generates 0.0 to 1.0 inclusive
            r = r*2; // generate 0.0 to 2.0 inclusive
            sleep(r);
            pthread_mutex_unlock(serviceMen+i);
        }
    }
    else
    {
        pthread_mutex_unlock(wpnMutex);
        pthread_mutex_lock(serviceMen+numberOfServiceMen-1);
        for(int i=numberOfServiceMen-1;i>=0;i--)
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // generates 0.0 to 1.0 inclusive
            r = r*2; // generate 0.0 to 2.0 inclusive
            sleep(r);
            if(i-1>=0)
            {
                pthread_mutex_lock(serviceMen+i-1);
            }
            pthread_mutex_unlock(serviceMen+i);
        }
        
    }
    pthread_mutex_lock(wpnMutex);
    wpn--;
    if(wpn==0)
    {
        //pthread_mutex_unlock(enter);
    }
    printf("biker number %d departed\n",currentBikerNumber);
    pthread_mutex_unlock(wpnMutex);
    
    



    pthread_exit(0);
    
    
}
