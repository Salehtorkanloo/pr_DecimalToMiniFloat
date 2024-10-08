//
// Created by Bobardo2 on 10/1/2024.
//

#ifndef MINIFLOAT_H
#define MINIFLOAT_H

namespace Minifloat {
    class Float8Bit {
        public :
        const static float FP_MAX;
        //Maximum representable value with 1 fractional digit
        const static float FP_MAX_1FRAC;
        const static float FPSubNormal_MAX;
        const static float FPPureFrac_MAX;
        const static float FP_MIN_POS;
        const static float Biased;

        static int* BOfA(int a);
        static int* Rep(float a);
    private:


    };
    typedef Float8Bit minifloat;
}
#endif //MINIFLOAT_H
