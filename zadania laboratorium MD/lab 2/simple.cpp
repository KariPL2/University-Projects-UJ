#include <iostream>
using namespace std;

// Funkcja ma generowac ciag liczb pseudolosowych o dlugosci seqLength
// wg. algorytmu podanego na zajeciach.

void pseudorandomSeq(long long a, long long c, long long modulus, long long seed, int seqLength)
{
    if (seqLength == 0) {
        return;
    }
  
    seed = ((a * seed + c) % modulus); //d)% 32768; //przesuniecie o 15 bitow;
    cout << seed << "  ";
    pseudorandomSeq(a, c, modulus, seed, seqLength-1);
}


int main()
{

    long long a = 22695477;
    long long c = 1;
    long long modulus = 4294967296;
    long long seed = 1;
    int seqLength = 20;
    pseudorandomSeq(a, c, modulus, seed, seqLength);


}
/*
kolejne outputy:
a)5  1  5  1  5  1  5  1  5  1  5  1  5  1  5  1  5  1  5  1
b)17  289  305  65  81  353  369  129  145  417  433  193  209  481  497  257  273  33  49  321
c)22695478  2156045615  2867233980  71484141  2911408402  2613937339  1153135800  420428313  1503962414  4187371143  590113780  3101602181  234047114  1499440787  3359393392  89175345  2502193446  3898671327  3619627052  1641484573




*/