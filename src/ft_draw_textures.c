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
	int	act_tile_map_x;
	int	act_tile_map_y;
	int	act_wall_facing_direction;

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

/**
 * @brief see comment of calc_start_wall
 * 
 */
void	calc_end_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info)
{
	int	end_x;

	end_x = corners[X3];
	if (info->dist_info[2][width_pixel] == NORTH)
		start_end_wall[END_X_WALL] = ((double)info->dist_info[EXACT_X] \
		[end_x] / 1000) - (double)info->dist_info[X][end_x];
	else if (info->dist_info[2][width_pixel] == SOUTH)
		start_end_wall[END_X_WALL] = (double)info->dist_info[X][end_x] \
		+ 1 - ((double)info->dist_info[EXACT_X][end_x] / 1000);
	else if (info->dist_info[2][width_pixel] == WEST)
		start_end_wall[END_X_WALL] = ((double)info->dist_info[EXACT_Y] \
		[end_x] / 1000) - (double)info->dist_info[Y][end_x];
	else if (info->dist_info[2][width_pixel] == EAST)
		start_end_wall[END_X_WALL] = (double)info->dist_info[Y][end_x] \
		+ 1 - ((double)info->dist_info[EXACT_Y][end_x] / 1000);
	start_end_wall[END_X_WALL] *= WIDTH_WALL;
}

/**
 * @brief when the left side of a wall is hidden 
 * the texture has to be shown not from the beginnig!
 * So take the exact point from the rayscan (dist_info[EXACT_X] or Y)
 * where you can see the the wall for the first time in the rayscan
 * and substract from that the position of the tile. F.e. you can see the tile
 * at (3.2, 2) (looking north, so x value is important). The coordinate of the
 * tile is important -> (3, 2) -> then you do 3.2 - 3 -> so the texture-
 * projection on the tile should also start at 0.2 of the texture.
 * The whole thing depends on the cardinal direction that you see 
 * from the tile.
 * 
 */
void	calc_start_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info)
{
	int	start_x;

	start_x = corners[X1];
	if (info->dist_info[2][width_pixel] == NORTH)
		start_end_wall[START_X_WALL] = ((double)info->dist_info[EXACT_X] \
			[start_x] / 1000) - (double)info->dist_info[X][start_x];
	else if (info->dist_info[2][width_pixel] == SOUTH)
		start_end_wall[START_X_WALL] = (double)info->dist_info[X][start_x] \
		+ 1 - ((double)info->dist_info[EXACT_X][start_x] / 1000);
	else if (info->dist_info[2][width_pixel] == WEST)
		start_end_wall[START_X_WALL] = ((double)info->dist_info[EXACT_Y] \
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
	double	height_on_x_value;
	double	buf;

	height_on_x_value = DISPLAY_HEIGHT * \
		(FACTOR_WALL_HEIGHT / dist_arr[width_pixel]);
	corners[X1] = width_pixel;
	corners[X2] = width_pixel;
	buf = round((DISPLAY_HEIGHT - height_on_x_value) / 2);
	corners[Y1] = (int)(buf + 0.1);
	buf = corners[Y1] + height_on_x_value;
	corners[Y2] = (int)(buf + 0.1);
	width_pixel = next_tile_on_display_x(width_pixel, info) - 1;
	height_on_x_value = DISPLAY_HEIGHT * \
		(FACTOR_WALL_HEIGHT / dist_arr[width_pixel]);
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
	int		act_x;
	int		corners[8];
	double	start_end_wall[3];
	double	dx_for_wall;
	t_img	*img_ptr[2];

	while (width_pixel < DISPLAY_WIDTH)
	{
		act_x = -1;
		calc_corners_of_wall(corners, width_pixel, info->dist_arr, info);
		calc_start_wall(start_end_wall, corners, width_pixel, info);
		calc_end_wall(start_end_wall, corners, width_pixel, info);
		img_ptr[DEST] = info->img;
		img_ptr[SRC] = get_wall_ptr(width_pixel, info->dist_info, info);
		start_end_wall[DX_FOR_WALL] = calc_dx_for_wall(start_end_wall, corners);
		while ((++act_x + corners[X1]) <= corners[X3])
		{
			draw_one_vertical_line(img_ptr, start_end_wall, \
				corners, act_x);
		}
		width_pixel = next_tile_on_display_x(width_pixel, info);
	}
}
