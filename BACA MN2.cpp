#include <iostream>
#include <iomanip>
using namespace std;

int sgn(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}


double secantMethod(double (*f)(double), double x1, double x2, int M, double eps, double delta) {
    double f1 = f(x1);
    double f2 = f(x2);
    double x0 = NAN;
    while (M > 0) {   
        x0 = x1 - (f1 * (x1 - x2)) / (f1 - f2);
        double f0 = f(x0);
        if (fabs(f0) < eps || fabs(x1-x2) < delta) break;
        x2 = x1; f2 = f1;
        x1 = x0; f1 = f0;
        M--;
    }
    return x0;
}


double bisection(double (*f)(double),double a, double b,int M,double eps, double delta) {
    double c = NAN;
    

        double e = b - a;
        double fa = f(a);
        double fb = f(b);
        for (int k = 1; k <= M; k++)
        {
            e = e / 2;
            c = a + e;
            double fc = f(c);
            if (fabs(e) < delta || fabs(fc) < eps) {
                break;
            }
            if (sgn(fc)!= sgn(fa)) {
                b = c;
                fb = fc;
                if (e < 0.1) {
                    c = secantMethod(f, a, b, M-k, eps, delta);
                    break;
                }
                
            }
            else {
                a = c;
                fa = fc;
                if (e < 0.1) {
                    c = secantMethod(f, a, b, M-k, eps, delta);
                    break;
                }
            }
        }
    
    return c;
}





double findZero(
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int M,                // maksymalna dozwolona liczba wywołań funkcji f
    double eps,           // spodziewana dokładność zera
    double delta          // wystarczający błąd bezwzględny wyniku
) {
    double point;
    if (f(a) * f(b) > 0) {
        // If function values at endpoints have same sign, start secant method
        point = secantMethod(f, a, b, M, eps, delta);
    }
    else if(f(a) * f(b) < 0){
        point = bisection(f, a, b, M, eps, delta);
    }
    else{
        if (f(a) == 0) {
            return a;
        }
        else {
            return b;
        }
    }

    return point;
    
}

double wielomian(double x) { return (((x - 6) * x + 11) * x) - 6; }
double wielomianSinExp(double x)
{
    return ((((x - 6) * x + 11) * x) - 4 + sin(15 * x)) * exp(-x * x);
}
double kwadrat(double x) { return (x * x - 2); }
double kwadrat100(double x) { return 1e100 * (x * x - 2); }
double kwadrat_10(double x) { return 1e-10 * (x * x - 2); }

int main() {
    cout.precision(17);                                               // Spodziewany wynik 
    cout << findZero(wielomian, 0, 4, 20, 1e-15, 1e-14) << endl;      // 1 lub 2 lub 3
    cout << findZero(wielomian, 0, 40, 20, 1e-15, 1e-14) << endl;     // 1 lub 2 lub 3
    cout << findZero(wielomian, 1, 2, 2, 1e-15, 1e-14) << endl;       // 1 lub 2   
    cout << findZero(wielomian, -150, 1.9, 20, 1e-15, 1e-14) << endl; // 1
    cout << findZero(wielomian, 1.5, 2.99, 20, 1e-15, 1e-14) << endl; // 2
    cout << findZero(wielomian, 2.01, 40, 20, 1e-15, 1e-14) << endl;  // 3
    cout << findZero(wielomian, 1.5, 6, 20, 1e-15, 1e-14) << endl;    // 1 lub 2 lub 3

    cout << findZero(wielomianSinExp, -1, 3, 60, 1e-60, 1e-14) << endl;  // 0.43636925909804245
    cout << findZero(wielomianSinExp, -3, 3, 60, 1e-160, 1e-14) << endl; // 0.43636925909804245

    cout << findZero(kwadrat, 0, 4, 15, 1e-11, 1e-14) << endl;          // 1.414213562373095
    cout << findZero(kwadrat100, 0, 4, 15, 1e-11, 1e-14) << endl;       // 1.414213562373095
    cout << findZero(kwadrat_10, 0, 4, 10, 1e-10, 1e-14) << endl;       // każdy punkt z przedziału [1, 1.73205]
    cout << findZero(kwadrat_10, 0, 4, 15, 1e-160, 1e-14) << endl;      // 1.414213562373095
    return 0;
}


