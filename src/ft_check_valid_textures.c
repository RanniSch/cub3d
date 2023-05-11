
#include "../inc/cub3d.h"

/*
* Saves each texture in the belonging pointer.
*/
bool    ft_save_path_texture(t_info *info, char *map, char x)
{
    int j;
    int len;

    j = 1;
    len = 0;
    while (map[++j] != '.')
    {
        if (map[j] != ' ')
        {
            message(CHECK_TEX_8);
            return (false);
        }
    }
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
    return (true);
}

bool    ft_texture_values(t_info *info)
{
    if (info->check_no != 1 || info->check_ea != 1 || info->check_so != 1 || info->check_we != 1)
    {
        message(CHECK_TEX_6);
        return (false);
    }
    if (info->check_c != 1 || info->check_f != 1)
    {
        message(CHECK_TEX_7);
        return (false);
    }
    return (true);
}

/*
* Checks for four textures that start either with NO, EA, SO or WE
* and for the two colours floor and ceiling.
*/
bool    check_valid_textures(t_info *info)
{
    //printf("1: %d\n", info->map_i);
    while (info->map[info->map_i])
    {
        skip_empty_lines(info);
        if (info->map[info->map_i][0] == 'N' && info->map[info->map_i][1] == 'O')
        {
            if (!ft_save_path_texture(info, info->map[info->map_i], 'n'))
                return (false);
            info->check_no++;
            //printf("NO %s\n", info->txt.path_no); // prints north texture!!!
        }
        else if (info->map[info->map_i][0] == 'E' && info->map[info->map_i][1] == 'A')
        {
            if (!ft_save_path_texture(info, info->map[info->map_i], 'e'))
                return (false);
            info->check_ea++;
            //printf("EA %s\n", info->txt.path_ea); // prints east texture!!!
        }
        else if (info->map[info->map_i][0] == 'S' && info->map[info->map_i][1] == 'O')
        {
            if (!ft_save_path_texture(info, info->map[info->map_i], 's'))
                return (false);
            info->check_so++;
            //printf("SO %s\n", info->txt.path_so); // prints south texture!!!
        }
        else if (info->map[info->map_i][0] == 'W' && info->map[info->map_i][1] == 'E')
        {
            if (!ft_save_path_texture(info, info->map[info->map_i], 'w'))
                return (false);
            info->check_we++;
            //printf("WE %s\n", info->txt.path_we); // prints west texture!!!
        }
        else if (info->map[info->map_i][0] == 'F')
        {
            if (!check_valid_fc(info, info->map[info->map_i], 'f'))
                return (false);
            info->check_f++;
        }
        else if (info->map[info->map_i][0] == 'C')
        {
            if (!check_valid_fc(info, info->map[info->map_i], 'c'))
                return (false);
            info->check_c++;
        }
        else if (info->map[info->map_i][0] == '1' || info->map[info->map_i][0] == ' ')
            break;
        else
        {
            message(CHECK_TEX_10);
            return (false);
        }
        info->map_i++;
        //printf("2: %d\n", info->map_i);
    }
    if (!ft_texture_values(info))
        return (false);
    //printf("NO %s\n", info->txt.path_no); // prints north texture!!!
    //printf("SO %s\n", info->txt.path_so); // prints south texture!!!
    //printf("WE %s\n", info->txt.path_we); // prints west texture!!!
    //printf("EA %s\n", info->txt.path_ea); // prints east texture!!!
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
	//printf("Could open texture\n");
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
