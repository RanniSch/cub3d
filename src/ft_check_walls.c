/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:05:58 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/20 13:05:51 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* Checks for a closed map on the top.
*/
bool	no_zero_top(t_info *info, int i, int j)
{
	int len;

	len = ft_strlen(info->map[i - 1]);
	if (len <= j)
		printf("!!!!!!!!!!");
	if (i > info->map_i && i < info->row)
	{
		if (info->map[i - 1][j] != '1')
		{
			if (!vertical_correct(info, i, j, 0))
				return (false);
		}
		else if (info->map[i - 1][j] == '1')
			return (true);
	}
	else
	{
		message(CHECK_MAP_5);
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the bottom.
*/
bool	no_zero_bottom(t_info *info, int i, int j)
{
	if (i + 1 <= info->row && info->map[i + 1] != NULL)
	{
		if (info->map[i + 1][j] != '1')
		{
			if (!vertical_correct(info, i, j, 1))
				return (false);
		}
		else if (info->map[i + 1][j] == '1')
			return (true);
	}
	else
	{
		message(CHECK_MAP_7);
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the right.
*/
bool	no_zero_right(t_info *info, int i, int j)
{
	if (info->map[i][j + 1] && info->map[i][j + 1] != '\n')
	{
		if (!horizontal_correct(info, i, j, 1))
			return (false);
	}
	else
	{
		message(CHECK_MAP_9);
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the left.
* gleich am Anfang
* //printf("left i %d j %d\n", i, j);
*/
bool	no_zero_left(t_info *info, int i, int j)
{
	if (j != 0 && info->map[i][j - 1])
	{
		if (!horizontal_correct(info, i, j, 0))
			return (false);
	}
	else
	{
		message(CHECK_MAP_11);
		return (false);
	}
	return (true);
}

/*
* calls the function for checking walls.
* No spaces inside a map allowed!!!
*/
bool	zero_middle(t_info *info, int i, int j)
{
	if (!no_zero_static(info, i, j))
		return (false);
	if (!no_zero_top(info, i, j))
		return (false);
	if (!no_zero_bottom(info, i, j))
		return (false);
	if (!no_zero_right(info, i, j))
		return (false);
	if (!no_zero_left(info, i, j))
		return (false);
	return (true);
}
