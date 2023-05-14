#include "../inc/cub3d.h"

void	clean_up_info_player_images(t_info *info)
{
	if (!info->p)
		return ;
	free (info->p);
	info->p = NULL;
	if (!info->img)
		return ;
	free (info->img);
	info->img = NULL;
	if (!info->north)
		return ;
	free (info->north);
	info->north = NULL;
	if (!info->south)
		return ;
	free (info->south);
	info->south = NULL;
	if (!info->east)
		return ;
	free (info->east);
	info->east = NULL;
	if (!info->west)
		return ;
	free (info->west);
	info->west = NULL;
}

char	*clean_up_one_txt_path(char *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
	return (ptr);
}

void	clean_up_txt_colors(t_info *info)
{
	info->txt.red = clean_up_one_txt_path(info->txt.red);
	info->txt.green = clean_up_one_txt_path(info->txt.green);
	info->txt.blue = clean_up_one_txt_path(info->txt.blue);
}

void	clean_up_txt_paths(t_info *info)
{
	info->txt.path_no = clean_up_one_txt_path(info->txt.path_no);
	info->txt.path_ea = clean_up_one_txt_path(info->txt.path_ea);
	info->txt.path_so = clean_up_one_txt_path(info->txt.path_so);
	info->txt.path_we = clean_up_one_txt_path(info->txt.path_we);
	clean_up_txt_colors(info);
}

/*
* Destroyes all textures, the window and the display.
* Frees the pointer and the allocations after pressing 
* ESC or the x in the corner of the window.
* clean_up texuters has 4 leaks?
*/
int	ft_free_destroy(t_info *info)
{
	clean_up_map_path(info);
	clean_up_txt_paths(info);
	clean_up_map_int(info);
	clean_up_dist_arr(info);
	clean_up_dist_info(info);
	clean_up_textures(info);
	clean_up_p(info);
	clean_up_mlx_ptr_win(info);
	info = clean_up_info(info);
	exit(0);//EXIT_FAILURE);  // programm wird doch ohne Fehler geschlossen oder? dann können wir 0 zurück geben
}
