
#include "hog.hpp"
extern const var_t s_row, s_col,c_row, c_col,b_row, b_col,n_cells_row,n_cells_col, orient,n_blocks_row,n_blocks_col;
extern data_t IBRAM[s_row][s_col], GRAD[s_row][s_col];
extern data_t orientation_histogram[n_cells_row][n_cells_col][orient],magnitude[][],orientation[][];
extern data_t norm_block[n_blocks_row][n_blocks_col][b_row][b_col][orient];
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
int i,j,k,r,c,n;
n=180/orient;
r_0 = cell_rows / 2 ;
c_0 = cell_columns / 2; 
#pragma HLS RESOURCE variable = ORIENTATIONS core = RAM_S2P_BRAM latency=2
cc = c_row * n_cells_row;
cr = c_col * n_cells_col;
for(i=0;i<orient;i++)
    {
    start=n*i;
    end=start+n;
    c = c_0;r = r_0;r_i = 0;c_i = 0;
    while (r < cc):
            {    c_i = 0
                c = c_0
                while c < cr:
                   {
                    orientation_histogram[r_i, c_i, i] = cell_hog(r,c,start,end)
                    c_i += 1
                    c += c_col
                   }
                r_i += 1
                r += c_row
            }      
    }
}
void compute_magnitude()
{
magnitude = np.hypot(gradient_columns, gradient_rows)
orientation = np.rad2deg(np.arctan2(gradient_rows, gradient_columns)) % 180
}

void cell_hog(r,c,start,end)
{
#pragma HLS inline
data_t total=0;
for (int i=-c_row/2; i<c_row/2; i++)
    {
    cri = r + i;
    if (cri < 0 or cri >= s_row):
        continue

    for (int j=-c_col/2; j<c_col/2; j++)
        {
        cci = c + j;
        if (cci < 0 or cci >= s_col or orientation[cri][cci]>= end or 
        orientation[cri][cci]< start)
        continue
        total += magnitude[cri, cci];
        }
    } 
return total / (c_row * c_col)
}            
void fourthstage()
{
int i,j,k;
#pragma HLS RESOURCE variable = NORM_BLOCKS core = RAM_S2P_BRAM latency=2
for(int r=0;r<n_blocks_row;r++)
    for(int c=0;c<n_blocks_col;c++)
        {
            sum=0;
          for ( i =0;i<b_row;i++)
            for( j=0;j<b_col;j++)
                for( k=0;k<orient;k++)
                   { block[i][j][k]=orientation_histogram[i+r][j+c][k]; 
                    if(orientation_histogram[i+r][j+c][k]>0)
                        sum +=orientation_histogram[i+r][j+c][k];
                    else
                        sum-=orientation_histogram[i+r][j+c][k];
                   }   
            sum+=0.00001;
        for (i =0;i<b_row;i++)
            for( j=0;j<b_col;j++)
                for(k=0;k<orient;k++)
                {   normalized_blocks[r][c][i][j][k]=block[i][j][k]/sum;
                }          
        }      
}
void writetoDRAM()
{
int result_offset = 0;
int result_size = sizeof(data_t)*n_blocks_row*n_blocks_col*b_row*b_col*orient;    
    
}


