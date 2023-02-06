# include <iostream>
using namespace std;

class Test{
  public:

  void squareValue(int num){
    num=num*num;

    cout<<num <<endl;
  }
   void squareRef(int* &num){
    *num=*num* *num;
    cout<<*num <<endl;
  }
   void squareRefPointer(int *pnum){
    *pnum=*pnum* *pnum;
    cout<<*pnum<<endl;
  }

};

int main (){
  Test t;
  int n=5;
  int *ptr=&n;

  t.squareValue(n);
    cout<<"squareValue " <<n<<endl;

  t.squareRef(ptr);
    cout<<"squareRef "<<n<<endl;

  t.squareRefPointer(ptr);
    cout<<"squareRefPointer "<<n<<endl;


}