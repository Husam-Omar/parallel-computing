#include<iostream>
#include<math.h>
#include<mpi.h>
#include<string>
#include <sys/time.h>
using namespace std;

double GetWallTime() {
    struct timeval tp;
    int rtn = gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (1.e-6)*tp.tv_usec);
}
int isPrime(int n){
    for(int i=2;i<=sqrt(n);i++){
        if (n%i==0)return false;
    }
    return true;
}
int main(int argc,char **argv){
    MPI_Init(&argc,&argv);
    unsigned long int n=stoi(argv[1]);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int x=n/size;

    cout<<"process "<<rank<<" : "; 
    double start =MPI_Wtime();// GetWallTime();
    if (rank==0)
        if (n > 2 )
            cout<<"2 ";
    for (int i=rank*x+1;i<=(rank+1)*x;i+=2)
        if ( isPrime (i) )
            cout<<i<<" ";
    double finish =MPI_Wtime();// GetWallTime();

    cout<<"\t time="<<finish-start<<endl;  

    MPI_Finalize();
    return 0;
}