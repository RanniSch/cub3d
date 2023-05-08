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

double	dot_prod_vec(double *one, double *two)
{
	return ((one[X] * two[X]) + (one[Y] * two[Y]));
}

double	calc_angle_vec(double *one, double *two)
{
	double	dot_prod;
	double	len_one;
	double	len_two;

	dot_prod = dot_prod_vec(one, two);
	len_one = len_vec(one);
	len_two = len_vec(two);
	return (acos(dot_prod / (len_one * len_two)));
}