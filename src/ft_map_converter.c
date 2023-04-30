
#include "../inc/cub3d.h"

int **map_converter(t_info *info)
{
	int		i;
    int     j;
    int     str_len;
	int 	**tmp_map_int;

	i = -1;
	tmp_map_int = (int **)malloc(sizeof(int *) * (info->row + 1));
	if (!tmp_map_int)
		return (0);
	while (++i < info->row && info->map[i] != NULL)
	{
		str_len = ft_strlen(info->map[i]);
        tmp_map_int[i] = (int*)malloc(sizeof(int) * str_len);
        j = 0;
        while (info->map[i][j] && info->map[i][j] != '\n')
        {
            tmp_map_int[i][j] = info->map[i][j] - 48;
            //printf("%d", tmp_map_int[i][j]);
            j++;
        }
        //printf("\n");
	}
	tmp_map_int[i] = NULL;
	//printf("%ls", tmp_map_int[i]);
    
    return (tmp_map_int);
}

void	convert_player_pos_dir(t_info *info)
{
	info->p->pos[X] = (double)info->player_x - info->map_i + 0.5;
	info->p->pos[Y] = (double)info->player_y + 0.5;
	info->p->cam_vec[X] = 0;
	info->p->cam_vec[Y] = 0;
	if (info->player_orientation == 'N')
		info->p->cam_vec[Y] = 1;
	if (info->player_orientation == 'E')
		info->p->cam_vec[X] = 1;
	if (info->player_orientation == 'S')
		info->p->cam_vec[Y] = -1;
	if (info->player_orientation == 'W')
		info->p->cam_vec[X] = -1;
}