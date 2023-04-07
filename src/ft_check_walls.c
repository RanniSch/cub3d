
#include "../inc/cub3d.h"

bool	zero_close_top(t_info *info, int i, int j)
{
	if (!correct_char(info, i - 1, j))
		return (false);
	if (i == v->map_i || i == v->row - 1 || j == 0)
	{
		printf("The map should be surrounded by the wall\n");
		return (false);
	}
	if (!is_allowed_char(info->map[i - 1][j]))
	{
		if (is_allowed_space_x(v, i - 1, j, 0))
			;
		else
		{
			printf("The map should be surrounded by the wall\n");
			return (false);
		}
	}
	return (true);
}

bool    zero_close_down(t_info *info, int i, int j)
{
	if (!correct_char(info, i + 1, j))
		return (false);
	if (!is_allowed_char(info->map[i + 1][j]))
	{
		if (is_allowed_space_x(info, i + 1, j, 1))
			;
		else
		{
			printf("The map should be surrounded by the wall\n");
			return (false);
		}
	}
	return (true);
}

bool	zero_close_right(t_info *info, int i, int j)
{
	if (!correct_char(info, i, j + 1))
		return (false);
	if (info->map[i][j + 1] && !is_allowed_char(info->map[i][j + 1]))
	{
		if (is_allowed_space_y(info, i, j + 1, 1))
			;
		else
		{
			printf("The map should be surrounded by the wall\n");
			return (false);
		}
	}
	return (true);
}

bool	zero_close_left(t_info *info, int i, int j)
{
	if (!correct_char(info, i, j - 1))
		return (false);
	if (!is_allowed_char(info->map[i][j - 1]))
	{
		if (is_allowed_space_y(info, i, j - 1, 0))
			;
		else
		{
			printf("The map should be surrounded by the wall\n");
			return (false);
		}
	}
	return (true);
}

bool    is_zero_close(t_info *info, int i, int j)
{
	if (is_zero_close_to_top(v, i, j, validator) == 1)
		return (false);
	if (is_zero_close_down(v, i, j, validator) == 1)
		return (false);
	if (is_zero_close_right(v, i, j, validator) == 1)
		return (false);
	if (is_zero_close_left(v, i, j, validator) == 1)
		return (false);
	return (true);
}
