#include<iostream>
#include<cmath>
#include<iomanip>
#include<iterator>
using namespace std;
const float FP_MAX = 240;
//Maximum representable value with 1 fractional digit
const float FP_MAX_1FRAC = 7.5f;
const float FPSubNormal_MAX = 0.013671875;
const float FPPureFrac_MAX = 0.9375;
const float FP_MIN_POS = 0.015625;
const float Biased = 7;

float Abs(const float& a){
    if(a<0)
        return -a;
    return a;
}
int remainderEqual(int &a, const int& d){
    int remainder = a%d;
    a/=d;
    return remainder;
}
int multiplyExtraEqual(float &a, const int& c = 2){
    if(a >= 1)
        return -1;
    a*=c;
    char extra = a>=1? 1 : 0;
    a = a - Abs((int)a);
    return extra;
}
int* BOfA(int a){
    int* _8_bit_b = new int[8]{0,0,0,0,0,0,0,0};
    for(int i = 7; i >= 0; --i){
        _8_bit_b[i] = remainderEqual(a, 2);
        if(a <= 0)
            break;
    }
    return _8_bit_b;
}

int* Rep(float a){
    if(a > FP_MAX){
        //Overflow
        return nullptr;
    }
    else if(a < -FP_MAX){
        //Underflow
        return nullptr;
    }

    char s = a > 0? 0 : 1;
    int* _3_bit_significand = new int[3]{0,0,0};
    int* _4_bit_exp = new int[4]{0,0,0,0};
    int* _8_bit_binary = new int[8]{0,0,0,0,0,0,0};

    if(a == 0){
        return new int[8]{0,0,0,0,0,0,0,0};
    }
    else if(a == -0){
        return new int[8]{1,0,0,0,0,0,0,0};
    }

    int* _9_bitBinary = new int[9]{0,0,0,0,0,0,0,0,0};
    if(Abs(a) <= FPPureFrac_MAX && Abs(a) >= FP_MIN_POS ){
        //Pure fractional
        char firstLeading1Pos = 127;
        float numberToExtract = Abs(a);
        for(int i = 0; i < 9; ++i){
            _9_bitBinary[i] = multiplyExtraEqual(numberToExtract);

            if(_9_bitBinary[i] == 1 && firstLeading1Pos == 127){
                firstLeading1Pos = i+1;
            }
            if(numberToExtract == 1)
                break;
        }
        for(int j4 = 0 ; j4 < 3; ++j4){
            char _9_bit_pos = j4 + firstLeading1Pos;
            if(_9_bit_pos >= 9)
                break;
            _3_bit_significand[j4] = _9_bitBinary[_9_bit_pos];
        }
        int biasedExp = -(firstLeading1Pos) +Biased;
        for(char j2 = 3; j2 >= 0; --j2){
            _4_bit_exp[j2] = remainderEqual(biasedExp,2);
            if(biasedExp <= 0)
                break;
        }
        std::copy(_4_bit_exp, _4_bit_exp+4, _8_bit_binary + 1);
        std::copy(_3_bit_significand, _3_bit_significand+3, _8_bit_binary + 5);
        return _8_bit_binary;
    }
    else if(Abs(a) < FP_MIN_POS && a > 0){
        //Subnormal
        char lastLeading0Pos = 127;
        float numberToExtract = Abs(a);
        for(int i = 0; i < 9; ++i){
            _9_bitBinary[i] = multiplyExtraEqual(numberToExtract);
            //cout << _9_bitBinary[i];
            if(_9_bitBinary[i] == 1 && lastLeading0Pos == 127){
                if(lastLeading0Pos >= 7)
                    lastLeading0Pos = 6;
                else
                    lastLeading0Pos = i;
            }
            if(numberToExtract == 1)
                break;
        }
        //cout << endl;
        for(int j4 = 0 ; j4 < 3; ++j4){
            char _9_bit_pos = j4 + lastLeading0Pos;
            if(_9_bit_pos >= 9)
                break;
            _3_bit_significand[j4] = _9_bitBinary[_9_bit_pos];
        }
        _4_bit_exp = new int[4]{0,0,0,0};

        std::copy(_4_bit_exp, _4_bit_exp+4, _8_bit_binary + 1);
        std::copy(_3_bit_significand, _3_bit_significand+3, _8_bit_binary + 5);
        return _8_bit_binary;
    }
    else{
        _8_bit_binary = BOfA(Abs(a));
        char n = 0;
        int startFracPos = -1;
        for(char i = 0 ; i < 8; ++i){
            if(_8_bit_binary[i] == 1){
                n = i;
                for(char j = 0; j < 3; ++j){
                    char bPos = n+1+j;
                    if(bPos > 7)
                        break;
                    _3_bit_significand[j] = _8_bit_binary[bPos];
                }
                int biasedExp = (7-n)+Biased;
                startFracPos = 7-n;
                for(char j2 = 3; j2 >= 0; --j2){
                    _4_bit_exp[j2] = remainderEqual(biasedExp,2);
                    if(biasedExp <= 0)
                        break;
                }
                break;
            }
        }
        if(Abs(a) <= FP_MAX_1FRAC){
            float fracValue = Abs(a) - Abs((int)a);
            for(char c = startFracPos ; c < 3; ++c){
                _3_bit_significand[c] =
                    multiplyExtraEqual(fracValue);

                if(fracValue == 0)
                    break;

            }

        }
        std::copy(_4_bit_exp, _4_bit_exp+4, _8_bit_binary + 1);
        std::copy(_3_bit_significand, _3_bit_significand+3, _8_bit_binary + 5);
        return _8_bit_binary;
    }


}
int main(){

    while(true){
        float a = 0;
        cin >> a;
        int* b = Rep(a);
        for(int i = 0; i < 8 ; ++i){
            cout << b[i];
        }
    }
    return 0;
}
