
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
		return (false);
	}
	p_len = ft_strlen(info->map_path);
	if (ft_strncmp(&info->map_path[p_len - 4], ".cub", 4))
	{
		printf("Invalid map: Use .cub file extension\n");
		return (false);
	}
	//printf("Could open file\n");
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
* Including skip empty line and skip spaces!
*/
/*int loop_compass(t_info *info)
{
	int i;
    int j;
    int player;

    i = 0;
    player = 0;
    while (info->map[i])
    {
        if (info->map[i][0] == '\n')
            continue;
        j = 0;
        while (info->map[i][j])
        {
            //if (info->map[i][j] == ' ')
            //    continue;
            if (info->map[i][j] == 'N' || info->map[i][j] == 'S' || \
		        info->map[i][j] == 'W' || info->map[i][j] == 'E')
                player++;
            //if (info->map[i][j] != '0' && info->map[i][j] != '1' && info->map[i][j] != 'N' && \
            //    info->map[i][j] != 'S' && info->map[i][j] != 'W' && info->map[i][j] != 'E')
            //    return (-1);
            //printf("j %d\n", j);
            j++;
        }
        i++;
    }
    return (player);
}*/

/*
* Where to check if other letters are in map?
*/
/*bool	check_orientation(t_info *info)
{
	printf("result %d\n", loop_compass(info));
    if (loop_compass(info) != 1)
    {
        printf("Invalid map: Only one player with N, S, W, E is allowed!\n");
        return (false);
    }
    return (true);
}*/

bool    is_allowed_char(t_info *info, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1' || c == '0')
	{
		if (c == 'N')
			info->player_amount++;
		if (c == 'S')
			info->player_amount++;
		if (c == 'W')
			info->player_amount++;
		if (c == 'E')
			info->player_amount++;
		return (true);
	}
    return (false);
}

/*
* An empty line where nothing comes after!
*/
bool    filled_line(t_info *info, int i)
{
	if (info->map[i][0] == '\0')
	{
		printf("Invalid map\n");
		return (false);
	}
	return (true);
}

bool    correct_char(t_info *info, int i, int j)
{
	if (info->map[i] != NULL && info->map[i][j] != '\0') // if (info->map[i][j] != '\0')
	{
		if (info->map[i][j] != 32 && info->map[i][j] != '\n')
		{
			if (!is_allowed_char(info, info->map[i][j]))
			{
				printf("Invalid character in map!\n");
				return (false);
			}
		}
		if (!filled_line(info, i))	// brauchen wir das wirklich an der Stelle??? Wird dies nicht schon durch das erste if statement ausgeschlossen
			return (false);
	}
	return (true);
}

bool    valid_lines(t_info *info, int i)
{
	if (info->map[i][0] == '\n')
	{
		printf("Found empty line in map!\n");  // just for debugging purpose!!!
		return (false);
	}
	/*if (info->map[i][j] == 32)
	{

	}
	if (info->map[i][j] == '0')
	{

	}*/
	return (true);
}

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

bool	init_player_pos(t_info *info, char c, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		info->player_x = i;
		info->player_y = j;
		info->player_orientation = c;
		return (true);
	}
	return (false);
}

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
	if (!amount_player(info->player_amount))
		return (false);
	return (true);
}

bool	parsing(t_info *info)
{

	if (!valid_map_extension(info))
		return (false);
    skip_empty_lines(info);
	//if (!check_orientation(info))
	//	return ;
	if (!check_valid_map(info))
		return (false);
	//valid_init_position(is_pos, validator);
    return (true);
}
