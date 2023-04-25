#include "../inc/cub3d.h"

/**
 * @brief dist_arr[] holds the distance values of the next wall.
 * dist_info[0][] and 1 hold the col and row values of the (1) Field on the
 * map that the next wall in that direction belongs to.
 * dist_arr[2][] holds the facing direction of the wall (NORTH, EAST, SOUTH, WEST)
 * 
 * @param info 
 * @return int** 
 */
int	**init_dist_arr(t_info *info)
{
	int i;

	i = -1;
	info->dist_arr = malloc(sizeof(double) * DISPLAY_WIDTH);
	if (!info->dist_arr)
		return (NULL);
	info->dist_info = malloc(sizeof(int*) * 5);
	if (!info->dist_info)
		return (NULL);
	while (++i < 5)
	{
		info->dist_info[i] = malloc(sizeof(int) * DISPLAY_WIDTH);
		if (!info->dist_info[i])
			return (NULL);
	}
	return (info->dist_info);
}

void	init_mlx_window_first_screen(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->mlx_win = mlx_new_window(info->mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3D");
	info->img = mlx_new_image(info->mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	info->img->addr = mlx_get_data_addr(info->img, &info->img->bits_per_pixel, &info->img->line_length, &info->img->endian);
		// double dpx; //difference pixel vector
	field_of_view(info->p->cam_vec, info->p->left_fov); //wichtig

	info->p->dpx = calc_diff_fov(info->p->left_fov);
	raycast_scan_in_fov(info, info->p);
	fill_background(info->ceiling, info->floor, info->img);
	draw_wallshadows(info->dist_arr, info->img);
	mlx_put_image_to_window(info->mlx_ptr, info->mlx_win, info->img, 0, 0);
	// print_dist_arr_info(&info);
}

t_info	*init_info_player_images()
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->p = malloc(sizeof(t_player));
	if (!info->p)
		return (NULL);
	info->img = malloc(sizeof(t_img));
	if (!info->img)
		return (NULL);
	info->north = malloc(sizeof(t_img));
	if (!info->north)
		return (NULL);
	info->south = malloc(sizeof(t_img));
	if (!info->south)
		return (NULL);
	info->east = malloc(sizeof(t_img));
	if (!info->east)
		return (NULL);
	info->west = malloc(sizeof(t_img));
	if (!info->west)
		return (NULL);
	return (info);
}

void	get_properties_from_mlx_img(void *img_ptr, t_img *img)
{
	img->addr = mlx_get_data_addr(img_ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

void	init_textures(t_info *info)
{
	char *no = "textures/Wall64x64.xpm";   //------- replace somehow
	char *ea = "textures/Collect64x64.xpm";
	char *so = "textures/Exit64x64.xpm";
	char *we = "textures/Player64x64.xpm";
	void *v_no;
	void *v_ea;
	void *v_so;
	void *v_we;

	info->north->width = WIDTH_WALL;
	info->north->height = HEIGHT_WALL;
	// img_no.height = 64;

	info->east->width = WIDTH_WALL;
	info->east->height = HEIGHT_WALL;

	info->south->width = WIDTH_WALL;
	info->south->height = HEIGHT_WALL;

	info->west->width = WIDTH_WALL;
	info->west->height = HEIGHT_WALL;

	v_no = mlx_xpm_file_to_image(info->mlx_ptr, no, &info->north->width, &info->north->height);
	v_ea = mlx_xpm_file_to_image(info->mlx_ptr, ea, &info->east->width, &info->east->height);
	v_so = mlx_xpm_file_to_image(info->mlx_ptr, so, &info->south->width, &info->south->height);
	v_we = mlx_xpm_file_to_image(info->mlx_ptr, we, &info->west->width, &info->west->height);
	get_properties_from_mlx_img(v_no, info->north);
	get_properties_from_mlx_img(v_ea, info->east);
	get_properties_from_mlx_img(v_so, info->south);
	get_properties_from_mlx_img(v_we, info->west);
}
