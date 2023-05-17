/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:05:41 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:42 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_up_all_expt_mlx(t_info *info)
{
	clean_up_map_path(info);
	clean_up_txt_paths(info);
	clean_up_char_map(info);
	clean_up_map_int(info);
	clean_up_dist_arr(info);
	clean_up_dist_info(info);
	clean_up_textures(info);
	clean_up_p(info);
	info = clean_up_info(info);
}
