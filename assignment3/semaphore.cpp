#include<iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
float sum=0.0;
int n,threadCount;
float a,b;
int flag=0;
sem_t sem;
void * trap(void *r){
    long rank=(long)r;
    float h=(b-a)/n;
    float localSum=0.0;
    float localN=n/threadCount;
    float localA=a+rank*localN*h;
    float localB=localA+localN*h;
    float x_i;
    for(int i=1;i<localN-1;i++){
        x_i=localA+i*h;
        localSum+=x_i*x_i+3*x_i+10;
    }
    localSum+=.5*((localA*localA+3*localA+10)+(localB*localB+3*localB+10));
    localSum*=h;
    sem_wait(&sem);
    sum+=localSum;
    flag=(flag+1)%threadCount;
    sem_post(&sem);

}
int main(){
    cout<<"enter a,b"<<endl;
    cin>>a>>b;
    cout<<"enter n"<<endl;
    cin>>n;
    cout<<"enter number of threads"<<endl;
    cin>>threadCount;
    pthread_t *x=new pthread_t[threadCount];
    sem_init(&sem, 0, 1);
    for(int i=0;i<threadCount;i++){
        pthread_create( &x[i], NULL, trap, (void*) i);
    }
    for(int i=0;i<threadCount;i++){
        pthread_join(x[i], NULL);
    }
    cout<<"the integral is: "<<sum<<endl;
}