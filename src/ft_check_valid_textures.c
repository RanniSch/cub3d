#include "../inc/cub3d.h"

/*
* Checks if there are only empty spaces between declaration and path.
* F.e. NO   ./[path]
*/
bool	ft_check_path_texture(t_info *info, char *map)
{
	info->str_j = 2;
	info->substr = 0;
	while (map[info->str_j] != '.')
	{
		if (map[info->str_j] != ' ')
		{
			message(CHECK_TEX_8);
			info->check_txt++;
			return (false);
		}
		info->str_j++;
	}
	info->str_j++;
	while (map[info->str_j] != '\n')
	{
		info->substr++;
		info->str_j++;
	}
	return (true);
}

/*
* Saves each texture in the belonging pointer.
*/
bool	ft_save_path_texture(t_info *info, char *map, char x)
{
	unsigned int	start;

	ft_check_path_texture(info, map);
	start = info->str_j - info->substr - 1;
	if (x == 'n')
	{
		info->txt.path_no = ft_substr(map, start, info->substr + 1);
		info->check_no++;
	}
	if (x == 'e')
	{
		info->txt.path_ea = ft_substr(map, start, info->substr + 1);
		info->check_ea++;
	}
	if (x == 's')
	{
		info->txt.path_so = ft_substr(map, start, info->substr + 1);
		info->check_so++;
	}
	if (x == 'w')
	{
		info->txt.path_we = ft_substr(map, start, info->substr + 1);
		info->check_we++;
	}
	return (true);
}

/*
bool	ft_save_path_texture(t_info *info, char *map, char x)
{
	ft_check_path_texture(info, map);
	if (x == 'n')
	{
		info->txt.path_no = ft_substr(map, info->str_j - info->substr - 1,
				info->substr + 1);
		info->check_no++;
	}
	if (x == 'e')
	{
		info->txt.path_ea = ft_substr(map, info->str_j - info->substr - 1,
				info->substr + 1);
		info->check_ea++;
	}
	if (x == 's')
	{
		info->txt.path_so = ft_substr(map, info->str_j - info->substr - 1,
				info->substr + 1);
		info->check_so++;
	}
	if (x == 'w')
	{
		info->txt.path_we = ft_substr(map, info->str_j - info->substr - 1,
				info->substr + 1);
		info->check_we++;
	}
	return (true);
}
*/

/*
* Figures out, when the map starts, which finishes the job of texture functions.
*/
bool	start_of_map(t_info *info)
{
	int	j;

	j = -1;
	if (info->map[info->map_i][0] == 32)
	{
		while (info->map[info->map_i][++j] != '\n')
		{
			if (info->map[info->map_i][j] == '1'
				|| info->map[info->map_i][j] == '0')
				return (true);
		}
		message(CHECK_TEX_10);
		return (false);
	}
	else if (info->map[info->map_i][0] == '1'
			|| info->map[info->map_i][0] == '0')
		return (true);
	message(CHECK_TEX_10);
	return (false);
}

/*
* Checks for four textures that start either with NO, EA, SO or WE
* and for the two colours floor and ceiling.
*/
bool	check_valid_textures(t_info *info)
{
	while (info->map[info->map_i])
	{
		skip_empty_lines(info);
		if (info->map[info->map_i][0] == 'N' && info->map[info->map_i][1] == 'O')
			ft_save_path_texture(info, info->map[info->map_i], 'n');
		else if (info->map[info->map_i][0] == 'E' && info->map[info->map_i][1] == 'A')
			ft_save_path_texture(info, info->map[info->map_i], 'e');
		else if (info->map[info->map_i][0] == 'S' && info->map[info->map_i][1] == 'O')
			ft_save_path_texture(info, info->map[info->map_i], 's');
		else if (info->map[info->map_i][0] == 'W' && info->map[info->map_i][1] == 'E')
			ft_save_path_texture(info, info->map[info->map_i], 'w');
		else if (info->map[info->map_i][0] == 'F' && info->map[info->map_i][1] == 32)
			check_valid_fc(info, info->map[info->map_i], 'f');
		else if (info->map[info->map_i][0] == 'C' && info->map[info->map_i][1] == 32)
			check_valid_fc(info, info->map[info->map_i], 'c');
		else if (!start_of_map(info))
			return (false);
		else if (start_of_map(info))
			break ;
		if (info->check_txt != 0 || info->check_colour != 0)
			return (false);
		info->map_i++;
	}
	//printf("NO _%s_\n", info->txt.path_no); // prints north texture!!!
	//printf("SO _%s_\n", info->txt.path_so); // prints south texture!!!
	//printf("WE _%s_\n", info->txt.path_we); // prints west texture!!!
	//printf("EA _%s_\n", info->txt.path_ea); // prints east texture!!!
	return (true);
}
