/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_converter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:27 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:04:28 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	count_mapsize_x(int i, t_info *info, int row_file)
{
	while (++i < info->mapsize[Y] && info->map[++row_file] != NULL)
	{
		if (ft_strlen(info->map[row_file]) > info->mapsize[X])
			info->mapsize[X] = ft_strlen(info->map[row_file]) - 1;
	}
}

int	dir_emp_zero(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' \
		|| c == ' ' || c == '0')
		return (1);
	return (0);
}

void	map_converter_init(int *i, int *row_file, \
	t_info *info, int ***tmp_map_int)
{
	*i = -1;
	*row_file = *i + info->map_i;
	info->mapsize[Y] = info->row - info->map_i;
	info->mapsize[X] = 0;
	count_mapsize_x(*i, info, *row_file);
	*row_file = info->mapsize[Y] + info->map_i;
	*tmp_map_int = (int **)malloc(sizeof(int *) * (info->mapsize[Y] + 1));
	if (!*tmp_map_int)
	{
		clean_up_all_expt_mlx(info);
		message(ERROR_4);
		exit (1);
	}
}

/*
void	map_converter_init(int *i, int *row_file, \
	t_info *info, int ***tmp_map_int)
{
	*i = -1;
	*row_file = *i + info->map_i;
	info->mapsize[Y] = info->row - info->map_i;
	info->mapsize[X] = 0;
	count_mapsize_x(*i, info, *row_file);
	*row_file = info->mapsize[Y] + info->map_i;
	*tmp_map_int = (int **)malloc(sizeof(int *) * (info->mapsize[Y] + 1));
	if (!*tmp_map_int)
	{										// max neu eingefügt
		clean_up_all_expt_mlx(info);
		message(ERROR_4);
		exit (1);
	}										// bis hier
}
*/

int	**map_converter(t_info *info)
{
	int		i;
	int		j;
	int		**tmp_map_int;
	int		row_file;

	map_converter_init(&i, &row_file, info, &tmp_map_int);
	while (++i < info->mapsize[Y] && --row_file >= 0)
	{
		tmp_map_int[i] = (int *)malloc(sizeof(int) * info->mapsize[X]);
		if (!tmp_map_int[i])
			return (NULL);
		j = map_int_init(tmp_map_int[i], info->mapsize[X]);
		while (info->map[row_file][++j] && info->map[row_file][j] != '\n')
		{
			if (info->map[row_file][j] == '1')
				tmp_map_int[i][j] = 1;
			else if (dir_emp_zero(info->map[row_file][j]))
				tmp_map_int[i][j] = 0;
		}
	}
	tmp_map_int[i] = NULL;
	clean_up_char_map(info);
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
	info->p->pos[Y] = (double)info->mapsize[Y] - \
		((double)info->player_x - info->map_i + 0.5);
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
