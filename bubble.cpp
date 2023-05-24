#include <iostream>
#include <omp.h>
#include <time.h>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <vector>
using namespace std;
using namespace std::chrono;
    
void bubble_sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (array[j + 1] < array[j])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}
    
void bubblesort(int arr[], int n)
{
    int i, j;
#pragma omp parallel for shared(arr) private(j)
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
    
void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << " " << arr[i];
    }
        cout << "\n";
    }
    
int main()
{
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;
    int arr[n];
    int count = 3;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }
    
    cout << "Input array: ";
    print_arr(arr, n);
    auto beg = high_resolution_clock::now();
    bubblesort(arr, n);
    auto end = high_resolution_clock::now();
    auto s = duration_cast<microseconds>(end - beg);
    
    auto begi = high_resolution_clock::now();
    bubble_sort(arr, n);
    auto endi = high_resolution_clock::now();
    auto sd = duration_cast<microseconds>(endi - begi);
    
    cout << "Sorted array using Bubble Sort: \n";
    print_arr(arr, n);
    
    cout << "\nTime taken by Bubble Sort (sequential): " << s.count() << " microseconds" << endl;
    cout << "\nTime taken by Bubble Sort (parallel): " << sd.count() << " microseconds" << endl;
    cout << "\nSpeedup: " << (float)sd.count() / s.count() << endl;
    
    return 0;
}
    
    

