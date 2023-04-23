
#include "../inc/cub3d.h"

int **map_converter(t_info *info)
{
	int		i;
    int     j;
    int     str_len;
	int 	**tmp_map_int;

	i = -1;
	tmp_map_int = (int **)malloc(sizeof(int *) * (info->row + 1));
	if (!tmp_map_int)
		return (0);
	while (++i < info->row && info->map[i] != NULL)
	{
		str_len = ft_strlen(info->map[i]);
        tmp_map_int[i] = (int*)malloc(sizeof(int) * str_len);
        j = 0;
        while (info->map[i][j] && info->map[i][j] != '\n')
        {
            tmp_map_int[i][j] = info->map[i][j] - 48;
            printf("%d", tmp_map_int[i][j]);
            j++;
        }
        printf("\n");
	}
	tmp_map_int[i] = NULL;
	printf("%ls", tmp_map_int[i]);
    
    return (tmp_map_int);
}
