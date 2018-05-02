#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv) {
    int rank,size,len;
    char* name=new char[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(name, &len);
    if(rank%2==0){
        cout << "Hello World from process " << rank <<" / "<<size<<" "<<name<<endl;
    }
    else{
        cout << "Yello World from process " << rank <<" / "<<size<<" "<<name<<endl;
    }
    MPI_Finalize();
    return 0;
}