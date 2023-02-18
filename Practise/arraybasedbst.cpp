#include <iostream>
using namespace std;

void insert(int arr[], int size, int value) {
    int i = 0; // Start at root
    while (i < size && arr[i] != 0) {
        if (value < arr[i]) {
            i = 2*i + 1; // Move to left child
        } else {
            i = 2*i + 2; // Move to right child
        }
    }
    if (i < size) {
        arr[i] = value; // Insert the new element
    }
}

void inorderTraversal(int arr[], int size, int root) {
    if (root >= size || arr[root] == 0) {
        return;
    }
    inorderTraversal(arr, size, 2*root + 1); // Visit left child
    cout << arr[root] << " "; // Visit root
    inorderTraversal(arr, size, 2*root + 2); // Visit right child
}

int main() {
    int arr[7] = {0}; // Array to store the binary search tree
    insert(arr, 7, 4);
    insert(arr, 7, 2);
    insert(arr, 7, 6);
    insert(arr, 7, 1);
    insert(arr, 7, 3);
    insert(arr, 7, 5);
    insert(arr, 7, 7);
    inorderTraversal(arr, 7, 0); // Start at root
    return 0;
}
