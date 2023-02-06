#include <iostream>
using namespace std;

void insertionSort(int arr[])
{
    int n = 10;
    for (int i = 1; i < n; i++)
    {
        int current = arr[i];
        int j = i - 1;
        while (arr[j] > current && j >= 0)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}

void selectioneSort(int arr[])
{
    int n = 10;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void bubbleSort(int arr[])
{
    int n = 10;
    bool swaped = false;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaped = true;
            }
        }
        if (swaped == false)
        {
            return;
        }
    }
}

int main()
{
    int A[10] = {23, 4, 6, 77, 3, 98, 12, 87, 33, 100};

    // selectioneSort(A);
    // bubbleSort(A);
    insertionSort(A);

    for (int i = 0; i < 10; i++)
    {
        cout << A[i] << " ";
    }
}