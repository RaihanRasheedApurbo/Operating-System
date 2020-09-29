#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <bits/stdc++.h>
using namespace std;

int numberOfBiker = 10;
int numberOfServiceMan = 3;
int numberOfCashier = 3;

void *bikerFunction(void *arg);



int main() 
{
    srand (static_cast <unsigned> (time(0)));

    int res;
    pthread_t *bikers = new pthread_t[numberOfBiker];

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
    int *t = (int *)arg;
    printf("inside biker function of %d\n",*t);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    printf("sleep time of thread %d is %f\n",*t,r*2);
    sleep(r*2);
    delete t;
    pthread_exit(NULL);
}
