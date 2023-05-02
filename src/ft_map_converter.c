
#include "../inc/cub3d.h"

void	count_mapsize_x(int i, t_info *info, int act_row_file)
{
	while (++i < info->mapsize[Y] && info->map[++act_row_file] != NULL)
	{
		if (ft_strlen(info->map[act_row_file]) > info->mapsize[X])
			info->mapsize[X] = ft_strlen(info->map[act_row_file]) - 1;
	}
}

// void	convert(int **tmp_map_int, t_info *info, int act_row_file, int j)
// {
// 	if (info->map[act_row_file][j] == '0' || info->map[act_row_file][j] == '1')
// 		tmp_map_int[i][j] = info->map[act_row_file][j] - 48;
// 	else if(info->map[act_row_file][j] == 'N' || info->map[act_row_file][j] == 'W' ||\
// 		info->map[act_row_file][j] == 'S' || info->map[act_row_file][j] == 'E' ||\
// 		info->map[act_row_file][j] == ' ')
// 	{
// 		tmp_map_int[i][j] = 0;
// 	}
// }

dir_emp_zero(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' \
		|| c == ' ' || c == '0')
		return (1);
}

void	map_converter_init(int *i, int *act_row_file, t_info *info)
{
	*i = -1;
	*act_row_file = *i + info->map_i;
	info->mapsize[Y] = info->row - info->map_i;
	info->mapsize[X] = 0;
	// count_mapsize_x(*i, info, *act_row_file);
}

int **map_converter(t_info *info)
{
	int		i;
    int     j;
    int     str_len;
	int 	**tmp_map_int;
	int		act_row_file;

	// map_converter_init(&i, &act_row_file, &info);
	i = -1;
	act_row_file = i + info->map_i;
	info->mapsize[Y] = info->row - info->map_i;
	info->mapsize[X] = 0;
	tmp_map_int = (int **)malloc(sizeof(int *) * (info->mapsize[Y]));
	if (!tmp_map_int)
		return (NULL);
	count_mapsize_x(i, info, act_row_file);
	while (++i < info->mapsize[Y] && info->map[++act_row_file] != NULL)
	{
		tmp_map_int[i] = (int*)malloc(sizeof(int) * info->mapsize[X]);//malloc sichern
		j = -1;
		while (info->map[act_row_file][++j] && info->map[act_row_file][j] != '\n')
		{
			if (info->map[act_row_file][j] == '1')
				tmp_map_int[i][j] = 1;
			else if(dir_emp_zero(info->map[act_row_file][j]))
				tmp_map_int[i][j] = 0;
		}
	}
    return (tmp_map_int);
}

/**
 * @brief player_y means the column
 * and player_x is the row (in the whole file), 
 * so don't forget to substract the beginning of the
 * map in the file (info->map_i)
 * 
 * @param info 
 */
void	convert_player_pos_dir(t_info *info)
{
	info->p->pos[Y] = (double)info->player_x - info->map_i + 0.5;
	info->p->pos[X] = (double)info->player_y + 0.5;
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