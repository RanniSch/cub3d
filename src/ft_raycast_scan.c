#include "../inc/cub3d.h"

/**
 * @brief calculates the left_fov from cam_vec 
 * and LEN_CAM_VEC and LEN_LEFT_FOV
 * (for the ratio of the fov) and saves in left_fov
 * sets len of cam_vec to LEN_CAM_VEC
 * and len of left_fov to LEN_LEFT_FOV
 * 
 * @param cam_vec 
 * @param left_fov 
 */
void	field_of_view(double *cam_vec, double *left_fov)
{
	norm_vec(cam_vec);
	mult_vec(cam_vec, LEN_CAM_VEC);
	cpy_vec(left_fov, cam_vec);
	rot_vec(left_fov, 90);
	mult_vec(left_fov, LEN_LEFT_FOV);
}

/**
 * @brief calculate the difference from left to right field of view
 * that every pixel vector pix_vec has to have to the last one to account 
 * for every pixel on the width
 */
double	calc_diff_fov(double *left_fov)
{
	double len_fov;

	len_fov = len_vec(left_fov);
	len_fov *= 2;
	len_fov = len_fov / (DISPLAY_WIDTH - 1);
		return (len_fov);
}

/**
 * @brief calculates left_px_vec and saves in left_px_vec
 * norm p.cam_vec to length 1
 * add cam_vec to left_fov, save that in left_px_vec
 * 
 * @param left_px_vec 
 * @param p 
 */
void	calc_left_px_vec(double *left_px_vec, t_player *p)
{
	norm_vec(p->cam_vec);
	cpy_vec(left_px_vec, p->cam_vec);
	mult_vec(left_px_vec, LEN_CAM_VEC);
	add_vec(left_px_vec, p->left_fov);
}

/**
 * @brief calc the next px_vec and save in px_vec
 */
void	calc_px_vec(double *px_vec, double *left_px_vec, t_player *p, int i)
{
	cpy_vec(px_vec, p->left_fov);
	mult_vec(px_vec, -1);
	norm_vec(px_vec);
	mult_vec(px_vec, (p->dpx * i));
	add_vec(px_vec, left_px_vec);
}

/**
 * @brief scans how far away the next wall is and saves the values in 
 * dist_arr[][].
 * 
 * 1) calculate the vector that points to the most left pixel (left_px_vec)
 * 2) calc in a loop the next px_vec to the right
 * 3) calc vector between px_vec and cam_vec
 * 4) raycast px_vec
 * 5) calc * cos(angle) -> avioding fisheye view
 * 6) save hit coordinates and cardinal_direction and exact hitting points
 */
void	raycast_scan_in_fov(t_info *info, t_player *p)
{
	double left_px_vec[2];
	double px_vec[2];
	int  hit_coordinates[5];
	int k = -1;
	double angle;

	field_of_view(p->cam_vec, p->left_fov);
	p->dpx = calc_diff_fov(p->left_fov);
	calc_left_px_vec(left_px_vec, p);
	while(++k < DISPLAY_WIDTH)
	{
		calc_px_vec(px_vec, left_px_vec, p, k);
		angle = calc_angle_vec(px_vec, p->cam_vec);
		info->dist_arr[k] = raycast(p->pos, px_vec, info, hit_coordinates);
		info->dist_arr[k] *= cos(angle);
		info->dist_info[0][k] = hit_coordinates[X];
		info->dist_info[1][k] = hit_coordinates[Y];
		info->dist_info[2][k] = hit_coordinates[2];
		info->dist_info[EXACT_X][k] = hit_coordinates[EXACT_X];
		info->dist_info[EXACT_Y][k] = hit_coordinates[EXACT_Y];
	}
	print_dist_arr_info(info);
}
