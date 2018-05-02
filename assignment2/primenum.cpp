#include<iostream>
#include<math.h>
#include<string>
using namespace std;
int isPrime(int n){
    for(int i=2;i<=sqrt(n);i++){
        if (n%i==0)return false;
    }
    return true;
}
int main(int argc, char *argv[]) {
    unsigned long int n=stoi(argv[1]);
    if (n > 2 )
        cout<<"2 ";
    for (int i=3;i<=n;i+=2)
        if ( isPrime (i) )
            cout<<i<<" ";
    cout<<endl;        
    return 0;
}