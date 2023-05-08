#include "../inc/cub3d.h"

/**
 * @brief calculate a slope from two points in 2d
 * 
 * @param one 
 * @param two 
 * @return double 
 */
double	slope(double *one, double *two)
{
	double	dy;
	double	dx;

	dy = two[Y] - one[Y];
	dx = two[X] - one[X];
	return (dy / dx);
}

/**
 * @brief makes a function from 2 points.
 * puts slope and b value into *func
 * func[M], func[B]
 * 
 * y = mx + b
 * -> b = y - mx
 * 
 * @param one 
 * @param two 
 * @returns -1 if slope is infinite, 0 if everything is ok
 */
int	func_from_points(double *one, double *two, double *func)
{
	double	m;
	double	b;

	if (one[X] == two[X])
		return (-1);
	m = slope(one, two);
	b = one[Y] - (m * one[X]);
	func[M] = m;
	func[B] = b;
	return (0);
}

/**
 * @brief y = mx + b
 * 
 * @param x 
 * @param func 
 * @return double 
 */
double	y_from_x(double x, double *func)
{
	double	y;

	y = (func[M] * x) + func[B];
	return (y);
}

/**
 * @brief y = mx + b
 * x = (y - b)/ m
 * 
 */
double	x_from_y(double y, double *func)
{
	double	x;

	x = (y - func[B]) / func[M];
	return (x);
}

/**
 * @brief calculate with pythagoras the hypothenuse 
 * between the two points
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return double len between two points
 */
double	len_between_two_points(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;
	double	sum;

	dx = x2 - x1;
	dy = y2 - y1;
	sum = (dx * dx) + (dy * dy);
	return (sqrt(sum));
}
