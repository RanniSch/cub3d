
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_info
{
    char		*map_path;
    int			row;
    char		**map;
}				t_info;

/* ########################################################################## */
/* FUNCTIONS */

/* map.c */
int		count_nb_row(char *map_path);
char	**save_map(t_info *info);

/* ft_parser.c */

bool	valid_map_extension(t_info *info);
bool	check_orientation(t_info *info);
void	parsing(t_info *info);

#endif