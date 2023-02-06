#include <iostream>
using namespace std;
struct student 
{
    int roll_no;
    string name;
};
 void display(student *& st){
    cout<< st->name<<endl;
    cout<<st->roll_no<< endl;
    st->roll_no=20;

 }

int main(){
    student s;
    // s.roll_no=5;
    // s.name="Ram";
    // cout<<s.name<<endl;
    student *st=new student();
    st->roll_no=10;
    st->name="Sita";

   // cout<< st->name <<endl;
   // cout<< st->name <<endl;
   display(st);
   cout<< st->roll_no <<endl;


}