//Karol Bargiel

#include <iostream>
using namespace std;
#include <vector>

// Funkcja obliczająca rozmiar maksymalnego kwadratu złożonego z '1' w macierzy binarnej.
int maximalSquare(vector<vector<char> >& matrix) {
    int row = matrix.size(); // Pobranie liczby wierszy w macierzy.
    int col = matrix[0].size(); // Pobranie liczby kolumn w macierzy.
    vector<int> prev(col); // Wektor przechowujący poprzedni wiersz.
    vector<int> curr(col); // Wektor przechowujący bieżący wiersz.
    int maxi = 0; // Zmienna przechowująca maksymalny rozmiar kwadratu.

    // Inicjalizacja pierwszego wiersza i obliczanie maksymalnego rozmiaru.
    for (int j = 0; j < col; j++) {
        prev[j] = matrix[0][j] - '0';
    // Operator || (logical OR) wykonuje się w taki sposób, że jeśli jedna z wartości jest true,
    // to wynik będzie true. Działa to jako sprawdzenie, czy w pierwszym wierszu jest co najmniej jedno '1'.
        maxi = maxi || prev[j];
    }

    // Przechodzenie przez pozostałe wiersze macierzy.
    for (int i = 1; i < row; i++) {
        curr[0] = matrix[i][0] - '0';
        maxi = max(maxi, curr[0]);

        // Przechodzenie przez pozostałe kolumny w bieżącym wierszu.
        for (int j = 1; j < col; j++) {
            // Obliczanie długości boku maksymalnego kwadratu w aktualnym punkcie.
            if (matrix[i][j] == '1')
                curr[j] = 1 + min(min(curr[j - 1], prev[j - 1]), prev[j]);
            else
                curr[j] = 0;

            // Aktualizacja maksymalnego rozmiaru kwadratu.
            maxi = max(maxi, curr[j]);
        }

        // Przesunięcie bieżącego wiersza do poprzedniego wiersza.
        prev = curr;
    }

    return maxi; // Zwrócenie maksymalnego rozmiaru kwadratu.
}

int main() {
    int Z; // Liczba zestawów danych.
    cin >> Z;

    // Przechodzenie przez wszystkie zestawy danych.
    for (int k = 0; k < Z; k++) {
        int H, W; // Wysokość i szerokość macierzy.
        cin >> H >> W;
        vector<vector<char> > tab(H, vector<char>(W)); // Inicjalizacja macierzy.

        // Wczytywanie wartości do macierzy.
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                char znak;
                cin >> znak;

                // Konwersja znaku 'o' na '1' i pozostałych znaków na '0'.
                if (znak == 'o') {
                    tab[i][j] = '1';
                }
                else {
                    tab[i][j] = '0';
                }
            }
        }

        // Wywołanie funkcji obliczającej maksymalny rozmiar kwadratu i wypisanie wyniku.
        int result = maximalSquare(tab);
        cout << result << '\n';
    }

    return 0;
}
