
#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
# include "../minilibx_opengl_20191021/mlx.h"
# else
	# include "../minilibx-linux/mlx.h"
# endif

# include <math.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
// # include "../minilibx-linux/mlx.h"
// # include "../minilibx_opengl_20191021/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265
# define X 0
# define Y 1
# define EXACT_X 3
# define EXACT_Y 4
# define X1 0
# define Y1 1
# define X2 2
# define Y2 3
# define X3 4
# define Y3 5
# define X4 6
# define Y4 7
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4
# define M 0
# define B 1
# define WIDTH_WALL 64
# define HEIGHT_WALL 64
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define DISPLAY_WIDTH 1000
# define DISPLAY_HEIGHT 600
# define LEN_CAM_VEC 1
# define LEN_LEFT_FOV 0.65 // 0,65 und 1 sind 33° -> fov von zusammen 66° gut für first person
# define FACTOR_WALL_HEIGHT 1
# define STEPSIZE 0.3
# define PLAYER_ROTATION_DEG 15
# define DISTANCE_FROM_WALL 0.3
# define START_X_WALL 0
# define END_X_WALL 1

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

typedef struct s_textures
{
	char		*path_no;
	char		*path_ea;
	char		*path_so;
	char		*path_we;
	char		*red;
	char		*green;
	char		*blue;
	//int			ceiling_color;
	//int			floor_color;
}				t_textures;

typedef struct s_info
{
	char	*map_path;
	int		row;
	char	**map;
	int		map_i;
	t_textures	txt;
	int		floor; // Max benutzt du das? Jo
	int		ceiling; // Max benutzt du das? Jo
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

/* ft_check_valid_textures.c */

bool    check_valid_textures(t_info *info);
bool	valid_texture_extension(t_info *info);
bool    check_valid_fc(t_info *info);

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

int 	**map_converter(t_info *info);
void	convert_player_pos_dir(t_info *info);

//**** ft_draw_textures_2.c ****//

void	fill_background(int	ceiling, int floor, t_img *img);
int		get_color_from_img(t_img *img, double x, double y);
t_img	*get_wall_ptr(int width_pixel, int **dist_info, t_info *info);
double	calc_dx_for_wall(double *start_end_wall, int *corners);
void	draw_one_vertical_line(t_img *dest, t_img *src, \
	double *start_end_wall, int *corners, int act_x, double dx_for_wall);

//**** ft_draw_textures_3.c ****//

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		argb(int alpha, int red, int green, int blue);

//**** ft_clean_up.c ****//

void	clean_up_map_int(t_info *info);

//**** ft_draw_textures.c ****//

int		next_tile_on_display_x(int act_x_on_display, t_info *info);
void	calc_end_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info);
void	calc_start_wall(double *start_end_wall, int *corners, \
	int width_pixel, t_info *info);
void	calc_corners_of_wall(int *corners, int width_pixel, \
	double *dist_arr, t_info *info);
void	draw_wall_textures(t_info *info, int width_pixel);

//**** ft_init.c ****//

int		**init_dist_arr(t_info *info);
void	init_mlx_window_first_screen(t_info *info);
t_info	*init_info_player_images();
void	get_properties_from_mlx_img(void *img_ptr, t_img *img);
void	init_mlx_and_textures(t_info *info);

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
double	dot_prod_vec(double *one, double *two);
double	calc_angle_vec(double *one, double *two);

//**** vec_ops.c ****//

double	len_vec(double *vec);
void	norm_vec(double *vec);
void	rot_vec(double *vec, double rot);
void	mult_vec(double *vec, double factor);
void	add_vec(double *dest, double *src);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif