#include <stdio.h>

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function (Max Heap)
void heapify(int arr[], int n, int i) {
    int largest = i;        // root
    int left = 2 * i + 1;   // left child
    int right = 2 * i + 2;  // right child

    // Check if left child is larger
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child is larger
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify affected subtree
        heapify(arr, n, largest);
    }
}

// Function to build heap
void buildHeap(int arr[], int n) {
    // Start from last non-leaf node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);

        // Display intermediate heap
        printf("Heap after heapify at index %d: ", i);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

// Heap Sort function
void heapSort(int arr[], int n) {
    // Step 1: Build Max Heap
    buildHeap(arr, n);

    // Step 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {

        // Move current root (max) to end
        swap(&arr[0], &arr[i]);

        printf("\nAfter swapping root with index %d: ", i);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // Heapify reduced heap
        heapify(arr, i, 0);

        printf("Heap after heapify: ");
        for (int j = 0; j < i; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nInitial Array: ");
    printArray(arr, n);

    heapSort(arr, n);

    printf("\nFinal Sorted Array (Ascending Order): ");
    printArray(arr, n);

    return 0;
}

// Steps to Write Code
// Take input array
// Build Max Heap using heapify (from n/2 − 1 to 0)
// Swap root (maximum) with last element
// Reduce heap size
// Apply heapify again
// Repeat until array is sorted
// Print final sorted array

// 📌 Output
// First: Max Heap is formed
// Then: Largest elements move to end one by one
// Final Output:
// Ascending order sorted array
// Example: 33 34 44 66 77

// 📌 Time Complexity
// Build Heap: O(n)
// Heap Sort: O(n log n)
// Final: O(n log n)

// 📌 Space Complexity
// O(1) (in-place sorting)
// 📌 Applications
// Priority Queue
// Operating System scheduling
// Dijkstra’s algorithm
// Large data sorting
// Real-time systems