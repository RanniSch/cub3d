/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:03:48 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:03:50 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// returns the value without any sign
double	betrag(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}

/**
 * @brief calculates the possible move in + - x direction
 * in respect to the map and to DISTANCE_FROM_WALL
 * has to be before move_y()
 * 
 * @param move_vec sets move_vec[X] to the possible move in x dir 
 * @param info 
 */
void	move_x(double *move_vec, t_info *info)
{
	double	dist;
	int		hit_coordinates[5];
	double	move_x[2];

	move_x[X] = move_vec[X];
	move_x[Y] = 0;
	if (move_x[X] >= -THRESHOLD_ZERO && move_x[X] <= THRESHOLD_ZERO)
		return ;
	dist = raycast(info->p->pos, move_x, info, hit_coordinates);
	if (dist >= betrag(move_vec[X]) + DISTANCE_FROM_WALL)
		return ;
	if (move_vec[X] > 0)
		move_vec[X] = hit_coordinates[X] - DISTANCE_FROM_WALL \
			- info->p->pos[X];
	else
		move_vec[X] = hit_coordinates[X] + 1 + DISTANCE_FROM_WALL \
			- info->p->pos[X];
}

/**
 * @brief calculates the possible move in + - y direction
 * based on the move in x direction and with respect to 
 * the map and to DISTANCE_FROM_WALL
 * has to be after move_x()
 * 
 * @param move_vec sets move_vec[Y] to the possible move in x dir 
 * @param info 
 */
void	move_y(double *move_vec, t_info *info)
{
	double	dist;
	int		hit_coordinates[5];
	double	move_y[2];
	double	temp_pos[2];

	temp_pos[Y] = info->p->pos[Y];
	temp_pos[X] = info->p->pos[X] + move_vec[X];
	move_y[Y] = move_vec[Y];
	move_y[X] = 0;
	if (move_y[Y] >= -THRESHOLD_ZERO && move_y[Y] <= THRESHOLD_ZERO)
		return ;
	dist = raycast(temp_pos, move_y, info, hit_coordinates);
	if (dist >= betrag(move_vec[Y]) + DISTANCE_FROM_WALL)
		return ;
	if (move_vec[Y] > 0)
		move_vec[Y] = hit_coordinates[Y] - DISTANCE_FROM_WALL \
			- info->p->pos[Y];
	else
		move_vec[Y] = hit_coordinates[Y] + 1 + DISTANCE_FROM_WALL \
			- info->p->pos[Y];
}

void	move(double *move_vec, t_info *info)
{
	norm_vec(move_vec);
	mult_vec(move_vec, STEPSIZE);
	move_x(move_vec, info);
	move_y(move_vec, info);
	add_vec(info->p->pos, move_vec);
}

void	move_forward(t_info *info)
{
	double	move_vec[2];

	cpy_vec(move_vec, info->p->cam_vec);
	move(move_vec, info);
}
