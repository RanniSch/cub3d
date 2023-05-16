/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_extension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:09 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:04:13 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* checks if the file exists and for the correct extension.
*/
bool	valid_map_extension(t_info *info)
{
	int	p_len;
	int	fd;

	fd = open(info->map_path, O_RDONLY);
	if (fd == -1)
	{
		message(ERROR_1);
		close(fd);
		clean_up_all_expt_mlx(info);
		exit (1);
		return (false);
	}
	p_len = ft_strlen(info->map_path);
	if (ft_strncmp(&info->map_path[p_len - 4], ".cub", 4))
	{
		message(ERROR_2);
		close(fd);
		clean_up_all_expt_mlx(info);
		exit (1);
		return (false);
	}
	close(fd);
	return (true);
}

/*
bool	valid_map_extension(t_info *info)
{
	int	p_len;
    int	fd;

	fd = open(info->map_path, O_RDONLY);
	if (fd == -1)
	{
		message(ERROR_1);
		close(fd);
		// clean_up_extension(info);	// max neu eingefügt
		clean_up_all_expt_mlx(info);	// max neu eingefügt
		exit (1);					// max neu eingefügt
		return (false);
	}
	p_len = ft_strlen(info->map_path);
	if (ft_strncmp(&info->map_path[p_len - 4], ".cub", 4))
	{
		message(ERROR_2);
		close(fd);
		// clean_up_extension(info);	// max neu eingefügt
		clean_up_all_expt_mlx(info);	// max neu eingefügt
		exit (1);					// max neu eingefügt
		return (false);
	}
	close(fd);
	return (true);
}
*/
