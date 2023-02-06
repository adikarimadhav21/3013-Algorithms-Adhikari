#include<iostream>
#include "avlTree.h"
#include<string>
//#include <time.h>
/**
 * g++ -c  avl_main.cpp
 * g++ -c  avlTree.cpp
 * g++ -o main avl_main.o avlTree.o
 * ./main
*/

using namespace std;
int main(){
      //  srand(time(0));

    AVLTree objAVLTree;
    objAVLTree.insert(5);
    objAVLTree.insert(10);
    objAVLTree.insert(1);
    objAVLTree.insert(57);
    objAVLTree.printValues();
}