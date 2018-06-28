

#ifndef _FPGA_TOP_H_
#define _FPGA_TOP_H_

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
size_t blocksize;
size_t cellsize;
size_t stride;
size_t grad_type; ///< "signed" (0..360) or "unsigned" (0..180) gradient
size_t binning; ///< the number of bins for each cell-histogram
size_t bin_width; ///< size of one bin in degree
size_t n_cells_per_block_y = blocksize/_cellsize;
size_t n_cells_per_block_x = n_cells_per_block_y;
size_t n_cells_per_block = n_cells_per_block_y*_n_cells_per_block_x;
size_t block_hist_size = binning*_n_cells_per_block;
size_t stride_unit = stride/cellsize;
// ====================
// = Type Definitions =
// ====================
typedef ap_uint<2> cacheline_t;  // cache height = 3 or 4 lines
typedef ap_uint<NBITS(MAX_INPUT_PER_LAYER)> imgdramoffset_t;
typedef ap_uint<NBITS(MAX_IMAGE_CACHE_SIZE)> imgcacheaddr_t;
typedef ap_uint<NBITS(MAX_IMAGE_CACHE_SIZE / 4)> pixelperrow_t;

typedef ap_int<NBITS(MAX_DIMENSION) + 2> coordinate_t;

