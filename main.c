#include "./inc/cub3d.h"

void	raycast_and_picturework(t_info *info)
{
	raycast_scan_in_fov(info, info->p);
	fill_background(info->ceiling, info->floor, info->img);
	draw_wall_textures(info, 0);
	mlx_put_image_to_window(info->mlx_ptr, info->mlx_win, info->img->img, 0, 0);
}

int	key_event(int key, t_info *info)
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
	{
		clean_up_map_int(info);
		clean_up_dist_info(info);
		exit(0);					// ----------------- exit and clean_up !!!
	}
	raycast_and_picturework(info);
	// printf("pos:\n");
	// pvec(info->p->pos);
	// printf("cam:\n");
	// pvec(info->p->cam_vec);
	// printf("\n");
	return (0);
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

	info->txt.path_no = NULL;
	info->txt.path_ea = NULL;
	info->txt.path_so = NULL;
	info->txt.path_we = NULL;

	//info->v_no = NULL;
	//info->v_ea = NULL;
	//info->v_so = NULL;
	//info->v_we = NULL;
}

/* frees each entry of the map if it exists */
/*void	ft_free_struct(t_info *info)
{
	int	i;

	i = map_i - 1;
	if (info->map_int)
	{
		while (++i < info->row)
		{
			free(info->map_i[i])
		}
		free(info->map_int)
	}
	i = -1
	if (info->map)
	{
		while (++i < info->row)
		{
			free(info->map[i]);
		}
		free(info->map);
	}
	free(info);
}

int	ft_free_destroy(t_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->v_no);
	mlx_destroy_image(info->mlx_ptr, info->v_ea);
	mlx_destroy_image(info->mlx_ptr, info->v_so);
	mlx_destroy_image(info->mlx_ptr, info->v_we);
	mlx_loop_end(info->mlx_ptr);
	mlx_destroy_window(info->mlx_ptr, info->mlx_win);
	mlx_destroy_display(info->mlx_ptr);
	free(info->mlx_ptr);
	ft_free_struct(info);
	exit(EXIT_FAILURE);
}*/

int	main(int argc, char **argv)
{
	t_info  *info;

	
	if (argc != 2)
 	{
 		printf("Only 1 argument is required for cub3D. Try: ./cub3d [path map]\n");
		exit(0);
 	}
	info = init_info_player_images();
	if (!info)
		printf("Fehler info");   //   ---------  change - clean_up oder so
	if(!init_dist_arr(info)) // wichtig
		return (1); // malloc not possible - change - clean_up oder so
	



 	// info = malloc(sizeof(t_info) * 1);
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
	// print_2d_arr(info->map_int, info->mapsize[Y], info->mapsize[X]);
	convert_player_pos_dir(info);
	init_mlx_and_textures(info); // nach parsing damit die Pfade zu den Texturen bekannt sind
	init_mlx_window_first_screen(info);
	mlx_key_hook(info->mlx_win, key_event, info);
	//mlx_hook(info->mlx_win, 17, 1L << 2, ft_free_destroy, info);
	mlx_loop(info->mlx_ptr);
 	return (0);
}
