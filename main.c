#include "./inc/cub3d.h"

/*void	raycast_and_picturework(t_info *info)
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
	else if (key == ESC)
		exit(0);					// ----------------- exit and clean_up !!!
	raycast_and_picturework(info);
}*/



/**
 * @brief color code is ARGB Alpha, red, green, blue
 * 
 * @return int 
 */
/*int main(void)
{
	// -----------------  wichtig MAIN behalten
	t_info *info;

	info = init_info_player_images();
	if (!info)
		printf("Fehler info");   //   ---------  change - clean_up oder so
	if(!init_dist_arr(info)) // wichtig
		return (1); // malloc not possible - change - clean_up oder so
	
	
	// char *no = "./textures/Wall64x64.xpm";  
	// void *v_no;
	// int width = 64;
	// int height = 64;
	// info->mlx_ptr = mlx_init();
	// v_no = mlx_xpm_file_to_image(&info->mlx_ptr, no, &width, &height);


	init_textures(info);
	// ----------------- ENDE  wichtig MAIN behalten
	
	double tile[2];
	
	// ------  create test map  -- recognize from map file

	info->mapsize[X] = 7;
	info->mapsize[Y] = 7;

	info->map_int = malloc(sizeof(int *) * 7);
	int j = -1;
	while (++j < 7)
	{
		info->map_int[j] = calloc(7, sizeof(int));
		if (j == 6 || j == 0)
		{
			info->map_int[j][1] = 1;
			info->map_int[j][2] = 1;
			info->map_int[j][3] = 1;
			info->map_int[j][4] = 1;
			info->map_int[j][5] = 1;
			info->map_int[j][6] = 1;
		}
		info->map_int[j][0] = 1;
		info->map_int[j][6] = 1;
	}

	info->map_int[3][5] = 1;
	info->map_int[3][1] = 1;

	// ------  player position and direction

	info->p->pos[X] = 2.5;			// replace - recognize from map file
	info->p->pos[Y] = 2.5;
	info->p->cam_vec[X] = 0;
	info->p->cam_vec[Y] = -1;


	info->ceiling = argb(0, 0, 2, 255);  // replace - recognize from map file
	info->floor = argb(0, 192, 192, 192);

	// -----------------  wichtig MAIN behalten
	init_mlx_window_first_screen(info);
	mlx_key_hook(info->mlx_win, key_event, info);
	mlx_loop(info->mlx_ptr);

	// ----------------- ENDE  wichtig MAIN behalten
}*/

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

	info->txt.path_no = NULL;
	info->txt.path_ea = NULL;
	info->txt.path_so = NULL;
	info->txt.path_we = NULL;
}

int	main(int argc, char **argv)
{
	t_info  *info;

	if (argc != 2)
 	{
 		printf("Only 1 argument is required for cub3D. Try: ./cub3d [path map]\n");
		exit(0);
 	}
 	info = malloc(sizeof(t_info) * 1);
 	info->map_path = ft_strdup(argv[1]);
     //printf("string path %s\n", info->map_path);
 	init_game(info);
 	if (!parsing(info))
     {
         printf("parsing false\n");
     }
     else
     {
        printf("great\n");
		info->map_int = map_converter(info);
     }
	
 	return (0);
}

