#include<iostream>
#include<string>
#include<mpi.h>
using namespace std;
float func(float*);
int main(int argc,char *argv[]){
    if(argc!=4){
        cout<<"usage: a b n"<<endl;
        return 1;
    }
    else{
        MPI_Init(&argc,&argv);
        int rank,size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        float a=stof(argv[1]);
        float b=stof(argv[2]);
        int n=stoi(argv[3]);
        float h=(b-a)/n;
        float localN=n/size;
        float localA=a+rank*localN*h;
        float localB=localA+localN*h;
        float x_i;
        float integral=0,total=0;
        for(int i=1;i<localN-1;i++){
            x_i=localA+i*h;
            integral+=func(&x_i);
        }
        integral+=.5*(func(&localA)+func(&localB));
        integral*=h;

        if(rank==0){//recieve
            total=integral;
            for(int p=1;p<size;p++){
                MPI_Recv(&integral,1,MPI_FLOAT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                total+=integral;
            }
        }
        else{//send
            MPI_Send(&integral,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);
        }
        if(rank==0)
            cout<<total<<endl;
        MPI_Finalize();
        return 0;
    }   
}