#include "../inc/cub3d.h"

int	count_nb_row(char *map_path)
{
	int		nb_row;
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
    //printf("line string %s\n", line);
	nb_row = 0;
	while (line != NULL)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		nb_row++;
	}
	if (line)
		free(line);
	close(fd);
	printf("nb row %d\n", nb_row);
	return (nb_row);
}

char	**save_map(t_info *info)
{
	int		fd;
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = malloc(sizeof(char *) * (info->row + 1));
	if (!tmp_map)
		return (0);
	fd = open(info->map_path, O_RDONLY);
	while (i < info->row)
	{
		tmp_map[i] = get_next_line(fd);
        //printf("%s", tmp_map[i]);
		i++;
	}
	tmp_map[i] = NULL;
	//printf("%s", tmp_map[i]);
	close(fd);
	return (tmp_map);
}
