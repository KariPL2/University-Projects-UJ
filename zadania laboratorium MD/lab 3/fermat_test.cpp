#include <iostream>
#include <time.h>
#include <gmpxx.h>


using namespace std;
typedef mpz_class bigInteger;

/* LICZBY PESUDOLOSWE */
gmp_randclass rr(gmp_randinit_default);    

void initalize_random()
{
    rr.seed(time(NULL));
}

bigInteger randomInt(bigInteger a, bigInteger b)
{    
    return a + rr.get_z_range(b-a+1);     
}

// Liczby pseudolosowe w GMP: Najpierw nalezy zainicjalizowac generator
// za pomoca funkcji initialize_random()
// a nastepnie mozna juz uzywac funkcji randomInt, ktora zwraca losowa
// liczbe calkowita z przedzialu [a,b]

bigInteger ModPower(bigInteger a, bigInteger b, bigInteger n)
{
    bigInteger z = a % n ;
    bigInteger y = 1;
    bigInteger m = b;
    while (m > 0) {

        if (m % 2 == 1)
            y = (y * z) % n;
        
        m=m/2;
        z = (z * z) % n;
    }
    return y;
}
bigInteger GCD(bigInteger a, bigInteger b){
while(b!=0){
    bigInteger temp=b;
    b=a%b;
    a=temp;
}
return a;

}


void fermat_test(bigInteger n, int no_of_trials)
{
    bigInteger i=0;
    while(i<=no_of_trials){
        bigInteger rand=randomInt(2,n-1);
        if(ModPower(rand,n-1,n)!=1){
            std::cout<<rand<<"\n";
            std::cout<<"GCD:"<<GCD(rand,n)<<"\n";
            
        }
        i++;
    }
    
}

bool MillerRabinTest(bigInteger num){
    int i=0;
    while(i<15){
        std::cout<< "TEST";
    bigInteger a=randomInt(2,num-1);

    bigInteger r=0;
    bigInteger s=num-1;
    while(s%2==0){
        r++;
        s/=2;
    }
    bigInteger x=ModPower(a,s,num);
    if(x == 1 || x== num - 1){
        return true;
    }
    for(bigInteger i=1; i<r;i++){
        x=ModPower(x,2,num);
        if(x==num-1){
            return true;
        }
    }
    return false;
    i++;
    }
}
bigInteger Power(bigInteger a, bigInteger b)
{
    bigInteger z = a ;
    bigInteger y = 1;
    bigInteger m = b;
    while (m > 0) {

        if (m % 2 == 1)
            y = (y * z);
        
        m=m/2;
        z = (z * z);
    }
    return y;
}




int main()
{
    initalize_random();
    bigInteger b("22701801293785014193580405120204586741061235962766583907094021879215171483119139894870133091111044901683400949483846818299518041763507948922590774925466088171879259465921026597046700449819899096862039460017743094473811056991294128542891880855362707407670722593737772666973440977361243336397308051763091506836310795312607239520365290032105848839507981452307299417185715796297454995023505316040919859193718023307414880446217922800831766040938656344571034778553457121080530736394535923932651866030515041060966437313323672831539323500067937107541955437362433248361242525945868802353916766181532375855504886901432221349733");
    bigInteger N("1590231231043178376951698401");
    //fermat_test(N,20);
    for(int i=0;i<15;i++){
        std::cout<<" F"<<i<<":"<<"\n";
        if(MillerRabinTest(Power(2,Power(2,i))+1)){
            std::cout<<"pierwsza \n";
        }
        else{
            std::cout<<"zlozona \n";
        }
 

    }


}