
#include "../inc/cub3d.h"

/*
* checks if the file exists and for the correct extension.
*/
bool	valid_map_extension(t_info *info)
{
	int p_len;
    int fd;

    fd = open(info->map_path, O_RDONLY);
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the file!");
        printf("Couldn't open the file!\n");
		close(fd);
		return (false);
	}
	p_len = ft_strlen(info->map_path);
	if (ft_strncmp(&info->map_path[p_len - 4], ".cub", 4))
	{
		printf("Invalid map: Use .cub file extension\n");
		close(fd);
		return (false);
	}
	//printf("Could open file\n");
	close(fd);
	return (true);
}

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
		if (!valid_lines(info, i))
			return (false);
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
		printf("Too many players! Only one player is allowed in map!\n");
		return (false);
	}
	else if (amount_player < 1)
	{
		printf("There is no player in map!\n");
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

	if (!valid_map_extension(info))
		return (false);
    skip_empty_lines(info);
	if (!check_valid_textures(info))
	{
		printf("Invalid map: Only four cardinal directions allowed!\n");
		return (false);
	}
	if (!valid_texture_extension(info))
		return (false);
	skip_empty_lines(info);
	if (!check_valid_fc(info))
		return (false);
	skip_empty_lines(info);
	//printf("line %d\n", info->map_i);
	if (!check_valid_map(info))
		return (false);
	if (!amount_player(info->player_amount))
		return (false);
    return (true);
}
