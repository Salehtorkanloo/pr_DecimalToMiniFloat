#include<iostream>
#include"Minifloat.h"
using namespace std;
using namespace Minifloat;
int main(){
    while(true){
        float a = 0;
        cin >> a;
        int* b = minifloat::Rep(a);
        for(int i = 0; i < 8 ; ++i){
            cout << b[i];
        }
        delete[] b;
    }
    return 0;
}
