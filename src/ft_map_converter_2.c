/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_converter_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:33 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:04:34 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief return value of -1 is only for saving lines 
 * (normitnette purpose)
 * @return -1
 */
int	map_int_init(int *map, int col)
{
	int	j;

	j = -1;
	while (++j < col)
		map[j] = 0;
	return (-1);
}
