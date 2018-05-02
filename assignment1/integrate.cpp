#include<iostream>
#include<string>
using namespace std;
float func(float*);
int main(int argc,char *argv[]){
	if(argc!=4){
		cout<<"usage: float a,float b,int n"<<endl;
		MPI_Abort;
	}
	else{
		
		float a=stof(argv[1]);
		float b=stof(argv[2]);
		int n=stoi(argv[3]);
		float h=(b-a)/n;
		float integral=0;
		float x_i;
		for(int i=1;i<n-1;i++){
			x_i=a+i*h;
			integral+=func(&x_i);
		}
		integral+=.5*(func(&a)+func(&b));
		integral*=h;
		cout<<"integral is: "<<integral<<endl;
		return 0;
	}
}
