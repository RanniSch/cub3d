
#include "../inc/cub3d.h"

/*
* Scans a row vertivally, starting by a '0' or the player.
* For var == 1 down, else up.
*/
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

/*
* Scans a line horizontally, starting by a '0' or the player.
* For var == 1 right, else left.
*/
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
