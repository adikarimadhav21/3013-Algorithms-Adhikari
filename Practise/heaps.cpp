#include <iostream>
using namespace std;
#include <vector>

class Heap
{

private:
    vector<int> elements;
    int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    // return left child of `A[i]`
    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    // return right child of `A[i]`
    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    int index_left_child(int i)
    {
        return (2 * i + 1);
    }
    int index_right_child(int i)
    {
        return (2 * i + 2);
    }
    int index_parent(int i)
    {
        return (i - 1) / 2;
    }
    void heapifyUp(int i)
    {
        if (i && elements[index_parent(i)] < elements[i])
        {
            swap(elements[index_parent(i)], elements[i]);
            heapifyUp(index_parent(i));
        }
    }

    void heapifyDown(int i)
    {
        // int left=index_left_child(i);
        // int right=index_right_child(i);
        int left = LEFT(i);
        int right = RIGHT(i);
        int max_index = i;

        // cout<< max_index;

        if (left < size() && elements[left] > elements[i])
        {
            max_index = left;
        }
        if (right < size() && elements[right] > elements[max_index])
        {
            max_index = right;
        }
        if (max_index != i)
        {
            swap(elements[i], elements[max_index]);
            heapifyDown(max_index);
        }
    }

    void heapify_down(int i)
    {
        int left = LEFT(i);
        int right = RIGHT(i);
        int largest = i;
        if (left < size() && elements[left] > elements[i])
        {
            largest = left;
        }

        if (right < size() && elements[right] > elements[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(elements[i], elements[largest]);
            heapify_down(largest);
        }
    }

public:
    Heap()
    {
        // elements.push_back();
    }
    Heap(vector<int> array)
    {
        heapifyUp(array);
    }

    void heapifyUp(vector<int>a){
        elements=a;
      //  heapifyDown(0);
         // Index of last non-leaf node
    int startIdx = (elements.size() / 2) - 1;
  
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapifyDown(i);
    }

    }
    void push(int data)
    {
        elements.push_back(data);
        heapifyUp(elements.size() - 1);
    }
    // return size of the heap
    unsigned int size()
    {
        return elements.size();
    }
    void pop()
    {
        // int max=elements.front();
        elements[0] = elements.back();
        // cout<<elements[0]<<endl;

        elements.pop_back();

        // 100 50 10 2 5 1
        //   1 50 10 2 5
        print();

        // heapify_down(0);
        heapifyDown(0);
    }
    void print()
    {
        for (int i = 0; i < elements.size(); i++)
        {
            cout << elements[i] << " ";
        }
    }
};

int main()
{

    Heap h;
    h.push(2);
    h.push(5);
    h.push(1);
    h.push(100);
    h.push(50);
    h.push(10);
    h.print();
    cout << endl;

    h.pop();
    h.print();
    cout<<endl;

    vector<int> vals{3, 4, 23, 22, 45, 67, 5, 4, 2, 99, 88, 77, 66, 55};

    Heap heap2(vals);
    heap2.print();
}