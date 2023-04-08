
#include "../inc/cub3d.h"

bool	is_allowed_space_x(t_info *info, int i, int j, int var)
{
	while (info->map[i][j] && info->map[i][j] == 32)
	{
		if (var == 1)
		{
			i++;
			if (info->map[i] == NULL)
				return (true);
		}
		else
			i--;
		if (is_allowed_char(info->map[i][j]))
			return (false);
	}
	return (true);
}

bool	is_allowed_space_y(t_info *info, int i, int j, int var)
{
	while (info->map[i][j])
	{
		if (var == 1)
			j++;
		else
			j--;
		if (is_allowed_char(info->map[i][j]))
			return (false);
	}
	return (true);
}

bool	no_zero_top(t_info *info, int i, int j)
{
	//if (!correct_char(info, i - 1, j))
	//	return (false);
	if (i == info->map_i || i == info->row - 1 || j == 0)
	{
		printf("Map should be surrounded by wall (top)\n");
		return (false);
	}
	if (!is_allowed_char(info->map[i - 1][j]))
	{
		if (is_allowed_space_x(info, i - 1, j, 0))
			;
		else
		{
			printf("Map should be surrounded by wall (top)\n");
			return (false);
		}
	}
	return (true);
}

bool    no_zero_bottom(t_info *info, int i, int j)
{
	//if (!correct_char(info, i + 1, j))
	//	return (false);
	if (!is_allowed_char(info->map[i + 1][j]))
	{
		if (is_allowed_space_x(info, i + 1, j, 1))
			;
		else
		{
			printf("Map should be surrounded by wall (bottom)\n");
			return (false);
		}
	}
	return (true);
}

bool	no_zero_right(t_info *info, int i, int j)
{
	//if (!correct_char(info, i, j + 1))
	//	return (false);
	if (info->map[i][j + 1] && !is_allowed_char(info->map[i][j + 1]))
	{
		if (is_allowed_space_y(info, i, j + 1, 1))
			;
		else
		{
			printf("Map should be surrounded by wall (right)\n");
			return (false);
		}
	}
	return (true);
}

bool	no_zero_left(t_info *info, int i, int j)
{
	//if (!correct_char(info, i, j - 1))
	//	return (false);
	if (!is_allowed_char(info->map[i][j - 1]))
	{
		if (is_allowed_space_y(info, i, j - 1, 0))
			;
		else
		{
			printf("Map should be surrounded by wall (left)\n");
			return (false);
		}
	}
	return (true);
}

bool    zero_middle(t_info *info, int i, int j)
{
	if (!no_zero_top(info, i, j))
		return (false);
	if (!no_zero_bottom(info, i, j))
		return (false);
	if (!no_zero_right(info, i, j))
		return (false);
	if (!no_zero_left(info, i, j))
		return (false);
	return (true);
}
