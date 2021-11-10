#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

void luDecomposition(double mat[][MAX], int n, double b[])
{
    double *l = new double[n * n];
    double *u = new double[n * n];
    
    for (int i = 0; i < n * n; i++)
        l[i] = 0;

    for (int i = 0 ; i < n * n; i++)
        u[i] = 0;

    // Decomposing matrix into Upper and Lower
    // triangular matrix
    for (int i = 0; i < n; i++){

        // Upper triangular
        for (int j = i; j < n; j++){

            // Summation of L(i, k) * U(k, j)
            double sum = 0;
            for (int k = 0; k < i; k++){
                sum += (l[i * n + k] * u[k * n + j]);
            }

            // Evaluating U(i, j)
            u[i * n + j] = mat[i][j] - sum;
        }

        // Lower triangular
        for (int j = i; j < n; j++){
            if (i == j)
                l[i * n + j] = 1;
            else {
                double sum = 0;
                for (int k = 0; k < i; k++){
                    sum += (l[j * n + k] * u[k * n + i]);
                }
                l[j * n + i] = (mat[j][i] - sum) / u[i * n + i];
            }
        }
    }

    double *z = new double[n];
    double *x = new double[n];

    z[0] = b[0] / l[0];
    for (int i = 1; i < n; i++){
        double sum = 0;
        for (int j = 0; j < i; j++){
            sum += z[j] * l[i * n + j];
        }
        z[i] = (b[i] - sum) / l[i * n + i];
    }

    x[n - 1] = z[n - 1] / u[n * n - 1];
    for (int i = n - 2; i >= 0; i--){
        double sum = 0;
        for (int j = i + 1; j < n; j++){
            sum += x[j] * u[i * n + j];
        }
        x[i] = (z[i] - sum) / u[i * n + i];
    }

    cout << setw(36)
         << "      Lower Triangular"
         << setw(60)
         << "         Upper Triangular" << endl;

    for (int i = 0; i < n; i++){

        for (int j = 0; j < n; j++){
            cout << setw(12) << l[i * n + j] << "\t";
        }
        cout << "\t";

        for (int j = 0; j < n; j++){
            cout << setw(12) << u[i * n + j] << "\t";
        }
        cout << endl;

    }
    cout << setw(24)
         << "    Solution" << endl;
    for (int i = 0; i < n; i++){
        cout << setw(12) << "\t"
             << x[i] << endl;
    }
}

int main()
{
    double mat[][MAX]
        = { { 22, -10, -12 }, 
            { -10, 38, -4 }, 
            { -8, -8, 16 } };
    double b[] = { 24, 0, 0 };
    
    luDecomposition(mat, sizeof(b) / sizeof(b[0]), b);
    return 0;
}



// 2 10 1 7
// 1 2 7 10
// 10 7 2 1
// 9 6 1
// 8 5
// 3

// -1 2 0
// 2 0 -1
// 3 1
// 2

// 3 2 -4 -2 0
// 3 2 0 -2 -4
//       2
//     2
//   2
// 1


// 3 -5 6 2 0 -6 -9 4 8
// 8 6 4 3 2 0 -5 -6 -9
// 2 2 1 1 2 (5) 1 3
// 17 15 13 12 11 9 4 3
// 14 12 10 9 8 6 1
// 13 11 9 8 7 5
// 8 6 4 3 2
// 6 4 2 1
// 5 3 1
// 4 2
// 2