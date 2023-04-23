
#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
// # include "../minilibx-linux/mlx.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265
# define X 0
# define Y 1
# define X1 0
# define Y1 1
# define X2 2
# define Y2 3
# define X3 4
# define Y3 5
# define X4 6
# define Y4 7
# define M 0
# define B 1
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define NORTH_WEST 5
# define NORTH_EAST 6
# define SOUTH_EAST 7
# define SOUTH_WEST 8
# define W 13
# define A 0
# define S 1
# define D 2
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define DISPLAY_WIDTH 600
# define DISPLAY_HEIGHT 400
# define LEN_CAM_VEC 1
# define LEN_LEFT_FOV 1 // mit 1 gestartet
# define FACTOR_WALL_HEIGHT 0.3
# define STEPSIZE 0.3
# define PLAYER_ROTATION_DEG 15
# define DISTANCE_FROM_WALL 0.3

typedef struct s_player
{
	double	pos[2];
	double	cam_vec[2];
	double	dpx;
	double	left_fov[2];
}	t_player;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

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

	int			mapsize[2];
	int			**map_int;
	double		*dist_arr;
	int			**dist_info;
	void		*mlx_ptr;
	void		*mlx_win;
	int			ceiling;
	int			floor;
	t_img		*north;
	t_img		*east;
	t_img		*south;
	t_img		*west;
	t_img		*img;
	t_player	*p;
}			t_info;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

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

/* ft_map_converter.c */

int **map_converter(t_info *info);

//**** linear_analysis.c ****//

double	slope(double *one, double *two);
int		func_from_points(double *one, double *two, double *func);
double	y_from_x(double x, double *func);
double	x_from_y(double y, double *func);
double	len_between_two_points(double x1, double y1, double x2, double y2);


//**** move_2.c ****//

void	move_backward(t_info *info);
void	move_left(t_info *info);
void	move_right(t_info *info);
void	rotate_left(t_info *info);
void	rotate_right(t_info *info);

//**** move.c ****//

double	betrag(double value);
void	move_x(double *move_vec, t_info *info);
void	move_y(double *move_vec, t_info *info);
void	move(double *move_vec, t_info *info);
void	move_forward(t_info *info);

//**** raycast_scan.c ****//

void	field_of_view(double *cam_vec, double *left_fov);
double	calc_diff_fov(double *left_fov);
void	calc_left_px_vec(double *left_px_vec, t_player *p);
void	calc_px_vec(double *px_vec, double *left_px_vec, t_player *p, int i);
void	raycast_scan_in_fov(t_info *info, t_player *p);

//**** raycast.c ****//

int		next_int_value_in_dir(double pos, double dir);
void	next_grid_point(double *dest, double *pos, double *dir, double *func);
int		find_correct_box(double pos, double dir);
int		hit(double *pos, double *dir, t_info *info, int *hit_coordinates);
double	raycast(double *position, double *cast_dir, t_info *info, int *hit_coordinates);

//**** test_utils.c ****//

void	print_dist_arr_info(t_info *info);
void	print_2d_arr(int **array, int row, int col);
void	draw_wallshadows(double *dist_arr, t_img *img);

//**** vec_ops_2.c ****//

void	pvec(double *vec);
void	cpy_vec(double *dest, double *src);
void	subtract_vec(double *dest, double *src);

//**** vec_ops.c ****//

double	len_vec(double *vec);
void	norm_vec(double *vec);
void	rot_vec(double *vec, double rot);
void	mult_vec(double *vec, double factor);
void	add_vec(double *dest, double *src);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif