#include<iostream>
#include<string>
#include<omp.h>
#include <sys/time.h>
using namespace std;

double GetWallTime() {
struct timeval tp;
int rtn = gettimeofday(&tp, NULL);
return ((double) tp.tv_sec + (1.e-6)*tp.tv_usec);
}

int main(int argc,char **argv){
    FILE * input=fopen(argv[1],"r");
    FILE * mask=fopen(argv[2],"r");
    FILE * output=fopen(argv[3],"w");
    int p=stoi(argv[4]);
    int m[3][3];
    int col,row,sum;
    fscanf(input,"%d",&row);
    fscanf(input,"%d",&col);
    int **a=new int*[row];
    int **b=new int*[row];
    for (int i=0;i<row;i++){
        a[i]=new int[col];
        b[i]=new int[col];
    }

    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fscanf(input,"%d",&a[i][j]);
        }
    }
    for (int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            fscanf(mask,"%d",&m[i][j]);
        }
    double start = GetWallTime();    
    #pragma omp parallel for num_threads(p)
    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            sum=0;
            if(i==0||i==row-1||j==0||j==col-1){
	            b[i][j]=a[i][j];
	        } else{
                for(int k=0;k<3;k++){
	                for (int l=0;l<3;l++){
	                    sum+=a[i+k-1][j+l-1]*m[k][l];
	                }
                }
                b[i+1][j+1]=sum;
            }
        }
    }
    double end = GetWallTime();
    cout<<"time :"<<end-start<<endl;
    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fprintf(output,"%d ",b[i][j]);
        }
            fprintf (output,"\n");
    }

    return 0;
}