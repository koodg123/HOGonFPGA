
#include "hog_feature.hpp"

#pragma HLS INTERFACE m_axi depth = DRAM_DEPTH port = SHARED_DRAM offset = \
    slave bundle = memorybus register
#pragma HLS INTERFACE s_axilite port = layer bundle = axilite  register
#pragma HLS INTERFACE s_axilite port = num_weights bundle = axilite  register
#pragma HLS INTERFACE s_axilite port = weights_offset bundle = axilite  register
#pragma HLS INTERFACE s_axilite port = input_offset bundle = axilite  register
#pragma HLS INTERFACE s_axilite port = return bundle = axilite  register



