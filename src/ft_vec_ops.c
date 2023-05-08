#include "../inc/cub3d.h"

/**
 * @brief calculates the length of the vector
 * and returns as double
 * 
 * @param vec 
 * @return double
 */
double	len_vec(double *vec)
{
	double	x;
	double	y;
	double	sum;

	x = vec[X] * vec[X];
	y = vec[Y] * vec[Y];
	sum = x + y;
	return (sqrt(sum));
}

/**
 * @brief normes the vector to a lemgth of 1
 * 
 * @param vec 
 */
void	norm_vec(double *vec)
{
	double	v_len;

	v_len = len_vec(vec);
	vec[X] = vec[X] / v_len;
	vec[Y] = vec[Y] / v_len;
}

/**
 * @brief rotates vec to rot degrees
 * 
 * @param vec Vector with x and y
 * @param rot degrees to rotate
 */
void	rot_vec(double *vec, double rot)
{
	double	r11;
	double	r12;
	double	r21;
	double	r22;
	double	buf[2];

	buf[X] = vec[X];
	buf[Y] = vec[Y];
	r11 = cos(rot * PI / 180);
	r12 = -sin(rot * PI / 180);
	r21 = sin(rot * PI / 180);
	r22 = cos(rot * PI / 180);
	vec[X] = r11 * buf[X] + r12 * buf[Y];
	vec[Y] = r21 * buf[X] + r22 * buf[Y];
}

/**
 * @brief multiplicate vec with facator and save in vec
 * 
 * @param vec 
 * @param factor 
 */
void	mult_vec(double *vec, double factor)
{
	vec[X] = vec[X] * factor;
	vec[Y] = vec[Y] * factor;
}

/**
 * @brief add dest with src and save in dest
 * 
 * @param dest 
 * @param src 
 */
void	add_vec(double *dest, double *src)
{
	dest[X] = dest[X] + src[X];
	dest[Y] = dest[Y] + src[Y];
}
