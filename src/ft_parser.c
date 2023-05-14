
#include "../inc/cub3d.h"

/*
* Empty line which is followed by something. It cannot be the last line!
*/
void	skip_empty_lines(t_info *info)
{
	//printf("map_i0: %d\n", info->map_i);
	while (info->map[info->map_i] && info->map[info->map_i][0] == '\n')
		info->map_i++;
	//printf("map_i1: %d\n", info->map_i);
}

/*
* Checks the correct amount of textures and rgb colours.
* Only one NO, EA, SO, WE, F and C allowed.
*/
bool	ft_texture_values(t_info *info)
{
	if (info->check_no != 1 || info->check_ea != 1 || info->check_so != 1
		|| info->check_we != 1)
	{
		message(CHECK_TEX_6);
		return (false);
	}
	if (info->check_c != 1 || info->check_f != 1)
	{
		message(CHECK_TEX_7);
		return (false);
	}
	return (true);
}

/*
* Checks for empty lines, correct characters (N, W, E, S, 0, 1)
* and there are no spaces next to a '0'/player and each '0'/player is
* surrounded by a '1'.
*/
bool    check_valid_map(t_info *info)
{
	int	i;
	int	j;

	i = info->map_i;
	while (i < info->row && info->map[i] != NULL)
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (!correct_char(info, i, j))
				return (false);
			if (info->map[i][j] == '0' || init_player_pos(info, info->map[i][j], i , j))
			{
				if (!zero_middle(info, i, j))
					return (false);
			}
		}
		i++;
	}
	return (true);
}

/*
* Checks that there is exsactly one player in the map!
*/
bool	amount_player(int	amount_player)
{
	if (amount_player > 1)
	{
		message(CHECK_MAP_12);
		return (false);
	}
	else if (amount_player < 1)
	{
		message(CHECK_MAP_13);
		return (false);
	}
	return (true);
}

/*
* Checks for a correct map by subject and our definition!
* Saves player position and player orientation in struct.
*/
bool	parsing(t_info *info)
{
    skip_empty_lines(info);
	if (!check_valid_textures(info))
		return (false);
	if (!ft_texture_values(info))
        return (false);
	if (!valid_texture_extension(info))
		return (false);
	skip_empty_lines(info);
	if (!check_valid_map(info))
		return (false);
	if (!amount_player(info->player_amount))
		return (false);
    return (true);
}
