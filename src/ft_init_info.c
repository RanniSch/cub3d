#include "../inc/cub3d.h"

void	init_info_sub(t_info *info)
{
	info->dist_info = NULL;
	info->mlx_ptr = NULL;
	info->mlx_win = NULL;
	info->north = NULL;
	info->east = NULL;
	info->south = NULL;
	info->west = NULL;
	info->img = NULL;
	info->p = NULL;
}

/*
* Creates info pointer and initializes some variables of the info struct.
*/
void	init_info(t_info *info)
{
	info->map_path = NULL;
	info->row = 0;
	info->map = NULL;
	info->floor = 0;
	info->ceiling = 0;
	info->player_amount = 0;
	info->player_x = 0;
	info->player_y = 0;
	info->player_orientation = 0;
	info->mapsize[X] = 0;
	info->mapsize[Y] = 0;
	info->map_int = NULL;
	info->dist_arr = NULL;
	init_info_sub(info);
}

/*
* Initializes the rest variables of the info struct.
*/
void	init_info_2(t_info *info)
{
	info->map_i = 0;
	info->player_amount = 0;
	info->player_x = -1;
	info->player_y = -1;
	info->player_orientation = '0';
	info->txt.path_no = NULL;
	info->txt.path_ea = NULL;
	info->txt.path_so = NULL;
	info->txt.path_we = NULL;
	info->check_no = 0;
	info->check_so = 0;
	info->check_we = 0;
	info->check_ea = 0;
	info->check_f = 0;
	info->check_c = 0;
	info->check_txt = 0;
	info->check_colour = 0;
	info->str_j = 0;
	info->substr = 0;
}

/*
* Calls all initialisation functions before parsing process.
*/
t_info *init_process_game(void)
{
	t_info  *info;
	
	info = malloc(sizeof(t_info));
	if (!info)
	{						// max geändert -> müssen nix aufräumen, ist erster malloc
		message(ERROR_4);
		exit (1);
			// return (NULL);
	}
	init_info(info);
	init_info_2(info);
	if (!init_info_player_images(info)) // besser clean_up alles? 
	{									// max hat geändert
		clean_up_p(info);
		clean_up_textures(info);
		message(ERROR_4);
		exit (1);
	}
	if (!init_dist_arr(info))
	{									// max hat geändert
		clean_up_p(info);
		clean_up_textures(info);
		clean_up_dist_arr(info);
		clean_up_dist_info(info);
		message(ERROR_4);
		exit (1);
	}
	return (info);
}