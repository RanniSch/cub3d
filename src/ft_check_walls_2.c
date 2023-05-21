/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_walls_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:06:03 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/21 18:52:52 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* A static check if there are "0" in the threshold.
*/
bool	no_zero_static(t_info *info)
{
	int	j;
	int	i;

	j = -1;
	i = info->map_i;
	while (info->map[info->map_i][++j])
	{
		if (info->map[info->map_i][j] == '0')
		{
			message(CHECK_MAP_5);
			return (false);
		}
	}
	while (i < info->row && info->map[i] != NULL)
	{
		if (info->map[i][0] == '0')
		{
			message(CHECK_MAP_11);
			return (false);
		}
		i++;
	}
	return (true);
}

/*
* A line length giver and checking with that if the previous line
* has the same length than the line after. Otherwise return false.
*/
bool	line_length_correct(t_info *info, int i, int j, int x)
{
	int	len;

	if (x == -1)
		len = ft_strlen(info->map[i - 1]) - 1;
	if (x == 1)
		len = ft_strlen(info->map[i + 1]) - 1;
	if (j + 1 > len && x == -1)
	{
		message(CHECK_MAP_4);
		return (false);
	}
	if (j + 1 > len && x == 1)
	{
		message(CHECK_MAP_6);
		return (false);
	}
	return (true);
}

/*
* Checks if there are spaces in the map.
*/
bool	no_spaces(t_info *info, int i, int j)
{
	if (info->map[i][j] == 32)
	{
		message(CHECK_MAP_14);
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
		if (!valid_lines(info, i) || !no_spaces(info, i, j))
			return (false);
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
		{
			if (!line_length_correct(info, i, j, 1))
				return (false);
			i++;
		}
		else
		{
			if (!line_length_correct(info, i, j, -1))
				return (false);
			i--;
		}
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
