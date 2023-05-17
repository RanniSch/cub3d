/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:02:00 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:02:05 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	cardinal_direction_of_tile(int col, int row, double *pos)
{
	int	buf;

	if (pos[X] == col)
		return (EAST);
	else if (pos[X] > col)
	{
		if (pos[Y] == row)
			return (NORTH);
		if (pos[Y] > row)
		{
			buf = (int)pos[X];
			buf -= 1;
			if (buf == col)
				return (WEST);
			buf = (int)pos[Y];
			buf -= 1;
			if (buf == row)
				return (SOUTH);
		}
	}
	else
		message(RAYCAST);
	return (-1);
}

/**
 * @brief I need the exact coordinates where the tile is hit
 * but easily there is only this int array, so muliply it with 1000
 * and later divide again by 1000
 * 
 * @param hit_coordinates 
 * @param dest 
 */
void	write_next_grid_pt_to_hit_coordinates(int *hit_coordinates, \
	double *dest)
{
	hit_coordinates[EXACT_X] = (int)(dest[X] * 1000);
	hit_coordinates[EXACT_Y] = (int)(dest[Y] * 1000);
}

double	calc_len(double *dest, double *position)
{
	double	len;

	subtract_vec(dest, position);
	len = len_vec(dest);
	return (len);
}
