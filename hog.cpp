
#include "hog.hpp"
extern const var_t s_row, s_col,c_row, c_col,b_row, b_col,n_cells_row,n_cells_col, orient,n_blocks_row,n_blocks_col;
extern data_t IBRAM[s_row][s_col], GRAD[s_row][s_col], ORIENTATIONS[n_cells_row][n_cells_col][orient];
extern data_t NORM_BLOCKS[n_blocks_row][n_blocks_col][b_row][b_col][orient];
extern cacheline_t curr_img_cache_line;
extern imgcacheaddr_t curr_img_cache_addr;
extern imgcacheaddr_t line_width;
extern imgdramoffset_t loads_left;
extern dimension_t width_in;
extern dimension_t height_in;

void hog(data_t *SHARED_DRAM, unsigned int input_offset)
{
#pragma HLS INTERFACE m_axi depth = DRAM_DEPTH port = SHARED_DRAM offset = slave bundle = memorybus register
#pragma HLS INTERFACE s_axilite port = input_offset bundle = axilite  register
#pragma HLS INTERFACE m_axi depth = DRAM_DEPTH port = results offset = master bundle = memorybus register

printf("FPGA: Computing ");
load_image()
//firstsstage() //Optional Not Implemented Right Now
secondstage();
threestage();
fourthstage();
writeback();
}
void load_image(data_t *SHARED_DRAM)
{
int pixel_offset=0;
//Load Row Here
#pragma HLS inline
#pragma HLS RESOURCE variable = IBRAM core = RAM_S2P_BRAM latency=2

for (coordinate_t x = 0; x < width_in; x++) {
#pragma HLS LOOP_TRIPCOUNT min = 4 max = 32 
 data_t pixel_from_ram = reg(SHARED_DRAM[pixel_offset])
    pixel_offset++;
	}

}
void secondstage()
{
//Implemented for a gray image
//Compute Gradients for the Image
#pragma HLS RESOURCE variable = GRAD core = RAM_S2P_BRAM latency=2
// Calculate Row GRADIENT
// get image row_buffer
for(int i=0; i<s_col;i++)
{
    g_row[0][i] = 0;
    g_row[s_row-1][i] = 0;
    for (int j=1;j<s_row-1;j++)
    g_row[j][i] = img[j+1][i] - img[j-1][i];
}
// Calculate Column GRADIENT
for(int i=0; i<s_row;i++)
{
    g_col[i][0] = 0;
    g_col[i][s_col-1] = 0;
    for (int j=1;j<s_row-1;j++)
    g_row[i][j] = img[i][j+1] - img[i][j-1];
}
}

void thirdstage()
{
#pragma HLS RESOURCE variable = ORIENTATIONS core = RAM_S2P_BRAM latency=2


}

void fourthstage()
{
#pragma HLS RESOURCE variable = NORM_BLOCKS core = RAM_S2P_BRAM latency=2
for r in range(n_blocks_row):
    for c in range(n_blocks_col):
        block = orientation_histogram[r:r + b_row, c:c + b_col, :]
        normalized_blocks[r, c, :] = block / (np.sum(np.abs(block)) + eps) #eps=1e-5
for(int r=0;r<n_blocks_row;r++)
    for(int c=0;c<n_blocks_col;c++)
       block=getblock(r,c);
       norm=sumblock(r,c);
       normalized_blocks=block/norm;
}
void writetoDRAM()
{
int result_offset = 0;
int result_size = sizeof(data_t)*n_blocks_row*n_blocks_col*b_row*b_col*orient;    
    
}