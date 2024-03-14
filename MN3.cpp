#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

void printVector(const double* x, unsigned N) {
    for (unsigned i = 0; i < N; ++i)
        printf("%17.17f ", x[i]);
    printf("\n");
}

int findCurve(FuncPointer f, double* x, unsigned k, double h) {
    double y[2];
    double df[6];
    double fx=NAN, fy=NAN;
    for (int i = 1; i <= k; i++) {
        
        x[2] += h;
        for (unsigned count = 0; count < 1000; count++)
        {
            f(x, y, df);
            // Obliczenie macierzy Jacobiego
            double j11 = df[0];
            double j12 = df[1];
            double j21 = df[3];
            double j22 = df[4];

            // Obliczenie odwrotności macierzy Jacobiego
            double det = j11 * j22 - j12 * j21;
            double inv_j11 = j22 / det;
            double inv_j12 = -j12 / det;
            double inv_j21 = -j21 / det;
            double inv_j22 = j11 / det;

            // Obliczenie wartości funkcji w punkcie x
            double fx = y[0];
            double fy = y[1];

            // Krok: J^{-1} * F(x)
            double sx = (inv_j11 * y[0] + inv_j12 * y[1]);
            double sy = (inv_j21 * y[0] + inv_j22 * y[1]);

            // Przesunięcie punktu
            x[0] -= sx;
            x[1] -= sy;
            count++;
            if (count == 999)
                return i;
            if (fabs(y[0]) < 10e-14 || fabs(y[1]) < 10e-14) {
                break;
            }
            if (isnan(x[0]) || isnan(x[1]))
                return i;
        }
        printVector(x, 3);

        // Aktualizacja punktu
        
    }
    return 0;
}

int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {

    double df[3];
    double y[1];
    double b = x[2];

    for (unsigned i = 1; i <= k1; i++)
    {
        x[1] += h1;
        x[2] = b;
        for (unsigned j = 1; j <= k2; j++)
        {
            x[2] += h2;
            for (unsigned count = 0; count < 1000; count++)
            {
                f(x, y, df);

                x[0] -= (y[0] / df[0]);

                if (fabs(y[0]) < 1e-14) {
                    break;
                }
                if (count == 999) {
                    return i * k1 + j;
                }
            }

            printVector(x, 3);

        }
        cout << endl;
    }

    return 0;

}


int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {
    double df[8];
    //macierz jakobiego
    double y[2];
    //y[]->[f1(x,y,a,b),f2(x,y,a,b)]
    double b = x[3];
    //x[]->[x,y,a,b]

    
    for (unsigned i = 1; i <= k1; i++)
    {
        x[2] += h1;
        x[3] = b;
        for (unsigned j = 1; j <= k2; j++)
        {
            x[3] += h2;
            for (unsigned count = 0; count < 1000; count++) {
                f(x, y, df);
                double j11 = df[0];//a
                double j12 = df[1];//b
                double j21 = df[4];//c
                double j22 = df[5];//d
                //macierz jakobiego 2x2
                //A^-1=1/(ad-bc)*[d -b]
                //               [-c a]

                double det = (j11 - 1) * (j22 - 1) - j12 * j21;


                double inverse_j11 = j22 / det;
                double inverse_j12 = -j12 / det;
                double inverse_j21 = -j21 / det;
                double inverse_j22 = j11 / det;



                double delta_x = (y[0] - x[0]) * inverse_j11 + (y[1] - x[1]) * inverse_j12;
                double delta_y = (y[0] - x[0]) * inverse_j21 + (y[1] - x[1]) * inverse_j22;


                x[0] -= delta_x;
                x[1] -= delta_y;

                if (count == 999)
                    return i * k1 + j;
                if (isnan(x[0]) || isnan(x[1]))
                    return i * k1 + j;
                if (max(fabs(y[0] - x[0]), fabs(y[1] - x[1])) < 1e-14) {
                    break;
                }
            }

            printVector(x, 4);

        }
        std::cout << std::endl;

    }

    return 0;
}

void henon(const double* x, double* y, double* Df) {
    // funkcja dana jest wzorem henon(x,y,a,b) = (1+y-a*x^2,b*x)
    const double x2 = x[0] * x[0];

    y[0] = 1 + x[1] - x[2] * x2;
    y[1] = x[3] * x[0];

    //obliczam pierwszy wiersz macierzy
    Df[0] = -2 * x[2] * x[0];
    Df[1] = 1.;
    Df[2] = -x2;
    Df[3] = 0.;

    //obliczam drugi wiersz macierzy
    Df[4] = x[3];
    Df[5] = 0.;
    Df[6] = 0.;
    Df[7] = x[0];
}

int main() {
    double x[4] = { -1.2807764064044151, -0.6403882032022076, 1.0000000000000000, 0.50000000000000000 };
    findFixedPoints(henon, x, 4, 4, 1. / 16, 1. / 16);
    return 0;
}