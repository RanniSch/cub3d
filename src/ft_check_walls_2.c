/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_walls_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:06:03 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/20 13:52:32 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* A static check if there are "0" in the threshold.
*/
bool	no_zero_static(t_info *info, int i, int j)
{
	int len;
	
	len = ft_strlen(info->map[info->map_i]);
	if (len > j)
	{
		if (info->map[info->map_i][j] == '0')
		{
			message(CHECK_MAP_5);
			return (false);
		}
	}
	if (info->map[i][0] == '0')
	{
		message(CHECK_MAP_11);
		return (false);
	}
	return (true);
}

/*
* Scans a row vertivally, starting by a '0' or the player.
* For var == 1 down, else up.
*/
bool	vertical_correct(t_info *info, int i, int j, int var)
{
	while (i >= info->map_i && i < info->row && info->map[i] != NULL)
	{
		if (!valid_lines(info, i)) // checked ob leerzeile ist
			return (false);
		if (info->map[i][j] == 32) //space
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			i++;
		else
			i--;
	}
	if (var == 1)
		message(CHECK_MAP_6);
	else
		message(CHECK_MAP_4);
	return (false);
}

/*
* Scans a line horizontally, starting by a '0' or the player.
* For var == 1 right, else left.
*/
bool	horizontal_correct(t_info *info, int i, int j, int var)
{
	while (j >= 0 && info->map[i][j] && info->map[i][j] != '\n')
	{
		if (info->map[i][j] == 32)
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			j++;
		else
			j--;
	}
	if (var == 1)
		message(CHECK_MAP_8);
	else
		message(CHECK_MAP_10);
	return (false);
}
