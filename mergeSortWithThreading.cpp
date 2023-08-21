#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

class Solution
{
public:
    void merge(int arr[], int l, int m, int r)
    {
        int n1 = m - l + 1;
        int n2 = r - m;

        int left[n1], right[n2];

        for (int i = 0; i < n1; i++)
            left[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            right[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;

        while (i < n1 && j < n2)
        {
            if (left[i] <= right[j])
            {
                arr[k] = left[i];
                i++;
            }
            else
            {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

public:
    void mergeSort(int arr[], int l, int r)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;

            // Create two threads to perform merge sort on left and right halves concurrently
            // thread t1(&Solution::mergeSort, this, arr, l, m);
            // thread t2(&Solution::mergeSort, this, arr, m + 1, r);
            mergeSort(arr, l, m);
            mergeSort(arr, m+1, r);

            // Wait for both threads to finish
            // t1.join();
            // t2.join();

            // Merge the sorted halves
            merge(arr, l, m, r);
        }
    }
};

int main()
{
    int arr[] = {5, 2, 9, 1, 3, 6, 8, 4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    Solution obj;

    auto start = high_resolution_clock::now();

    obj.mergeSort(arr, 0, n - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Time elapsed: " << duration.count() << " milliseconds" << endl;

    return 0;
}
