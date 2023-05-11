
#include "../inc/cub3d.h"

/*
* Checks for a closed map on the top.
*/
bool    no_zero_top(t_info *info, int i, int j)
{
	//printf("top i %d j %d\n", i, j);
	if (i > info->map_i && i < info->row) // && j != 0
	{
		if (info->map[i - 1][j] != '1')
		{
			if (!vertical_correct(info, i, j, 0))
				return (false);
		}
		else if (info->map[i - 1][j] == '1')
			return (true);
	}
	else
	{
		message(CHECK_MAP_5); // for last entry "0" before end of file!
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the bottom.
*/
bool    no_zero_bottom(t_info *info, int i, int j)
{
	//printf("bottom i %d j %d\n", i, j);
	if (i + 1 <= info->row && info->map[i + 1] != NULL) // && j != 0
	{
		if (info->map[i + 1][j] != '1')
		{
			if (!vertical_correct(info, i, j, 1))
				return (false);
		}
		else if (info->map[i + 1][j] == '1')
			return (true);
	}
	else
	{
		message(CHECK_MAP_7); // for last entry "0" before end of file!
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the right.
*/
bool	no_zero_right(t_info *info, int i, int j)
{
	//printf("right i %d j %d\n", i, j);
	if (info->map[i][j + 1] && info->map[i][j + 1] != '\n') // && j != 0
	{
		if (!horizontal_correct(info, i , j, 1))
			return (false);
	}
	else
	{
		message(CHECK_MAP_9);
		return (false);
	}
	return (true);
}

/*
* Checks for a closed map on the left.
*/
bool	no_zero_left(t_info *info, int i, int j)
{
	//printf("left i %d j %d\n", i, j);
	if (j != 0 && info->map[i][j - 1])
	{
		if (!horizontal_correct(info, i , j, 0))
			return (false);
	}
	else
	{
		message(CHECK_MAP_11);
		return (false);
	}
	return (true);
}

/*
* calls the function for checking walls.
* No spaces inside a map allowed!!!
*/
bool    zero_middle(t_info *info, int i, int j)
{
	//printf("drin\n");
	//printf("map %c\n", info->map[9][1]);
	if (!no_zero_static(info, i , j))
		return (false);
	if (!no_zero_top(info, i, j))
		return (false);
	if (!no_zero_bottom(info, i, j))
		return (false);
	if (!no_zero_right(info, i, j))
		return (false);
	if (!no_zero_left(info, i, j))
		return (false);
	//printf("Only zeros in middle\n");
	return (true);
}
