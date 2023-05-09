#include "../inc/cub3d.h"

/**
 * @brief return value of -1 is only for saving lines 
 * (normitnette purpose)
 * @return -1
 */
int	map_int_init(int *map, int col)
{
	int j;

	j = -1;
	while (++j < col)
		map[j] = 0;
	return (-1);
}
