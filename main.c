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

void	raycast_and_picturework(t_info *info)
{
	raycast_scan_in_fov(info, info->p);
	fill_background(info->ceiling, info->floor, info->img);
	
	draw_wall_textures(info, 0);
	// draw_wallshadows(info->dist_arr, info->img);
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
	// double func[2];
	// double left_fov[2];
	double tile[2];
	// int game[3][3];

// 	int worldMap[24][24]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

// 	printf("%d\n", worldMap[0][0]);
	
	info.mapsize[X] = 7;
	info.mapsize[Y] = 7;

	info.map_int = malloc(sizeof(int *) * 7);
	int j = -1;
	while (++j < 7)
	{
		info.map_int[j] = calloc(7, sizeof(int));
		if (j == 6 || j == 0)
		{
			info.map_int[j][1] = 1;
			info.map_int[j][2] = 1;
			info.map_int[j][3] = 1;
			info.map_int[j][4] = 1;
			info.map_int[j][5] = 1;
			info.map_int[j][6] = 1;
		}
		info.map_int[j][0] = 1;
		info.map_int[j][6] = 1;
	}

	p.pos[X] = 2.5;
	p.pos[Y] = 2.5;
	p.cam_vec[X] = 0;
	p.cam_vec[Y] = -1;
	info.p = &p;

	info.map_int[3][5] = 1;
	info.map_int[3][1] = 1;

	print_2d_arr(info.map_int, 7, 7);
	if(!init_dist_arr(&info)) // wichtig
		return (1); // malloc not possible

	// double dpx; //difference pixel vector
	field_of_view(p.cam_vec, p.left_fov); //wichtig

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
	// int width = 64;
	// int height = 64;
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
