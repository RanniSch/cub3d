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
		ft_free_destroy(info);
		exit(0);					// ----------------- exit and clean_up !!!
	}
	// print_dist_arr_info(info);
	raycast_and_picturework(info);
	// printf("pos:\n");
	// pvec(info->p->pos);
	// printf("cam:\n");
	// pvec(info->p->cam_vec);
	// printf("\n");
	return (0);
}

/* 
* Frees each entry of the map and map_int if it exists.
*/
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
}*/

bool	success_malloc_game(t_info *info)
{
	if (!init_process_game())
	{
		message(ERROR_4);
		return (false);
	}
	if(!init_dist_arr(info)) // wichtig
	{
		message(ERROR_4);
		return (false);
	}
	if(!init_info_player_images(info))
	{
		message(ERROR_4);
		return (false);
	}
	return (true);
}

bool	success_malloc_converter(t_info *info)
{
	if(!map_converter(info)) // wichtig
	{
		message(ERROR_4);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_info  *info;

	if (argc != 2)
 	{
 		message(ERROR_3);
		exit(0);
 	}
	info = init_process_game();
 	info->map_path = ft_strdup(argv[1]);
	if (!valid_map_extension(info))
	{
		clean_up_extension(info);
		exit (0);
	}
	info->row = count_nb_row(info->map_path);
	info->map = save_map(info);
	//if (!success_malloc_game(info)) // provides leaks
	//{
	//	clean_up_parser(info);
	//	exit(0);
	//}
 	if (!parsing(info))
    {
        printf("parsing false\n"); // only for debugging purpuse!
		clean_up_parser(info);
		exit (0);
    }
	printf("great\n"); // only for debugging purpuse!
	info->map_int = map_converter(info); // if malloc fails?
	//if (!success_malloc_converter(info)) // provides leaks
	//	exit(0);
	if (DISTANCE_FROM_WALL < 0.3) // An Max: Soll das hier bleiben?
	{
		printf("DISTANCE_FROM_WALL ist to low\n");
		exit(0);
	}
	convert_player_pos_dir(info);
	init_mlx_and_textures(info); // nach parsing damit die Pfade zu den Texturen bekannt sind
	init_mlx_window_first_screen(info);
	mlx_key_hook(info->mlx_win, key_event, info);
	mlx_hook(info->mlx_win, 17, 1L << 2, ft_free_destroy, info);
	mlx_loop(info->mlx_ptr);
 	return (0);
}
