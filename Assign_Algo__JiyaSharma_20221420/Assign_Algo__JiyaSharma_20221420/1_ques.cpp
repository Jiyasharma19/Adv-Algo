#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::vector;

int comparisonCount = 0; // Keep track of number of comparisons

// Function to swap values in a vector
void exchange(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

// Function to partition the vector based on the pivot
int performPartition(vector<int> &arr, int start, int end) {
    int pivotValue = arr[end];
    int smallerIndex = start - 1;

    cout << "Partitioning with pivot: " << pivotValue << " at position: " << end << "\n";

    for (int k = start; k < end; ++k) {
        comparisonCount++;
        if (arr[k] <= pivotValue) {
            ++smallerIndex;
            exchange(arr[smallerIndex], arr[k]);
        }
    }
    exchange(arr[smallerIndex + 1], arr[end]);
    return smallerIndex + 1;
}

// Function to select a random pivot and partition the vector
int selectRandomPivot(vector<int> &arr, int start, int end) {
    int randomIdx = start + rand() % (end - start + 1);
    exchange(arr[randomIdx], arr[end]);
    return performPartition(arr, start, end);
}

// Randomized Quick Sort implementation
void quickSortRandomized(vector<int> &arr, int start, int end) {
    if (start < end) {
        int pivotPos = selectRandomPivot(arr, start, end);
        cout << "Pivot finalized at position: " << pivotPos << "\n";
        quickSortRandomized(arr, start, pivotPos - 1);
        quickSortRandomized(arr, pivotPos + 1, end);
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    vector<int> data = {15, 3, 45, 10, 29, 8, 19, 42};
    int size = data.size();

    // Display the input vector
    cout << "Initial array: ";
    for (const int &num : data) {
        cout << num << " ";
    }
    cout << "\n";

    // Sort the vector using Randomized Quick Sort
    quickSortRandomized(data, 0, size - 1);

    // Display the sorted vector
    cout << "\nSorted array: ";
    for (const int &num : data) {
        cout << num << " ";
    }
    cout << "\n";

    // Display number of comparisons
    cout << "Total comparisons made: " << comparisonCount << "\n";

    return 0;
}
