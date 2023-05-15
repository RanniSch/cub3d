#include "../inc/cub3d.h"

/*
* A static check if there are "0" in the threshold.
*/
bool	no_zero_static(t_info *info, int i, int j)
{
	if (info->map[info->map_i][j] == '0')
	{
		message(CHECK_MAP_5);
		return (false);
	}
	if (info->map[i][0] == '0')
	{
		message(CHECK_MAP_11);
		return (false);
	}
	return (true);
}

/*
* Scans a row vertivally, starting by a '0' or the player.
* For var == 1 down, else up.
*/
bool	vertical_correct(t_info *info, int i, int j, int var)
{
	while (i >= info->map_i && i < info->row && info->map[i] != NULL)
	{
		if (!valid_lines(info, i))
			return (false);
		if (info->map[i][j] == 32)
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			i++;
		else
			i--;
	}
	if (var == 1)
		message(CHECK_MAP_6);
	else
		message(CHECK_MAP_4);
	return (false);
}

/*
bool	vertical_correct(t_info *info, int i, int j, int var)
{
	while (i >= info->map_i && i < info->row && info->map[i] != NULL)  
	// info->map[i] != NULL
	{
		//printf("bottom i %d j %d\n", i, j);
		if (!valid_lines(info, i))
			return (false);
		if (info->map[i][j] == 32)
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')		// i existiert, j aber nicht!!!
			return (true);
		//printf("i %d\n", i);
		if (var == 1)
			i++;
		else
			i--;
	}
	if (var == 1)
		message(CHECK_MAP_6);
	else
		message(CHECK_MAP_4);
	return (false);
}
*/

/*
* Scans a line horizontally, starting by a '0' or the player.
* For var == 1 right, else left.
*/
bool	horizontal_correct(t_info *info, int i, int j, int var)
{
	while (j >= 0 && info->map[i][j] && info->map[i][j] != '\n')
	{
		if (info->map[i][j] == 32)
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			j++;
		else
			j--;
	}
	if (var == 1)
		message(CHECK_MAP_8);
	else
		message(CHECK_MAP_10);
	return (false);
}

/*
bool	horizontal_correct(t_info *info, int i, int j, int var)
{
	while (j >= 0 && info->map[i][j] && info->map[i][j] != '\n')	
	// was wenn File nicht mit leerer Zeile endet?
	{
		if (info->map[i][j] == 32)
		{
			message(CHECK_MAP_14);
			return (false);
		}
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			j++;
		else
			j--;
	}
	if (var == 1)
		message(CHECK_MAP_8);
	else
		message(CHECK_MAP_10);
	return (false);
}
*/
