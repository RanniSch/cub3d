
#include "../inc/cub3d.h"

/*
* Saves each texture in the belonging pointer.
*/
void    ft_save_path_texture(t_info *info, char *map, char x)
{
    int j;
    int len;

    j = 0;
    len = 0;
    while (map[j] != '.')
        j++;
    while (map[++j] != '\n')
        len++;
    //printf("start %d len %d\n", j - len - 1, len);
    if (x == 'n')
        info->txt.path_no = ft_substr(map, j - len - 1, len + 1);
    if (x == 'e')
        info->txt.path_ea = ft_substr(map, j - len - 1, len + 1);
    if (x == 's')
        info->txt.path_so = ft_substr(map, j - len - 1, len + 1);
    if (x == 'w')
        info->txt.path_we = ft_substr(map, j - len - 1, len + 1);
    //printf("path %s\n", info->txt.path_no);
}

/*
* Checks for four textures that start either with NO, EA, SO
* or WE.
*/
bool    check_valid_textures(t_info *info)
{
    int i;
    int wall_orientations;

    wall_orientations = 0;
    i = info->map_i;
    while (info->map[i][0] != '\n')
    {
        // man könnte auch noch hinzunehmen, dass jede Himmelsrichtung nur genau einmal vorkommt
        if (info->map[i][0] == 'N' && info->map[i][1] == 'O')
            ft_save_path_texture(info, info->map[i], 'n');
        else if (info->map[i][0] == 'E' && info->map[i][1] == 'A')
            ft_save_path_texture(info, info->map[i], 'e');
        else if (info->map[i][0] == 'S' && info->map[i][1] == 'O')
            ft_save_path_texture(info, info->map[i], 's');
        else if (info->map[i][0] == 'W' && info->map[i][1] == 'E')
            ft_save_path_texture(info, info->map[i], 'w');
        else
            return (false);
        wall_orientations++;
        info->map_i++;
        i = info->map_i;
    }
    if (wall_orientations != 4)
        return (false);
    return (true);
}

/*
* The process of checking every texture extention and if
* the texture can be opened.
*/
bool    ft_texture_extension_helper(char *path_texture)
{
    int p_len;
    int fd;

    fd = open(path_texture, O_RDONLY);
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the texture!");
        printf("Couldn't open path of texture!\n");
        close(fd);
		return (false);
	}
	p_len = ft_strlen(path_texture);
	if (ft_strncmp(&path_texture[p_len - 4], ".xpm", 4))
	{
		printf("Invalid path of texture: Use .xpm texture extension\n");
        close(fd);
		return (false);
	}
	//printf("Could open texture\n");
    close(fd);
    return (true);
}

/*
* checks if the texture exists and for the correct extension.
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
