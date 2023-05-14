#include "../inc/cub3d.h"

t_info	*clean_up_info(t_info *info)
{
	if (!info)
		return (NULL);
	free (info);
	return (NULL);
}

void	clean_up_map_path(t_info *info)
{
	if (!info->map_path)
		return ;
	free (info->map_path);
	info->map_path = NULL;
}

/**
 * @brief 
 * mlx_destroy_image - is that correct there?
 * and int the next line? // free (img->img); // muss das hier hin?
 * and after the if then: 
 * // if (img->addr)
 *	// {
 *	// 	free (img->addr);
 *	// 	img->addr = NULL;
 *	// }
 * @param img 
 * @param info 
 * @return t_img* 
 */
t_img	*clean_up_one_texture(t_img *img, t_info *info)
{
	if (!img)
		return (img);
	if (img->img)
	{
		mlx_destroy_image(info->mlx_ptr, img->img);
		img->img = NULL;
	}
	free (img);
	img = NULL;
	return (img);
}

void	clean_up_textures(t_info *info)
{
	info->north = clean_up_one_texture(info->north, info);
	info->east = clean_up_one_texture(info->east, info);
	info->south = clean_up_one_texture(info->south, info);
	info->west = clean_up_one_texture(info->west, info);
	clean_up_one_texture(info->img, info);
	info->img = NULL;
}

void	clean_up_mlx_ptr_win(t_info *info)
{
	if (!info->mlx_ptr && !info->mlx_win)
		return ;
	if (LINUX)
		mlx_loop_end(info->mlx_ptr);
	mlx_destroy_window(info->mlx_ptr, info->mlx_win);
	mlx_destroy_display(info->mlx_ptr);
	info->mlx_win = NULL;
	info->mlx_ptr = NULL;
}
