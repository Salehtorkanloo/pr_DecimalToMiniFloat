//
// Created by Bobardo2 on 10/1/2024.
//
#include"Math.h"
float Math::Abs(const float& a){
    if(a<0)
        return -a;

    return a;
}
int Math::remainderEqual(int &a, const int& d){
    int remainder = a%d;
    a/=d;
    return remainder;
}
int Math::multiplyExtraEqual(float &a, const int& c){
    if(a >= 1)
        return -1;
    a*=c;
    char extra = a>=1? 1 : 0;
    a = a - Abs((int)a);
    return extra;
}
