/* Copyright Statement:
 *
 */

//#ifdef _MATH_METHOD_H
//#define _MATH_METHOD_H

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

int divide32(int numerator, int denominator);

unsigned int FFracSqrt(unsigned int x);

unsigned int dsp_fixed_sqrt (unsigned int x);

int abs_value (int x);

int mean_statistics(int *ipSignal, int arraySize, int windowLength, int currentIdx);

int var_statistics(int *ipSignal, int arraySize, int windowLength, int currentIdx);

int index_rollback(int index, int arraySize, int N);

#ifdef __cplusplus
}
#endif


//#endif //end of _MATH_METHOD_H
