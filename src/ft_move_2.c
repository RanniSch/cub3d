/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:03:57 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:03:58 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_backward(t_info *info)
{
	double	move_vec[2];

	cpy_vec(move_vec, info->p->cam_vec);
	mult_vec(move_vec, -1);
	move(move_vec, info);
}

void	move_left(t_info *info)
{
	double	move_vec[2];

	cpy_vec(move_vec, info->p->cam_vec);
	rot_vec(move_vec, 90);
	move(move_vec, info);
}

void	move_right(t_info *info)
{
	double	move_vec[2];

	cpy_vec(move_vec, info->p->cam_vec);
	rot_vec(move_vec, 270);
	move(move_vec, info);
}

void	rotate_left(t_info *info)
{
	rot_vec(info->p->cam_vec, PLAYER_ROTATION_DEG);
}

void	rotate_right(t_info *info)
{
	rot_vec(info->p->cam_vec, -PLAYER_ROTATION_DEG);
}
