/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid_fc_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:06:30 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/21 18:06:27 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* Checks that there are only spaces between the capital letter
* "F" or "C" and the first entry of the colour code.
*/
bool	ft_valid_rgb_code(t_info *info, char *map)
{
	info->str_j++;
	if (map[info->str_j] == ' ')
	{
		info->str_j++;
		while (map[info->str_j] < 48 || map[info->str_j] > 57)
		{
			if (map[info->str_j] != ' ')
			{
				message(CHECK_TEX_9);
				return (false);
			}
			info->str_j++;
		}
		info->substr++;
		return (true);
	}
	message(CHECK_TEX_9);
	return (false);
}

/*
* Checks that there are only spaces or nothing between
* the commar and the next rgb code.
*/
bool	ft_valid_rgb_code_2(t_info *info, char *map)
{
	info->str_j++;
	if (map[info->str_j] > 47 && map[info->str_j] < 58)
	{
		info->substr++;
		return (true);
	}
	if (map[info->str_j] == ' ')
	{
		info->str_j++;
		while (map[info->str_j] < 48 || map[info->str_j] > 57)
		{
			if (map[info->str_j] != ' ')
			{
				message(CHECK_TEX_9);
				return (false);
			}
			info->str_j++;
		}
		info->substr++;
		return (true);
	}
	message(CHECK_TEX_9);
	return (false);
}

/*
* Saves the length substr of the string which is the colour code.
*/
bool	ft_valid_rgb_code_3(t_info *info, char *map)
{
	while (map[info->str_j] != ',')
	{
		if (map[info->str_j] == '\n')
		{
			message(CHECK_TEX_12);
			return (false);
		}
		info->str_j++;
		info->substr++;
	}
	return (true);
}
