#include <iostream>
#include <vector>

using namespace std;

int main() {
    int matrixCount, rows, cols, selectedMatrix;
    cin >> matrixCount >> rows >> cols;

    // 3D vector to store matrices
    vector<vector<vector<int>>> allMatrices(matrixCount, vector<vector<int>>(rows, vector<int>(cols)));

    // Input values for all matrices
    for (int mat = 0; mat < matrixCount; mat++) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                cin >> allMatrices[mat][row][col];
            }
        }
    }

    // Read and display selected matrices
    while (cin >> selectedMatrix) {
        selectedMatrix--; // Convert 1-based index to 0-based index
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                cout << allMatrices[selectedMatrix][row][col] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
