#include <iostream>
using namespace std;
class Test{
public:
void display(int * a){
    for (int i=0; i<5;i++){
        *(a+i)=9;
    cout<<*(a+i)<<endl;
 }
}

};

int main(){
Test t;
 int arr[5]={1,2,3,4,5};
 t.display(arr);
 for (int i=0; i<5;i++){
    cout<<arr[i]<<endl;
 }
 cout<<arr+1<<endl;
 cout<<&arr[1]<<endl;

 cout<<*(arr+1)<<endl;
 cout<<arr[1]<<endl;


}