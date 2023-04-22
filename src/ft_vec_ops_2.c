#include "../inc/cub3d.h"

void	pvec(double *vec)
{
	printf("(%.2f)\n(%.2f)\n", vec[X], vec[Y]);
}

/**
 * @brief copy values of array[2] src to dest
 * 
 * @param dest 
 * @param src 
 */
void	cpy_vec(double *dest, double *src)
{
	dest[X] = src[X]; 
	dest[Y] = src[Y];
}

/**
 * @brief subtract dest - src and save in dest
 * 
 * @param dest 
 * @param src 
 */
void	subtract_vec(double *dest, double *src)
{
	dest[X] = dest[X] - src[X];
	dest[Y] = dest[Y] - src[Y];
}