//Karol Bargiel
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
	cout << scientific << setprecision(10);
	float x1, x2, x3;//kolejne wyrazy ciagu
	float q1;
	float q2;
	float P;//iloczyn
	float S;//suma
	int N;//ilosc zestawow danych
	cin >> N;
	while (N-- > 0) {
		cin >> P >> S;
		x2 = cbrt(P);// x1*x1q*x1q^2=x1^3q^3  -->  cbrtf(x1^3q^3)=x1q = x2
		float transformation = (S / x2) - 1; //S = x2/q + x2 + x2*q -> S/x2 = 1/q + 1 + q -> S/x2 - 1 = 1/ q + q 
		float delta = sqrt(powf(transformation, 2) - 4);// mnozac przez q i przenoszac na jedna strone otrzymuje q^2-(S/x2-1)q +1 = 0 gdzie a=1, b=transormation, c=1
		//czyli delta ronwa jest b^2=4ac = transfomation^2-4
		if (delta == 0) {
			q1 = (transformation) / 2;//gdy delta ==0 q=-b/2a
			x1 = x2 / q1;
			x3 = x2 * q1;
			if (x1 < x3) {
				x1 = x2 = x3 = 0;
				cout << x1 << " " << x2 << " " << x3 << endl;
			}
			else {
				cout << x1 << " " << x2 << " " << x3 << endl;
			}
		}
		else if (delta > 0) {
			if (transformation >= 0) { //x^2-2px+q=0 ,if p>=0, jako ze stosuje wzor na 2p dziele p(transoframtion) przez 2
				q1 = transformation/2 + sqrt(powf(transformation/2, 2) - 1);//x1=p+sqrt(p^2-q)
				q2 = 1 / q1;//x1=q/x2
			}
			else {//p<0
				q1 = transformation/2 - sqrt(powf(transformation/2, 2) - 1);//x1=p-sqrt(p^2-q)
				q2 = 1 / q1;//x2=q/x1
			}
			if (x2 / q1 >= x2 * q1) {
				x1 = x2 / q1;
				x3 = x2 * q1;
				cout << x1 << " " << x2 << " " << x3 << endl;
			}
			else if (x2 / q2 >= x2 * q2) {
				x1 = x2 / q2;
				x3 = x2 * q2;
				cout << x1 << " " << x2 << " " << x3 << endl;
			}
			else {
				x1 = x2 = x3 = 0;
				cout << x1 << " " << x2 << " " << x3 << endl;
			}

		}
		else {
			x1 = x2 = x3 = 0;
			cout << x1 << " " << x2 << " " << x3 << endl;
		}
	}
}