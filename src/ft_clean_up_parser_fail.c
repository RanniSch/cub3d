/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_up_parser_fail.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:05:36 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:37 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_up_extension(t_info *info)
{
	clean_up_info_player_images(info);
	clean_up_dist_info(info);
	clean_up_dist_arr(info);
	clean_up_map_path(info);
	clean_up_info(info);
}

void	clean_up_parser(t_info *info)
{
	clean_up_info_player_images(info);
	clean_up_dist_info(info);
	clean_up_dist_arr(info);
	clean_up_txt_paths(info);
	clean_up_map_path(info);
	clean_up_char_map(info);
	clean_up_info(info);
}
