/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:05:51 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:54 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_up_map_int(t_info *info)
{
	int	i;

	i = -1;
	if (info->map_int == NULL)
		return ;
	while (info->map_int[++i])
		free (info->map_int[i]);
	free (info->map_int);
	info->map_int = NULL;
}

void	clean_up_dist_info(t_info *info)
{
	int	i;

	i = -1;
	if (info->dist_info == NULL)
		return ;
	while (++i < 5 && info->dist_info[i])
	{
		free (info->dist_info[i]);
	}
	free (info->dist_info);
	info->dist_info = NULL;
}

void	clean_up_dist_arr(t_info *info)
{
	if (!info->dist_arr)
		return ;
	free (info->dist_arr);
	info->dist_arr = NULL;
}

void	clean_up_char_map(t_info *info)
{
	int	i;

	i = -1;
	if (info->map == NULL)
		return ;
	while (info->map[++i])
		free (info->map[i]);
	free (info->map);
	info->map = NULL;
}

void	clean_up_p(t_info *info)
{
	if (!info->p)
		return ;
	free (info->p);
	info->p = NULL;
}
