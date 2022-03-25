#ifndef _MY_LAPACK_HPP_
#define _MY_LAPACK_HPP_

extern "C" {

    void dgbsv_(int *N, int *KL, int *KU, int *NRHS, double *AB, int *LDAB, int *IPIV, double *B, int *LDB, int *INFO);
    void sgbsv_(int *N, int *KL, int *KU, int *NRHS, float *AB, int *LDAB, int *IPIV, float *B, int *LDB, int *INFO);

    void dgesv_(int *N, int *NRHS, double *A, int *LDA, int *IPIV, double *B, int *LDB, int *INFO);
    void sgesv_(int *N, int *NRHS, float *A, int *LDA, int *IPIV, float *B, int *LDB, int *INFO);

}

template<typename T>
void gbsv(int *N, int *KL, int *KU, int *NRHS, T *AB, int *LDAB, int *IPIV, T *B, int *LDB, int *INFO);

template<typename T>
void gesv(int *N, int *NRHS, T *A, int *LDA, int *IPIV, T *B, int *LDB, int *INFO);


#endif