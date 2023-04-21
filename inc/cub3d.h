
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
    int			map_i;
    int         player_amount;
    int         player_x;
    int         player_y;
    char        player_orientation;
}				t_info;

/* ########################################################################## */
/* FUNCTIONS */

/* rd_map.c */
int		count_nb_row(char *map_path);
char	**save_map(t_info *info);

/* ft_parser.c */

bool	valid_map_extension(t_info *info);
void 	skip_empty_lines(t_info *info);
//int     loop_compass(t_info *info);
//bool	check_orientation(t_info *info);
bool    is_allowed_char(t_info *info, char c);
bool    filled_line(t_info *info, int i);
bool    correct_char(t_info *info, int i, int j);
bool	init_player_pos(t_info *info, char c, int i, int j);
bool    check_valid_map(t_info *info);
bool	parsing(t_info *info);

/* ft_check_walls.c */

bool	horizontal_correct(t_info *info, int i, int j, int var);
bool	allowed_space_y(t_info *info, int i, int j, int var);
//bool	is_allowed_space_x(t_info *info, int i, int j, int var);
//bool	is_allowed_space_y(t_info *info, int i, int j, int var);
bool	no_zero_top(t_info *info, int i, int j);
bool    no_zero_bottom(t_info *info, int i, int j);
bool	no_zero_right(t_info *info, int i, int j);
bool	no_zero_left(t_info *info, int i, int j);
bool    zero_middle(t_info *info, int i, int j);

#endif