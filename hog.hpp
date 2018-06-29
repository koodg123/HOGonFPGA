

#ifndef _HOG_FEATURE_H_
#define _HOG_FEATURE_H_

#include <cassert>
#include <cmath>
#include "ap_int.h"


#ifdef __SYNTHESIS__
#include <ap_utils.h>
#include <hls_math.h>
#endif


// Number of Image Cache Lines (need 3, use 4 for simplified Addressing HW)
const int NUM_IMG_CACHE_LINES = 4;
// Number of Processing Elements
const int N_PE = 8;

// ====================
// = Type Definitions =
// ====================
typedef ap_uint<2> cacheline_t;  // cache height = 3 or 4 lines


void hog(data_t *SHARED_DRAM, unsigned int input_offset);
void load_image(data_t *SHARED_DRAM);


