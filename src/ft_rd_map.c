/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rd_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:01:43 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:03:13 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	count_nb_row(char *map_path)
{
	int		nb_row;
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	nb_row = 0;
	while (line != NULL)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		nb_row++;
	}
	if (line)
		free(line);
	close(fd);
	return (nb_row);
}

char	**save_map(t_info *info)
{
	int		fd;
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (info->row + 1));
	if (!tmp_map)
		return (0);
	fd = open(info->map_path, O_RDONLY);
	while (i < info->row)
	{
		tmp_map[i] = get_next_line(fd);
		i++;
	}
	tmp_map[i] = NULL;
	close(fd);
	return (tmp_map);
}
