#include "cpu_top.hpp"

// ======================================
// = Global Variables (Memory Pointers) =
// ======================================
// Pointers to Shared DRAM Memory
data_t *SHARED_DRAM;
data_t *SHARED_DRAM_DATA;

int main()
{
SHARED_DRAM = (data_t *)malloc(total_size);
SHARED_DRAM_DATA = (data_t *)(SHARED_DRAM);
copy_config_to_FPGA();
printf("CPU: FPGA DRAM Memory Allocation:\n");
printf("     region: %lu – %lu\n", (long)SHARED_DRAM, (long)(SHARED_DRAM + total_size));
data_t *input_image = (data_t *)malloc(win * hin * sizeof(data_t));
load_prepared_input_image(input_image, "input.bin", win, hin);
// Copy onto FPGA
copy_input_image_to_FPGA(input_image);
return 0;
}

void copy_input_image_to_FPGA(data_t *image) {
  // Input Data goes into Layer 0:
  int win =
  int hin = 
  int input_img_size = win * hin * sizeof(data_t);

  // Info:
  printf("CPU: Copy Input Data: %dKB (input image)\n", input_img_size / 1024);

  // Copy Input Data:
  memcpy(SHARED_DRAM_DATA, image, input_img_size);
}

void load_prepared_input_image(data_t *input_image, const char *filename,int win, int hin) {
  // calculate size of input data
  int num_pixels = win * hin;
  printf("CPU: Loading Input from File %s, %lu kBytes.\n", filename,num_pixels * sizeof(data_t) / 1024);

  // load binary data from file
  FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("ERROR: File %s could not be opened!\n", filename);
    exit(-1);
  }
  fread(input_image, sizeof(data_t), num_pixels, infile);
  fclose(infile);
}
void copy_results_from_FPGA(data_t *results) {

  int result_offset = 0;
  //TODO Fill size here
//   int result_size = ;

  printf("CPU: Copy Results from FPGA DRAM: %d Bytes\n", result_size);

  // Copy Result Data:
  memcpy(results, SHARED_DRAM_DATA + result_offset, result_size);
}