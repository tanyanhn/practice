#ifndef DET_BOOLEAN
#define DET_BOOLEAN

class det {
//    double a0[3], a1[3], a2[3];
public:
    const double operator()(const double a00, const double a01, const double a02,
               const double a10, const double a11, const double a12,
               const double a20, const double a21, const double a22){
        return (a00 * a11 * a22) + (a01 * a12 * a20) + (a02 * a10 * a21) -
            (a00 * a12 * a21) - (a01 * a10 * a22) - (a02 * a11 * a20);
    }
}

#endif