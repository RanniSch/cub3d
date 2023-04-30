#include "../inc/cub3d.h"

void	fill_background(int	ceiling, int floor, t_img *img)
{
	int x;
	int y;

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
	char *addr;
	int color;

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
	double dx;
	double visible_wall_px;
	int	amount_of_px_on_display;

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
 * @sum_dy: diff in height from left to right (right display height - left display height)
 * @sum_dx: width on display (right side minus left side)
 */
void	draw_one_vertical_line(t_img *dest, t_img *src, \
	double *start_end_wall, int *corners, int act_x, double dx_for_wall)
{
	double dy_for_wall;
	double act_height;
	double sum_dy;
	double sum_dx;
	int	start_y;
	int	y;
	int	color;

	y = -1;
	
	sum_dy = (corners[Y4] - corners[Y3]) - (corners[Y2] - corners[Y1]);
	sum_dx = corners[X3] - corners[X1]; // unlogische bezeichnung
	act_height = ((sum_dy / sum_dx) * (double)act_x) + (corners[Y2] - corners[Y1]);
	start_y = (DISPLAY_HEIGHT - act_height) / 2;
	dy_for_wall = HEIGHT_WALL / act_height;
	while (++y < act_height)
	{
		color = get_color_from_img(src, (((double)act_x * dx_for_wall) + start_end_wall[START_X_WALL]), (y * dy_for_wall));
		my_mlx_pixel_put(dest, (act_x + corners[X1]), (y + start_y), color);
	}
}