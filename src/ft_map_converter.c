
#include "../inc/cub3d.h"

int **map_converter(t_info *info)
{
	int		i;
    int     j;
    int     str_len;
	int 	**tmp_map_int;

	i = -1;
	info->mapsize[Y] = info->row - info->map_i;
	info->mapsize[X] = 0;
	tmp_map_int = (int **)malloc(sizeof(int *) * (info->mapsize[Y]));
	if (!tmp_map_int)
		return (0);
	while (++i < info->mapsize[Y] && info->map[i + info->map_i] != NULL)
	{
		if (ft_strlen(info->map[i + info->map_i]) > info->mapsize[X])
			info->mapsize[X] = ft_strlen(info->map[i + info->map_i]) - 1;
	}
	i = -1;
	while (++i < info->mapsize[Y] && info->map[i + info->map_i] != NULL)
	{
		tmp_map_int[i] = (int*)malloc(sizeof(int) * info->mapsize[X]);//malloc sichern
		j = -1;
		while (info->map[i + info->map_i][++j] && info->map[i + info->map_i][j] != '\n')
		{
			if (info->map[i + info->map_i][j] == '0' || info->map[i + info->map_i][j] == '1')
				tmp_map_int[i][j] = info->map[i + info->map_i][j] - 48;
			else if(info->map[i + info->map_i][j] == 'N' || info->map[i + info->map_i][j] == 'W' ||\
				info->map[i + info->map_i][j] == 'S' || info->map[i + info->map_i][j] == 'E' ||\
				info->map[i + info->map_i][j] == ' ')
			{
				tmp_map_int[i][j] = 0;
			}
		}
	}

       
        
        //     tmp_map_int[i][j] = info->map[i][j] - 48;
        //     //printf("%d", tmp_map_int[i][j]);
        //     j++;
		// // str_len = ft_strlen(info->map[i + info->map_i]);
        // // tmp_map_int[i] = (int*)malloc(sizeof(int) * str_len);
        // // j = 0;
        // // while (info->map[i][j] && info->map[i][j] != '\n')
        // // {
        // //     tmp_map_int[i][j] = info->map[i][j] - 48;
        //     //printf("%d", tmp_map_int[i][j]);
        //     j++;
        
        //printf("\n");
	
	// tmp_map_int[i] = NULL;
	//printf("%ls", tmp_map_int[i]);
    
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