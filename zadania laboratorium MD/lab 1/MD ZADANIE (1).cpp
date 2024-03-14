#include <iostream>


bool nextPermutation(int* A, int n) {
    int k = -1;
    int* B = new int[n];

    for (int i = n-1 ; i >= 0; i--)
    {
        if (A[i] < A[i + 1]) {
            k = i;
            break;
        }
    }
    if (k == -1) {
        return false;//kiedy juz mamy caly ciag odwrocony to sie wywola
    }

    int l = -1;

    for (int j = n; j > k; j--)
    {
        if (A[j] > A[k]) {
            l = j;
            break;
        }
    }
    int temp = A[l];
    A[l] = A[k];
    A[k] = temp;

    for (int i = 0; i <= k; i++)
    {
        B[i] = A[i];
    }

    for (int i = k + 1, j = n - 1; i < n; i++, j--)
    {
        B[i] = A[j];

    }
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
    return true;
}


bool nextCombination(int N, int k, int* A) {
    for (int i = k-1 ; i >= 0; i--) {
        if (A[i] < N - k + i) {
            A[i] = A[i] + 1;
            for (int j = i + 1; j < k; j++) {
                A[j] = A[j - 1] + 1;
            }
            return true;
        }
    }
    return false;
}

void injekcje(int k, int n) {
    int* A = new int[k];
    int* tab = new int[k];

    for (int i = 0; i < k; i++) {
        A[i] = i;
        tab[i] = i;
    }


    do {

        for (int i = 0; i < k; i++)
        {
            tab[i] = A[i];
        }
        do {
            for (int i = 0; i < k; i++) {
                std::cout << tab[i] + 1 << " ";
            }
            std::cout << '\n';
        } while (nextPermutation(tab, k));

    } while (nextCombination(n, k, A));
}

int main() {
    //funckja z  R^k->R^N
    injekcje(3, 3);
    

    return 0;
}