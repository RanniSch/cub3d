/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:01:52 by mrehberg          #+#    #+#             */
/*   Updated: 2023/05/16 15:01:53 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief 
 * vorher war dir < 0, aber gab Problem bei dir minimal unter 0
 * evtl besser auch hier THRESHHOLD_ZERO einzuführen
 * else if (dir < 0)
 */
int	next_int_value_in_dir(double pos, double dir)
{
	int		ret;

	ret = 0;
	if (dir > 0)
		ret = (int)(pos + 1);
	else if (dir <= 0)
	{
		ret = (int)pos;
		if (!(ret < pos))
			ret -= 1;
	}
	return (ret);
}

/**
 * @brief searches the next grid point from position pos
 * on linear function func in direction x_dir
 * copies the matched gridpoint into dest
 * 
 * @param dest 
 * @param pos 
 * @param func 
 */
void	next_grid_point(double *dest, double *pos, double *dir, double *func)
{
	double	y;
	double	x;
	int		dx;
	int		dy;
	double	start_p[2];

	cpy_vec(start_p, pos);
	dx = next_int_value_in_dir(pos[X], dir[X]);
	dy = next_int_value_in_dir(pos[Y], dir[Y]);
	y = y_from_x(dx, func);
	x = x_from_y(dy, func);
	if (len_between_two_points(start_p[X], start_p[Y], dx, y) \
		< len_between_two_points(start_p[X], start_p[Y], x, dy))
	{
		dest[X] = dx;
		dest[Y] = y;
	}
	else
	{
		dest[X] = x;
		dest[Y] = dy;
	}
}

/**
 * @brief pos is the x (or y) value 
 * 
 * @param pos 
 * @param dir 
 * @return int 
 */
int	find_correct_box(double pos, double dir)
{
	int	ret;

	ret = 0;
	if (dir >= 0)
		ret = (int)pos;
	else if (dir < 0)
	{
		ret = (int)pos;
		if (!(ret < pos))
			ret -= 1;
	}
	return (ret);
}

/**
 * @brief looks if *pos hit a wall 
 * by looking at that coordinates in 
 * the map
 * if outside the map returns -1
 * if hit_coordinates is not NULL the col and row of the tile
 * and the cardinal direction of the hit of the tile will be 
 * saved in hit_coordinates
 * 
 * @param pos position where the tile is hit
 * @param map_int the map with the tiles
 * @param mapsize size of the map in x and y direction (if the map is correct
 * it should not matter)
 * @return int 1 if hit a wall, 0 if not, 
 * -1 if outside of the map
 */
int	hit(double *pos, double *dir, t_info *info, int *hit_coordinates)
{
	int	col;
	int	row;

	col = find_correct_box(pos[X], dir[X]);
	row = find_correct_box(pos[Y], dir[Y]);
	if (col >= info->mapsize[X] || row >= info->mapsize[Y] || \
		col < 0 || row < 0)
		return (-1);
	if (info->map_int[row][col] == 1)
	{
		if (hit_coordinates)
		{
			hit_coordinates[X] = col;
			hit_coordinates[Y] = row;
			hit_coordinates[2] = cardinal_direction_of_tile(col, row, pos);
		}
		return (1);
	}
	return (0);
}

/**
 * @brief calculates length to next wall from position
 * in direction cast_dir (needs the map)
 * For that it makes a linear function (y=mx+b) out of 
 * two points: the position and the direction. 
 * Then calculates the cutting points on that function 
 * with the grid. Looks if it hit a wall on that cutting point.
 * If hit a wall, calulates the distance to wall from pos.
 * 
 * if hit_coordinates not NULL, Saves the coordinates 
 * in map that it hit in hit_coordinates hit...[X] = col 
 * hit...[Y] = row and in hit...[2] the cardinal_direction
 * @param pos 
 * @param dir length of dir is not important
 * @return double: len to next wall, -1 if no wall found
 */
double	raycast(double *position, double *cast_dir, \
	t_info *info, int *hit_coordinates)
{
	double	func[2];
	double	dest[2];
	double	pos[2];

	cpy_vec(pos, position);
	if (cast_dir[X] == 0)
		cast_dir[X] += 0.0000001;
	cpy_vec(dest, cast_dir);
	add_vec(dest, pos);
	func_from_points(pos, dest, func);
	while (1)
	{
		next_grid_point(dest, pos, cast_dir, func);
		if (hit(dest, cast_dir, info, NULL) == -1)
			return (-1);
		if (hit_coordinates)
			write_next_grid_pt_to_hit_coordinates(hit_coordinates, dest);
		if (hit(dest, cast_dir, info, hit_coordinates))
			return (calc_len(dest, position));
		cpy_vec(pos, dest);
	}
	return (0);
}
