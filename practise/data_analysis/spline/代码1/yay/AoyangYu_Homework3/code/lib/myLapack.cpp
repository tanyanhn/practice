#include "myLapack.hpp"

template<>
void gbsv<double>(int *N, int *KL, int *KU, int *NRHS, double *AB, int *LDAB, int *IPIV, double *B, int *LDB, int *INFO) {
    dgbsv_(N, KL, KU, NRHS, AB, LDAB, IPIV, B, LDB, INFO);
}

template<>
void gbsv<float>(int *N, int *KL, int *KU, int *NRHS, float *AB, int *LDAB, int *IPIV, float *B, int *LDB, int *INFO) {
    sgbsv_(N, KL, KU, NRHS, AB, LDAB, IPIV, B, LDB, INFO);
}

template<>
void gesv<double>(int *N, int *NRHS, double *A, int *LDA, int *IPIV, double *B, int *LDB, int *INFO) {
    dgesv_(N, NRHS, A, LDA, IPIV, B, LDB, INFO);
}

template<>
void gesv<float>(int *N, int *NRHS, float *A, int *LDA, int *IPIV, float *B, int *LDB, int *INFO) {
    sgesv_(N, NRHS, A, LDA, IPIV, B, LDB, INFO);
}