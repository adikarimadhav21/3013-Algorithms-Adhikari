/*****************************************************************************
*                    
*  Author:           Madhav Adhikari
*  Email:            madhikari0624@my.msutexas.edu
*  Label:            A04
*  Title:            CircularArrayQue
*  Course:           CMPS 3013
*  Semester:         Spring 2023
* 
*  Description:
*        This program implements a class that demostrate the concept of circular array queue concept. 
* 
*  Usage:
*        This files used to test the CircularArrayQue concept
* 
*  Files:       
   main.cpp    : driver program 
*****************************************************************************/

#include <iostream>

using namespace std;
/**
 * CircularArrayQue
 * 
 * Description:
 *       This class implements concept of circular array queue 
 * 
 * Public Methods:
 *          CircularArrayQue()
 *    void  push(int item)
 *    int  pop()
 * 
 * Private Methods:
 *   void  init(init size=0)
 *   bool Full()   
 *
 * 
 * Usage: 
 *  CircularArrayQue()  // create instance of CircularArrayQue
 *  push (int item)     // insert item in queue or container 
 *  pop ()              // retrive item 
 *  inint()             // initialize variables
 *      
 */

class CircularArrayQue {
private:
    int *Container;
    int Front;
    int Rear;
    int QueSize; // items in the queue
    int CurrentSize;
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }
     /**
     * Public : push
     * 
     * Description:
     *      Loads item into a ArrayQueue.
     * 
     * Params:
     *      [int]     :  item
     * 
     * Returns:
     *      void
     */

    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}