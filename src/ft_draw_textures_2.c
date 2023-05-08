#include "../inc/cub3d.h"

void	fill_background(int ceiling, int floor, t_img *img)
{
	int	x;
	int	y;

	y = -1;
	while (++y < DISPLAY_HEIGHT / 2)
	{
		x = -1;
		while (++x < DISPLAY_WIDTH)
			my_mlx_pixel_put(img, x, y, ceiling);
	}
	--y;
	while (++y < DISPLAY_HEIGHT)
	{
		x = -1;
		while (++x < DISPLAY_WIDTH)
			my_mlx_pixel_put(img, x, y, floor);
	}
}

int	get_color_from_img(t_img *img, double x, double y)
{
	char	*addr;
	int		color;

	addr = img->addr + ((int)(y) % img->height * img->line_length + \
		(int)(x) % img->width * (img->bits_per_pixel / 8));
	color = *(int *)addr;
	return (color);
}

t_img	*get_wall_ptr(int width_pixel, int **dist_info, t_info *info)
{
	int	wall;

	wall = dist_info[2][width_pixel];
	if (wall == NORTH)
		return (info->north);
	if (wall == SOUTH)
		return (info->south);
	if (wall == WEST)
		return (info->west);
	if (wall == EAST)
		return (info->east);
	return (NULL);
}

/**
 * @brief calc dx_for_wall -> how many px on the wall do we have to go
 * for one px on the display ?
 * -> visible wall px / amount of px on display
 * 
 */
double	calc_dx_for_wall(double *start_end_wall, int *corners)
{
	double	dx;
	double	visible_wall_px;
	int		amount_of_px_on_display;

	visible_wall_px = start_end_wall[END_X_WALL] - \
		start_end_wall[START_X_WALL];
	amount_of_px_on_display = corners[X3] - corners[X1];
	dx = visible_wall_px / (double)amount_of_px_on_display;
	return (dx);
}

/**
 * @brief draw one vertical line of a wall into img in respect to corners[]
 * calc act_hight per intercept theorem 
 * calc dy_for_wall -> how many px in the wall texture do I have to go
 * 	   for one px on the display?
 * calc start_y
 * while
 * 		get color of texture
 * 		my_mlx_pixel_put()
 * @sum_dy: diff in height from left to right 
 * 			(right display height - left display height)
 * @sum_dx: width on display (right side minus left side) + 1
 * 			because when you have a far away wall with width of 1
 * 			it would be f.e. X3:532 - X1:532. But it should be 1
 * @act_height: tells how high the wall at this x value has to be
 * 				the first part is the intercept theorem -> when the wall 
 * 				is getting bigger to the right how much do I have to add
 * 				to the height at this x value. Y2 - Y1 is the basic height
 * 				from the most left part of the wall.
 * @val: has val[START_Y], val[Y], val[COLOR]
 */
void	draw_one_vertical_line(t_img **img_ptr, double *start_end_wall, \
	int *corners, int act_x)
{
	double	dy_for_wall;
	double	act_height;
	double	sum_dy;
	double	sum_dx;
	int		val[3];

	val[Y] = -1;
	sum_dy = (corners[Y4] - corners[Y3]) - (corners[Y2] - corners[Y1]);
	sum_dx = corners[X3] - corners[X1] + 1;
	act_height = ((sum_dy / sum_dx) * (double)act_x) + \
		(corners[Y2] - corners[Y1]);
	val[START_Y] = (DISPLAY_HEIGHT - act_height) / 2;
	dy_for_wall = HEIGHT_WALL / act_height;
	while (++val[Y] < act_height)
	{
		val[COLOR] = get_color_from_img(img_ptr[SRC], \
			(((double)act_x * start_end_wall[DX_FOR_WALL]) + \
			start_end_wall[START_X_WALL]), (val[Y] * dy_for_wall));
		if ((val[Y] + val[START_Y]) >= 0 && (val[Y] + val[START_Y]) \
			< DISPLAY_HEIGHT)
			my_mlx_pixel_put(img_ptr[DEST], (act_x + corners[X1]), \
				(val[Y] + val[START_Y]), val[COLOR]);
	}
}
