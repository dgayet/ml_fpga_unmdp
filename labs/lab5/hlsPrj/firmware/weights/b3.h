//Numpy array shape [5]
//Min -0.125000000000
//Max 0.125000000000
//Number of zeros 3

#ifndef B3_H_
#define B3_H_

#ifndef __SYNTHESIS__
bias3_t b3[5];
#else
bias3_t b3[5] = {0.125, 0.000, 0.000, 0.000, -0.125};
#endif

#endif
