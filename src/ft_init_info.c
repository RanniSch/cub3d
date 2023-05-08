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

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->map_path = NULL;
	info->row = 0;
	info->map = NULL;
	info->map_i = 0;
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
	return (info);
}
