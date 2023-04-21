
#include "../inc/cub3d.h"

/*bool	is_allowed_space_x(t_info *info, int i, int j, int var)
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
}*/

bool	vertical_correct(t_info *info, int i, int j, int var)
{
	while (i >= 0 && i < info->row && info->map[i] != NULL)  // info->map[i] != NULL
	{
		if (info->map[i][0] == '\n' || info->map[i][0] == '\0') // falls wir keine leeren Zeilen in der Map akzeptieren
		{
			//printf("Empty line in map!\n");
			return (false);
		}
		if (info->map[i][j] == 32)
			return (false);
		if (info->map[i][j] == '1')		// i existiert, j aber nicht!!!
			return (true);
		//printf("i %d\n", i);
		if (var == 1)
			i++;
		else
			i--;
	}
	return (false);
}

/*bool	is_allowed_space_y(t_info *info, int i, int j, int var)
{
	while (info->map[i][j])
	{
		if (var == 1)
			j++;
		else
			j--;
		if (!is_allowed_char(info->map[i][j]))
			return (false);
	}
	return (true);
}*/

bool	horizontal_correct(t_info *info, int i, int j, int var)
{
	while (j >= 0 && info->map[i][j] && info->map[i][j] != '\n')	// was wenn File nicht mit leerer Zeile endet?
	{
		if (info->map[i][0] == '0')
			return (false);
		if (info->map[i][j] == 32)
			return (false);
		if (info->map[i][j] == '1')
			return (true);
		if (var == 1)
			j++;
		else
			j--;
	}
	/*if (info->map[i][j] == '\n')	// handled when there is 0 before '\n' in no_zero_right
	{
		if (info->map[i][j - 1] != '1')
			return (false);
	}*/
	return (false);
}

bool    no_zero_top(t_info *info, int i, int j)
{
	//printf("top i %d j %d\n", i, j);
	if (i > info->map_i && i < info->row && j != 0)
	{
		if (info->map[i - 1][j] != '1')
		{
			if (vertical_correct(info, i, j, 0))
				return (true);
			else
			{
				printf("Map should be surrounded by wall (top) 1!\n"); // kann später raus, for debugging purpuse only
				return (false);
			}
			//if (is_allowed_space_x(info, i + 1, j, 1))
			//	;
		}
		else if (info->map[i - 1][j] == '1')
			return (true);
		else
		{
			printf("Map should be surrounded by wall (top)!\n"); // kann später raus, for debugging purpuse only
			return (false);
		}
	}
	printf("Fix wall on the top!\n"); // for last entry "0" before end of file!
	return (false);
}

bool    no_zero_bottom(t_info *info, int i, int j)
{
	//printf("bottom i %d j %d\n", i, j);
	if (i + 1 <= info->row && info->map[i + 1] != NULL && j != 0)
	{
		if (info->map[i + 1][j] != '1')
		{
			if (vertical_correct(info, i, j, 1))
				return (true);
			else
			{
				printf("Map should be surrounded by wall (bottom) 1\n"); // kann später raus, for debugging purpuse only
				return (false);
			}
			//if (is_allowed_space_x(info, i + 1, j, 1))
			//	;
		}
		else if (info->map[i + 1][j] == '1')
			return (true);
		else
		{
			printf("Map should be surrounded by wall (bottom)\n"); // kann später raus, for debugging purpuse only
			return (false);
		}
	}
	printf("Fix wall on the bottom!\n"); // for last entry "0" before end of file!
	return (false);
}

bool	no_zero_right(t_info *info, int i, int j)
{
	//printf("right i %d j %d\n", i, j);
	if (j != 0 && info->map[i][j + 1] && info->map[i][j + 1] != '\n')
	{
		if (horizontal_correct(info, i , j, 1))
			return (true);
		//if (is_allowed_space_y(info, i, j - 1, 0))
		//	;
		else
		{
			printf("Map should be surrounded by wall (right)\n"); // kann später raus, for debugging purpuse only
			return (false);
		}
	}
	printf("Fix wall on the right!\n");
	return (false);
}

bool	no_zero_left(t_info *info, int i, int j)
{
	//printf("left i %d j %d\n", i, j);
	if (j != 0 && info->map[i][j - 1])
	{
		if (horizontal_correct(info, i , j, 0))
			return (true);
		//if (is_allowed_space_y(info, i, j - 1, 0))
		//	;
		else
		{
			printf("Map should be surrounded by wall (left)\n"); // kann später raus, for debugging purpuse only
			return (false);
		}
	}
	printf("Fix wall on the left!\n");
	return (false);
}

bool    zero_middle(t_info *info, int i, int j)
{
	//printf("drin\n");
	//printf("map %c\n", info->map[9][1]);
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
