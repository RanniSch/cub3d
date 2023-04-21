
#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_info
{
	char	*map_path;
	int		row;
	char	**map;
	int		map_i;
	int		player_amount;
	int		player_x;
	int		player_y;
	char	player_orientation;
}			t_info;

/* ########################################################################## */
/* FUNCTIONS */

/* rd_map.c */
int			count_nb_row(char *map_path);
char		**save_map(t_info *info);

/* ft_parser.c */

bool		valid_map_extension(t_info *info);
void		skip_empty_lines(t_info *info);
bool		check_valid_map(t_info *info);
bool		amount_player(int	amount_player);
bool		parsing(t_info *info);

/* ft_check_valid_map.c */

bool    valid_lines(t_info *info, int i);
bool    is_allowed_char(t_info *info, char c);
bool    filled_line(t_info *info, int i);
bool    correct_char(t_info *info, int i, int j);
bool	init_player_pos(t_info *info, char c, int i, int j);

/* ft_check_walls.c */

bool		no_zero_top(t_info *info, int i, int j);
bool		no_zero_bottom(t_info *info, int i, int j);
bool		no_zero_right(t_info *info, int i, int j);
bool		no_zero_left(t_info *info, int i, int j);
bool		zero_middle(t_info *info, int i, int j);

/* ft_check_walls_2.c */

bool		horizontal_correct(t_info *info, int i, int j, int var);
bool		vertical_correct(t_info *info, int i, int j, int var);

#endif