
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

int	skip_empty_line(t_info *info)
{
	int	loop_i;

	loop_i = 0;
	//printf("map_i0: %d\n", info->map_i);
	while (info->map[info->map_i] && info->map[info->map_i][0] == '\n')
	{
		info->map_i++;
		loop_i++;
	}
	//printf("map_i1: %d\n", info->map_i);
	return (loop_i);
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

bool    is_allowed_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1' || c == '0')
		return (true);
    return (false);
}

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
			if (!is_allowed_char(info->map[i][j]))
			{
				printf("Invalid character in map\n");;
				return (false);
			}
		}
		if (!filled_line(info, i))	// brauchen wir das wirklich???
			return (false);
	}
	return (true);
}

bool	init_player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool    check_valid_map(t_info *info)
{
	int	i;
	int	j;

	i = info->map_i;
	j = 0;
	while (i < info->row && info->map[i] != NULL)
	{
		if (info->map[i][0] == '\n') // falls wir keine leeren Zeilen in der Map akzeptieren
		{
			printf("Empty line in map!\n");
			return (false);
		}
		j = 0;
		while (info->map[i][j])
		{
			if (!correct_char(info, i, j))
				return (false);
			if (info->map[i][j] == '0' || init_player_pos(info->map[i][j]))
			{
				if (!zero_middle(info, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	parsing(t_info *info)
{

	if (!valid_map_extension(info))
		return (false);
    skip_empty_line(info);
	//if (!check_orientation(info))
	//	return ;
	if (!check_valid_map(info))
		return (false);
	//valid_init_position(is_pos, validator);
    return (true);
}
