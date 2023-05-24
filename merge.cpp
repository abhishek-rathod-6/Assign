#include <iostream>
#include <omp.h>
#include <time.h>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <vector>
using namespace std;
using namespace std::chrono;
    
void merge(int low, int mid, int high, vector<int> &nums)
{
    if (low >= high)
        return;
    int l = low, r = mid + 1, k = 0, size = high - low + 1;
    vector<int> sorted(size, 0);
    
    while (l <= mid and r <= high)
        sorted[k++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
    while (l <= mid)
        sorted[k++] = nums[l++];
    while (r <= high)
        sorted[k++] = nums[r++];
    for (k = 0; k < size; k++)
        nums[k + low] = sorted[k];
}
    
void mergeSort(vector<int> nums, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid);
        mergeSort(nums, mid + 1, end);
        merge(start, mid, end, nums);
    }
}
    
void merge_para(vector<int> nums, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
#pragma omp parallel sections
            {
#pragma omp section
            {
                merge_para(nums, start, mid);
            }
    
#pragma omp section
            {
                merge_para(nums, mid + 1, end);
            }
        }
        merge(start, mid, end, nums);
    }
}
    
void printArray(vector<int> v, int size)
{
    for (int i = 0; i < size; i++)
        cout << v[i] << " ";
    cout << endl;
}
    
int main()
{
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        nums[i] = rand() % n;
    }
    
    cout << "Input array: ";
    printArray(nums, n);
    
    auto beg = high_resolution_clock::now();
    mergeSort(nums, 0, n - 1);
    auto end = high_resolution_clock::now();
    auto s = duration_cast<microseconds>(end - beg);
    
    auto begp = high_resolution_clock::now();
    merge_para(nums, 0, n - 1);
    auto endp = high_resolution_clock::now();
    auto sd = duration_cast<microseconds>(endp - begp);
    
    cout << "\nSorted array using Merge Sort: \n";
    printArray(nums, n);
    
    cout << "\nTime taken by Merge Sort: " << s.count() << " microseconds" << endl;
    cout << "\nTime taken by Parallel Sort: " << sd.count() << " microseconds" << endl;
    cout << "\nSpeedup: " << (float)s.count() / sd.count() << endl;
    
    return 0;
}
    
    
