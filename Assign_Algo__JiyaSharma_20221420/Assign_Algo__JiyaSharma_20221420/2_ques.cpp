#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Utility function to swap two elements in an array
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to partition the array and return the position of the pivot
int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int partitionIndex = start;
    cout << "Pivot chosen: " << pivot << "\n";

    for (int i = start; i < end; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(arr[partitionIndex], arr[end]);
    return partitionIndex;
}

// Randomly selects a pivot and partitions the array
int randomPartition(int arr[], int start, int end) {
    int randomIndex = start + rand() % (end - start + 1);
    swap(arr[randomIndex], arr[end]);
    return partition(arr, start, end);
}

// Function to find the ith smallest element in the array
int selectIthSmallest(int arr[], int start, int end, int i) {
    while (start <= end) {
        int pivotIndex = randomPartition(arr, start, end);
        int k = pivotIndex - start + 1;

        if (i == k) {
            return arr[pivotIndex];
        } else if (i < k) {
            end = pivotIndex - 1;
        } else {
            start = pivotIndex + 1;
            i = i - k;
        }
    }
    return -1; // Should not reach here if input is valid
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Initialize random seed

    int arr[] = {15, 3, 45, 10, 29, 8, 19, 42};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    // Display the input array
    cout << "Initial array: ";
    for (int j = 0; j < n; ++j) {
        cout << arr[j] << " ";
    }
    cout << "\n";

    cout << "Enter the value of i (to find the ith smallest element): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input! i should be between 1 and " << n << ".\n";
    } else {
        int result = selectIthSmallest(arr, 0, n - 1, i);
        cout << "The " << i << "th smallest element is: " << result << "\n";
    }

    return 0;
}
