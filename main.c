 
#include "./inc/cub3d.h"

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
	info->dist_info = malloc(sizeof(int*) * 3);
	if (!info->dist_info)
		return (NULL);
	while (++i < 3)
	{
		info->dist_info[i] = malloc(sizeof(int) * DISPLAY_WIDTH);
		if (!info->dist_info[i])
			return (NULL);
	}
	return (info->dist_info);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	argb(int alpha, int red, int green, int blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

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

/**
 * @brief goes through the raycast_scan (dist_info) and looks for
 * the next tile
 * 
 * @param act_tile_display_y 
 * @param info 
 * @return int number where the next tile starts in dist_info 
 * (same as width pixel on display)
 */
int	next_tile_on_display_x(int act_tile_display_x, t_info *info)
{
	int act_tile_map_x;
	int act_tile_map_y;
	// int i;

	act_tile_map_x = info->dist_info[X][act_tile_display_x];
	act_tile_map_y = info->dist_info[Y][act_tile_display_x];
	// i = -1;
	while (++act_tile_display_x < DISPLAY_WIDTH)
	{
		if (info->dist_info[X][act_tile_display_x] != act_tile_map_x || \
			info->dist_info[Y][act_tile_display_x] != act_tile_map_y)
			return (act_tile_display_x);
	}
	return (act_tile_display_x);
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
void	calc_corners_of_wall(int *corners, int width_pixel, double *dist_arr, t_info *info)
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
 * calc dx_for_wall -> how many px of the wall do we have to go
 * for one px of the display ?
 * calc dWally_px_per_display_px
 * draw_vertical_wall_line till the end or till the next comes
 * 
 * @param info 
 */
void	draw_wall_textures(t_info *info)
{
	int	width_pixel;
	int	corners[8];
	double	dx_for_wall;

	width_pixel = 0;
	print_dist_arr_info(info);
	while (width_pixel < DISPLAY_WIDTH)
	{
		
		calc_corners_of_wall(corners, width_pixel, info->dist_arr, info);
		my_mlx_pixel_put(info->img, corners[X1], corners[Y1], 0x00FF0000); // for testing
		my_mlx_pixel_put(info->img, corners[X2], corners[Y2], 0x00FF0000); // for testing
		my_mlx_pixel_put(info->img, corners[X3], corners[Y3], 0x00FF0000); // for testing
		my_mlx_pixel_put(info->img, corners[X4], corners[Y4], 0x00FF0000); // for testing
		dx_for_wall = WIDTH_WALL / (corners[X3] - corners[X1]);
		

		width_pixel = next_tile_on_display_x(width_pixel, info);
	}
	
}

void	raycast_and_picturework(t_info *info)
{
	raycast_scan_in_fov(info, info->p);
	fill_background(info->ceiling, info->floor, info->img);
	draw_wallshadows(info->dist_arr, info->img);
	draw_wall_textures(info);
	mlx_put_image_to_window(info->mlx_ptr, info->mlx_win, info->img->img, 0, 0);
}

void	key_event(int key, t_info *info)
{
	if (key == W)
		move_forward(info);
	else if (key == S)
		move_backward(info);
	else if (key == A)
		move_left(info);
	else if (key == D)
		move_right(info);
	else if (key == ARROW_LEFT)
		rotate_left(info);
	else if (key == ARROW_RIGHT)
		rotate_right(info);
	raycast_and_picturework(info);

	
	
	// t_img img_3;

	// img_3.img = mlx_new_image(info->mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	// img_3.addr = mlx_get_data_addr(img_3.img, &img_3.bits_per_pixel, &img_3.line_length, &img_3.endian);
	// fill_background(info->ceiling, info->floor, &img_3);
	// draw_wallshadows(info->dist_arr, &img_3);
	// mlx_put_image_to_window(info->mlx_ptr, info->mlx_win, img_3.img, 0, 0);
}

int	get_color_from_img(t_img *img, double x, double y)
{
	char *addr;
	int color;

	addr = img->addr + ((int)(y) % img->height * img->line_length + (int)(x) % img->width * (img->bits_per_pixel / 8));
	color = *(int *)addr;
	return (color);
	// dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// *(unsigned int*)dst = color;
}

void	get_properties_from_mlx_img(void *img_ptr, t_img *img)
{
	img->addr = mlx_get_data_addr(img_ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
} 


/**
 * @brief color code is ARGB Alpha, red, green, blue
 * 
 * @return int 
 */
int main(void)
{
	t_player p;
	t_info info;
	double func[2];
	// double left_fov[2];
	double tile[2];
	double ret;
	int game[3][3];
	
	info.mapsize[X] = 5;
	info.mapsize[Y] = 5;

	info.map_int = malloc(sizeof(int *) * 5);
	int j = -1;
	while (++j < 5)
	{
		info.map_int[j] = calloc(5, sizeof(int));
		if (j == 4 || j == 0)
		{
			info.map_int[j][1] = 1;
			info.map_int[j][2] = 1;
			info.map_int[j][3] = 1;
		}
		info.map_int[j][0] = 1;
		info.map_int[j][4] = 1;
	}

	p.pos[X] = 2.5;
	p.pos[Y] = 2;
	p.cam_vec[X] = 0;
	p.cam_vec[Y] = 1;
	info.p = &p;

	info.map_int[3][2] = 1;
	

	print_2d_arr(info.map_int, 5, 5);
	if(!init_dist_arr(&info))
		return (1); // malloc not possible

	// double dpx; //difference pixel vector
	field_of_view(p.cam_vec, p.left_fov);

	p.dpx = calc_diff_fov(p.left_fov);
	raycast_scan_in_fov(&info, &p);
	// print_dist_arr_info(&info);

	info.ceiling = argb(0, 0, 2, 255);
	info.floor = argb(0, 192, 192, 192);

	t_img img;
	t_img img_no;
	t_img img_ea;
	t_img img_so;
	t_img img_we;

	info.img = &img;
	info.north = &img_no;
	info.south = &img_so;
	info.east = &img_ea;
	info.west = &img_we;

	img_no.width = 64;
	img_no.height = 64;

	img_ea.width = 64;
	img_ea.height = 64;

	img_so.width = 64;
	img_so.height = 64;

	img_we.width = 64;
	img_we.height = 64;



	info.mlx_ptr = mlx_init();
	info.mlx_win = mlx_new_window(info.mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT, "Hello world!");
	img.img = mlx_new_image(info.mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	fill_background(info.ceiling, info.floor, &img);
	draw_wallshadows(info.dist_arr, &img);
	mlx_put_image_to_window(info.mlx_ptr, info.mlx_win, img.img, 0, 0);

	// img_2.img = mlx_new_image(info.mlx_ptr, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	// img_2.addr = mlx_get_data_addr(img_2.img, &img_2.bits_per_pixel, &img_2.line_length, &img_2.endian);
	void *v_no;
	void *v_ea;
	void *v_so;
	void *v_we;
	int width = 64;
	int height = 64;
	char *no = "textures/Wall64x64.xpm";
	char *ea = "textures/Collect64x64.xpm";
	char *so = "textures/Exit64x64.xpm";
	char *we = "textures/Player64x64.xpm";
	v_no = mlx_xpm_file_to_image(info.mlx_ptr, no, &img_no.width, &img_no.height);
	v_ea = mlx_xpm_file_to_image(info.mlx_ptr, ea, &img_ea.width, &img_ea.height);
	v_so = mlx_xpm_file_to_image(info.mlx_ptr, so, &img_so.width, &img_so.height);
	v_we = mlx_xpm_file_to_image(info.mlx_ptr, we, &img_we.width, &img_we.height);
	get_properties_from_mlx_img(v_no, &img_no);
	get_properties_from_mlx_img(v_ea, &img_ea);
	get_properties_from_mlx_img(v_so, &img_so);
	get_properties_from_mlx_img(v_we, &img_we);
	// img_2.addr = mlx_get_data_addr(test, &img_2.bits_per_pixel, &img_2.line_length, &img_2.endian);
	char *tex_addr;
	// t_img *wall_tex = &img_2;
	// tex_addr = wall_tex->addr + ((int)(1) % 64 * wall_tex->line_length + 1 % 64 * (wall_tex->bits_per_pixel / 8));
	// int color = *(int *)tex_addr;
	int color = get_color_from_img(&img_no, 17, 1);
	printf("ceiling = %d\n", info.ceiling);
	printf("color = %d\n", color);
	printf("test = %p\n", v_no);
	printf("addr = %p\n", img_no.addr);
	mlx_put_image_to_window(info.mlx_ptr, info.mlx_win, v_no, 100, 100);
	
	// mlx_put_image_to_window(window -> mlx_ptr, window -> win_ptr, window -> player_ptr, (run_width * window -> tile_width), (run_height * window -> tile_height));
	// fill_background(color_fl, color_ce, &img_2);
	// draw_wallshadows(info.dist_arr, &img);
	// mlx_put_image_to_window(info.mlx_ptr, info.mlx_win, test, 0, 0);
	
	
	mlx_key_hook(info.mlx_win, key_event, &info);
	mlx_loop(info.mlx_ptr);
}

void	init_game(t_info *info)
{
	info->row = count_nb_row(info->map_path);
    //printf("num rows: %d\n", info->row);
	info->map = save_map(info);
	info->map_i = 0;
	info->player_amount = 0;
	info->player_x = -1;
	info->player_y = -1;
	info->player_orientation = '0';
}

// int	main(int argc, char **argv)
// {
// 	t_info  *info;

// 	if (argc != 2)
// 	{
// 		printf("Only 1 argument is required for cub3D. Try: ./cub3d [path map]\n");
// 		exit(0);
// 	}
// 	info = malloc(sizeof(t_info) * 1);
// 	info->map_path = ft_strdup(argv[1]);
//     //printf("string path %s\n", info->map_path);
// 	init_game(info);
// 	if (!parsing(info))
//     {
//         printf("parsing false\n");
//     }
//     else
//     {
//         printf("great\n");
// 		info->map_int = map_converter(info);
//     }
	
// 	return (0);
// }
