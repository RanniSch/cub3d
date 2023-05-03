#include "../inc/cub3d.h"

void	clean_up_map_int(t_info *info)
{
	int	i;

	i = -1;
	if (info->map_int == NULL)
		return;
	while (info->map_int[++i])
		free (info->map_int[i]);
	free (info->map_int);
}