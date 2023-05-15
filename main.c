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
		exit(0);
	}
	raycast_and_picturework(info);
	return (0);
}

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

void	check_argc_and_dist_from_wall(int argc)
{
	if (argc != 2)
 	{
 		message(ERROR_3);
		exit(0);
 	}
	if (DISTANCE_FROM_WALL < 0.3)
	{
		printf("DISTANCE_FROM_WALL ist to low\n");
		exit(0);
	}
}

void	parsing_(t_info *info)
{
	if (!parsing(info)) // unsaved malloc in: check_valid_textures -> ft_save_path_texture -> ft_substr
    {
        printf("parsing false\n"); // only for debugging purpuse!
		clean_up_parser(info);
		exit (0);
    }
}

int	main(int argc, char **argv)
{
	t_info  *info;

	check_argc_and_dist_from_wall(argc);
	info = init_process_game(); // init info, p, images, dist info, dist arr mit saved malloc
 	info->map_path = ft_strdup(argv[1]);
	if (!info->map_path)
	{
		clean_up_all_expt_mlx(info);
		message(ERROR_4);
		exit(1);
	}
	valid_map_extension(info); // max: ok (6te Zeile) (habe cleanup mit rein gepackt)
	info->row = count_nb_row(info->map_path); //unsave malloc inside?? (get_next_line)
	info->map = save_map(info); // returns 0 when malloc fails -> not save
	parsing_(info); // -> parsing ist in unterfunktion
	info->map_int = map_converter(info); // if malloc fails? - Max: ist gehändelt
	convert_player_pos_dir(info);
	init_mlx_and_textures(info); // nach parsing damit die Pfade zu den Texturen bekannt sind
	init_mlx_window_first_screen(info);
	mlx_key_hook(info->mlx_win, key_event, info);
	mlx_hook(info->mlx_win, 17, 1L << 2, ft_free_destroy, info);
	mlx_loop(info->mlx_ptr);
 	return (0);
}

/*
int	main(int argc, char **argv)
{
	t_info  *info;

	check_argc_and_dist_from_wall(argc);
	// if (argc != 2)
 	// {
 	// 	message(ERROR_3);
	// 	exit(0);
 	// }
	// if (DISTANCE_FROM_WALL < 0.3) // An Max: Soll das hier bleiben?
	// {
	// 	printf("DISTANCE_FROM_WALL ist to low\n");
	// 	exit(0);
	// }


	info = init_process_game();  //max: ok
	
 	info->map_path = ft_strdup(argv[1]); //max: ok
	// if (!valid_map_extension(info)) // kann eine Zeile sein
	// {
	// 	clean_up_extension(info);
	// 	exit (0);
	// }
	valid_map_extension(info); // max: ok (6te Zeile) (habe cleanup mit rein gepackt)


	info->row = count_nb_row(info->map_path); //max says: unsave malloc in here
	info->map = save_map(info); // returns 0 when malloc fails -> not save
	//if (!success_malloc_game(info)) // provides leaks -> alles schon halb gut abgesichert in init_process_game
	//{
	//	clean_up_parser(info);
	//	exit(0);
	//}
 	
	parsing_(info);
	printf("great\n"); // only for debugging purpuse!
	info->map_int = map_converter(info); // if malloc fails? - Max: keine Ahnung - so viele unsichere mallocs
	// if (!success_malloc_converter(info)) // provides leaks
	//	exit(0);
	
	convert_player_pos_dir(info);
	init_mlx_and_textures(info); // nach parsing damit die Pfade zu den Texturen bekannt sind
	init_mlx_window_first_screen(info);
	mlx_key_hook(info->mlx_win, key_event, info);
	mlx_hook(info->mlx_win, 17, 1L << 2, ft_free_destroy, info);
	mlx_loop(info->mlx_ptr);
 	return (0);
}
*/
