/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:06:18 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:06:19 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* Checks that there is no empty line in map.
*/
bool	valid_lines(t_info *info, int i)
{
	if (info->map[i][0] == '\n')
	{
		message(CHECK_MAP_1);
		return (false);
	}
	return (true);
}

/*
* Compares the input with all allowed characters.
*/
bool	is_allowed_char(t_info *info, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1' || c == '0')
	{
		if (c == 'N')
			info->player_amount++;
		if (c == 'S')
			info->player_amount++;
		if (c == 'W')
			info->player_amount++;
		if (c == 'E')
			info->player_amount++;
		return (true);
	}
	return (false);
}

/*
* An empty line where nothing comes after!
*/
bool	filled_line(t_info *info, int i)
{
	if (info->map[i][0] == '\0')
	{
		message(CHECK_MAP_2);
		return (false);
	}
	return (true);
}

/*
* Checks for only correct characters in map.
*/
bool	correct_char(t_info *info, int i, int j)
{
	if (info->map[i] != NULL && info->map[i][j] != '\0')
	{
		if (info->map[i][j] != 32 && info->map[i][j] != '\n')
		{
			if (!is_allowed_char(info, info->map[i][j]))
			{
				message(CHECK_MAP_3);
				return (false);
			}
		}
		if (!filled_line(info, i))
			return (false);
	}
	return (true);
}

/*
* Identifies the player, its position by indexes and its orientation.
* Also checks that the player is inside of the map.
*/
bool	init_player_pos(t_info *info, char c, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		info->player_x = i;
		info->p->pos[X] = (double)i - info->map_i + 0.5;
		info->player_y = j;
		info->p->pos[Y] = (double)j + 0.5;
		info->player_orientation = c;
		return (true);
	}
	return (false);
}
