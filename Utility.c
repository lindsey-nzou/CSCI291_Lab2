#include <stdio.h>
#include <stdbool.h>

// Function - check if position is valid within array bounds
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

// Function - remove element from array at specified position
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid input position. No element has been removed.\n");
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[length - 1] = 0; // Optional: Set last element to 0 after shifting
}

// Function - insert element at specific position in array
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid input position. No element has been inserted.\n");
        return;
    }
    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

// Function - reshape 1D array into 2D array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Invalid input dimensions for array reshape.\n");
        return;
    }
    for (int i = 0, index = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            arr2d[j][i] = arr[index++];
        }
    }
}

// Function - transpose matrix
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int transposed[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            transposed[j][i] = mat[i][j];
        }
    }
}

// Function - check for duplicates in the array
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

// Main function for testing purposes
int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2d[2][5];
    int transposed[5][2];

    printf("Original array: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Remove element test
    remove_element(arr, 10, 3);
    printf("After removing value at 3 position: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Insert element test
    insert_element(arr, 10, 3, 99);
    printf("After inserting 99 at 3: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reshape test
    reshape(arr, 10, 2, 5, arr2d);
    printf("Reshaped 2D array:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    // Transpose test
    trans_matrix(2, 5, arr2d, transposed);
    printf("Transposed matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    // Duplicate check test
    if (found_duplicate(arr, 10)) {
        printf("Array has duplicate numbers.\n");
    } else {
        printf("Array does not have duplicate numbers.\n");
    }

    return 0;
}