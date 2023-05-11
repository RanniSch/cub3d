
#include "../inc/cub3d.h"

/*
* The process of checking every texture extention and if
* the texture can be opened.
*/
bool	ft_texture_extension_helper(char *path_texture)
{
	int	p_len;
	int	fd;

	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
	{
		message(CHECK_TEX_1);
		close(fd);
		return (false);
	}
	p_len = ft_strlen(path_texture);
	if (ft_strncmp(&path_texture[p_len - 4], ".xpm", 4))
	{
		message(CHECK_TEX_2);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

/*
* checks if the texture exists and for the correct extension.
* Calls the function ft_texture_extension_helper.
*/
bool	valid_texture_extension(t_info *info)
{
	if (!ft_texture_extension_helper(info->txt.path_no))
	{
		return (false);
	}
	if (!ft_texture_extension_helper(info->txt.path_ea))
	{
		return (false);
	}
	if (!ft_texture_extension_helper(info->txt.path_so))
	{
		return (false);
	}
	if (!ft_texture_extension_helper(info->txt.path_we))
	{
		return (false);
	}
	return (true);
}
