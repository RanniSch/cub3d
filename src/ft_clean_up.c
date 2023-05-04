#include "../inc/cub3d.h"

void	clean_up_map_int(t_info *info)
{
	int	i;

	i = -1;
	if (info->map_int == NULL)
		return;
	while (info->map_int[++i])
		free (info->map_int[i]);
	free (info->map_int);
	info->map_int = NULL;
}

void	clean_up_dist_info(t_info *info)
{
	int	i;

	i = -1;
	if (info->dist_info == NULL)
		return;
	while (++i < 5)
		free (info->dist_info[i]);
	free (info->dist_info);
	info->dist_info = NULL;
}

void	clean_up_dist_arr(t_info *info)
{
	if (!info->dist_arr)
		return;
	free (info->dist_arr);
	info->dist_arr = NULL;
}

void	clean_up_char_map(t_info *info)
{
	int	i;

	i = -1;
	if (info->map == NULL)
		return;
	while (info->map[++i])
		free (info->map[i]);
	free (info->map);
	info->map = NULL;
}

void	clean_up_p(t_info *info)
{
	if (!info->p)
		return;
	free (info->p);
	info->p = NULL;
}

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
		return;
	free (info->map_path);
	info->map_path = NULL;
}

t_img	*clean_up_one_texture(t_img *img, t_info *info)
{
	if (!img)
		return (img);
	if (img->img)
	{
		mlx_destroy_image(info->mlx_ptr, img->img); // korrekt?
		// free (img->img); // muss das hier hin?
		img->img = NULL;
	}
	if (img->addr)
	{
		free (img->addr);
		img->addr = NULL;
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
		return;
	if (LINUX)
		// mlx_loop_end(info->mlx_ptr);  // wichtig, aber nur für linux!!!!
	mlx_destroy_window(info->mlx_ptr, info->mlx_win);
	if (info->mlx_ptr)
	{
		free (info->mlx_ptr);
		info->mlx_ptr = NULL;
	}
	if (info->mlx_win)
	{
		free (info->mlx_win);
		info->mlx_win = NULL;
	}
}

char	*clean_up_one_txt_path(char *ptr)
{
	if (ptr)
	{
		free (ptr);
		ptr = NULL;
	}
	return (ptr);
}

void	clean_up_txt_colors(t_info *info)
{
	info->txt.red = clean_up_one_txt_path(info->txt.red);
	info->txt.green = clean_up_one_txt_path(info->txt.green);
	info->txt.blue = clean_up_one_txt_path(info->txt.blue);
}

void	clean_up_txt_paths(t_info *info)
{
	info->txt.path_no = clean_up_one_txt_path(info->txt.path_no);
	info->txt.path_ea = clean_up_one_txt_path(info->txt.path_ea);
	info->txt.path_so = clean_up_one_txt_path(info->txt.path_so);
	info->txt.path_we = clean_up_one_txt_path(info->txt.path_we);
	clean_up_txt_colors(info);
}



/*
* Destroyes all textures, the window and the display.
* Frees the pointer and the allocations after pressing 
* ESC or the x in the corner of the window.
*/
int	ft_free_destroy(t_info *info)
{
	clean_up_map_path(info);
	clean_up_txt_paths(info);
	clean_up_map_int(info);
	clean_up_dist_arr(info);
	clean_up_dist_info(info);
	clean_up_textures(info); //hier sind 4 leaks
	clean_up_p(info);
	clean_up_mlx_ptr_win(info);
	info = clean_up_info(info); // nicht relevant, dass info hier übergeben wird
	
	// ft_free_struct(info); // schon oben erledigt
	exit(EXIT_FAILURE);
}