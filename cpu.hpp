#ifndef _FPGA_SIMULATOR_H_
#define _FPGA_SIMULATOR_H_

// ========================
// = Standard C Libraries =
// ========================
#include <cstdio>     // printf
#include <ctime>      // time() for random seed
#include <cmath>      // fabs, fmax, ...
#include <vector>     // std::vector for softmax calculation
#include <algorithm>  // sort, reverse (on std::vector)

// ==============
// = Unit Tests =
// ==============
#include "test.hpp"  // Unit Tests for Modules

// ==================
// = FPGA Algorithm =
// ==================
#include "hog.hpp"  // top-level FPGA module

// ===========================================
// = CPU-Side Functions for SqueezeNetOnFPGA =
// ===========================================

void load_prepared_input_image(data_t *input_image, const char *filename,int win, int hin);
void copy_input_image_to_FPGA(data_t *image);
void copy_results_from_FPGA(data_t *results);
int main();
#endif