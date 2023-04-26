#include "../inc/cub3d.h"

/**
 * @brief goes through the raycast_scan (dist_info) and looks for
 * the value where the next tile starts
 * 
 * @param act_tile_display_y 
 * @param info 
 * @return int number where the next tile starts in dist_info 
 * (same as width pixel on display)
 */
int	next_tile_on_display_x(int act_x_on_display, t_info *info)
{
	int act_tile_map_x;
	int act_tile_map_y;
	int act_wall_facing_direction;

	act_tile_map_x = info->dist_info[X][act_x_on_display];
	act_tile_map_y = info->dist_info[Y][act_x_on_display];
	act_wall_facing_direction = info->dist_info[2][act_x_on_display];
	while (++act_x_on_display < DISPLAY_WIDTH)
	{
		if (info->dist_info[X][act_x_on_display] != act_tile_map_x || \
			info->dist_info[Y][act_x_on_display] != act_tile_map_y || \
			info->dist_info[2][act_x_on_display] != act_wall_facing_direction) 
			return (act_x_on_display);
	}
	return (act_x_on_display);
}

void	calc_end_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info)
{
	int	end_x;

	end_x = corners[X3];
	if (info->dist_info[2][width_pixel] == NORTH)
		start_end_wall[END_X_WALL] = ((double)info->dist_info[EXACT_X]\
		[end_x] / 1000) - (double)info->dist_info[X][end_x];
	else if (info->dist_info[2][width_pixel] == SOUTH)
		start_end_wall[END_X_WALL] = (double)info->dist_info[X][end_x] \
		+ 1 - ((double)info->dist_info[EXACT_X][end_x] / 1000);
	else if (info->dist_info[2][width_pixel] == WEST)
		start_end_wall[END_X_WALL] = ((double)info->dist_info[EXACT_Y]\
		[end_x] / 1000) - (double)info->dist_info[Y][end_x];
	else if (info->dist_info[2][width_pixel] == EAST)
		start_end_wall[END_X_WALL] = (double)info->dist_info[Y][end_x] \
		+ 1 - ((double)info->dist_info[EXACT_Y][end_x] / 1000);
	start_end_wall[END_X_WALL] *= WIDTH_WALL;
}

void	calc_start_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info)
{
	int	start_x;

	start_x = corners[X1];
	if (info->dist_info[2][width_pixel] == NORTH)
		start_end_wall[START_X_WALL] = ((double)info->dist_info[EXACT_X]\
			[start_x] / 1000) - (double)info->dist_info[X][start_x];
	else if (info->dist_info[2][width_pixel] == SOUTH)
		start_end_wall[START_X_WALL] = (double)info->dist_info[X][start_x] \
		+ 1 - ((double)info->dist_info[EXACT_X][start_x] / 1000);
	else if (info->dist_info[2][width_pixel] == WEST)
		start_end_wall[START_X_WALL] = ((double)info->dist_info[EXACT_Y]\
		[start_x] / 1000) - (double)info->dist_info[Y][start_x];
	else if (info->dist_info[2][width_pixel] == EAST)
		start_end_wall[START_X_WALL] = (double)info->dist_info[Y][start_x] \
		+ 1 - ((double)info->dist_info[EXACT_Y][start_x] / 1000);
	start_end_wall[START_X_WALL] *= WIDTH_WALL;
}

/**
 * @brief top left corner is 1 -> X1, Y1
 * bottom left corner is 2, top right is 3 bottom right is 4
 * 
 * Display grid starts in the top left corner. x goes to the right,
 * y goes to the bottom.
 * @param corners 
 * @param width_pixel 
 * @param dist_arr 
 */
void	calc_corners_of_wall(int *corners, int width_pixel, \
	double *dist_arr, t_info *info)
{
	double height_on_x_value;
	double buf;

	height_on_x_value = DISPLAY_HEIGHT * FACTOR_WALL_HEIGHT / dist_arr[width_pixel];
	corners[X1] = width_pixel;
	corners[X2] = width_pixel;
	buf = round((DISPLAY_HEIGHT - height_on_x_value) / 2);
	corners[Y1] = (int)(buf + 0.1);
	buf = corners[Y1] + height_on_x_value;
	corners[Y2] = (int)(buf + 0.1);
	width_pixel = next_tile_on_display_x(width_pixel, info) - 1;
	height_on_x_value = DISPLAY_HEIGHT * FACTOR_WALL_HEIGHT / dist_arr[width_pixel];
	corners[X3] = width_pixel;
	corners[X4] = width_pixel;
	buf = round((DISPLAY_HEIGHT - height_on_x_value) / 2);
	corners[Y3] = (int)(buf + 0.1);
	buf = corners[Y3] + height_on_x_value;
	corners[Y4] = (int)(buf + 0.1);
}

/**
 * @brief
 * calc corners of Wall
 * 
 * draw_one_vertical_line
 * 
 * draw_vertical_wall_line till the end or till the next comes
 * 
 * @param info 
 * @param width_pixel set to 0 when calling the function
 */
void	draw_wall_textures(t_info *info, int width_pixel)
{
	// int	width_pixel;
	int	act_x;
	int	corners[8];
	double start_end_wall[2];
	double	dx_for_wall;
	t_img	*wall_ptr;
	
	// print_dist_arr_info(info);
	while (width_pixel < DISPLAY_WIDTH)
	{
		act_x = -1;
		calc_corners_of_wall(corners, width_pixel, info->dist_arr, info);
		calc_start_wall(start_end_wall, corners, width_pixel, info);
		calc_end_wall(start_end_wall, corners, width_pixel, info);
		wall_ptr = get_wall_ptr(width_pixel, info->dist_info, info);
		dx_for_wall = calc_dx_for_wall(start_end_wall, corners);
		while ((++act_x + corners[X1]) <= corners[X3])
		{
			draw_one_vertical_line(info->img, wall_ptr, start_end_wall, \
				corners, act_x, dx_for_wall);
		}
		// my_mlx_pixel_put(info->img, corners[X1], corners[Y1], 0x00FF0000); // for testing
		// my_mlx_pixel_put(info->img, corners[X2], corners[Y2], 0x00FF0000); // for testing
		// my_mlx_pixel_put(info->img, corners[X3], corners[Y3], 0x00FF0000); // for testing
		// my_mlx_pixel_put(info->img, corners[X4], corners[Y4], 0x00FF0000); // for testing
		

		width_pixel = next_tile_on_display_x(width_pixel, info);
	}
}