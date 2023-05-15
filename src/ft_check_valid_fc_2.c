#include "../inc/cub3d.h"

/*
* Checks that there are only spaces between the capital letter
* "F" or "C" and the first entry of the colour code.
* direkt am Anfang der Funktion
* //printf("map: %c_%d\n", map[info->str_j], info->str_j);
*/
bool	ft_valid_rgb_code(t_info *info, char *map)
{
	info->str_j++;
	if (map[info->str_j] == ' ' || \
		(map[info->str_j] > 47 && map[info->str_j] < 58))
	{
		info->str_j++;
		while (map[info->str_j] < 48 || map[info->str_j] > 57)
		{
			if (map[info->str_j] != ' ')
			{
				message(CHECK_TEX_9);
				return (false);
			}
			info->str_j++;
		}
		return (true);
	}
	message(CHECK_TEX_9);
	return (false);
}

bool	ft_valid_rgb_code_2(t_info *info, char *map)
{
	while (map[info->str_j] != ',')
	{
		if (map[info->str_j] == '\n')
		{
			message(CHECK_TEX_12);
			return (false);
		}
		info->str_j++;
		info->substr++;
	}
	return (true);
}
