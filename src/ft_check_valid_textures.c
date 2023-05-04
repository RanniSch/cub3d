
#include "../inc/cub3d.h"

/*
* Checks for four textures that start either with NO, EA, SO
* or WE. 
* Saves each texture in the belonging pointer.
*/
bool    check_valid_textures(t_info *info)
{
    int i;
    int j;
    int len;
    int wall_orientations;

    wall_orientations = 0;
    i = info->map_i;
    //printf("String %s i %d\n", info->map[i], i);
    while (info->map[info->map_i][0] != '\n')
    {
        // man könnte auch noch hinzunehmen, dass jede Himmelsrichtung nur genau einmal vorkommt!
        j = 0;
        len = 0;
        if (info->map[i][0] == 'N' && info->map[i][1] == 'O')
        {
            while (info->map[info->map_i][j] != '.')
                j++;
            while (info->map[info->map_i][++j] != '\n')
                len++;
            //printf("start %d len %d\n", j - len - 1, len);
            info->txt.path_no = ft_substr(info->map[i], j - len - 1, len + 1);
            //printf("path %s\n", info->txt.path_no);
        }
        else if (info->map[i][0] == 'E' && info->map[i][1] == 'A')
        {
            while (info->map[info->map_i][j] != '.')
                j++;
            while (info->map[info->map_i][++j] != '\n')
                len++;
            //printf("start %d len %d\n", j - len - 1, len);
            info->txt.path_ea = ft_substr(info->map[i], j - len - 1, len + 1);
            //printf("path %s\n", info->txt.path_ea);
        }
        else if (info->map[i][0] == 'S' && info->map[i][1] == 'O')
        {
            while (info->map[info->map_i][j] != '.')
                j++;
            while (info->map[info->map_i][++j] != '\n')
                len++;
            //printf("start %d len %d\n", j - len - 1, len);
            info->txt.path_so = ft_substr(info->map[i], j - len - 1, len + 1);
            //printf("path %s\n", info->txt.path_so);
        }
        else if (info->map[i][0] == 'W' && info->map[i][1] == 'E')
        {
            while (info->map[info->map_i][j] != '.')
                j++;
            while (info->map[info->map_i][++j] != '\n')
                len++;
            //printf("start %d len %d\n", j - len - 1, len);
            info->txt.path_we = ft_substr(info->map[i], j - len - 1, len + 1);
            //printf("path %s\n", info->txt.path_we);
        }
        else
        { 
            printf("Invalid map: Only cardinal directions allowed!\n");
            return (false);
        }
        wall_orientations++;
        info->map_i++;
        i = info->map_i;
    }
    if (wall_orientations != 4)
    {
        printf("Invalid map: Only four cardinal directions allowed!\n");
        return (false);
    }
    return (true);
}

/*
* checks if the texture exists and for the correct extension.
*/
bool	valid_texture_extension(t_info *info)
{
	int p_len;
    int fd;

    fd = open(info->txt.path_no, O_RDONLY); // Muster wiederholt sich, kann ich eine Unterfunktion
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the texture!");
        printf("Couldn't open north texture!\n");
        close(fd);
		return (false);
	}
	p_len = ft_strlen(info->txt.path_no);
	if (ft_strncmp(&info->txt.path_no[p_len - 4], ".xpm", 4))
	{
		printf("Invalid north texture: Use .xpm texture extension\n");
        close(fd);
		return (false);
	}
	//printf("Could open texture\n");
    close(fd);

    fd = open(info->txt.path_ea, O_RDONLY);
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the texture!");
        printf("Couldn't open east texture!\n");
        close(fd);
		return (false);
	}
	p_len = ft_strlen(info->txt.path_ea);
	if (ft_strncmp(&info->txt.path_ea[p_len - 4], ".xpm", 4))
	{
		printf("Invalid east texture: Use .xpm texture extension\n");
        close(fd);
		return (false);
	}
	//printf("Could open texture\n");
    close(fd);

    fd = open(info->txt.path_so, O_RDONLY);
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the texture!");
        printf("Couldn't open south texture!\n");
        close(fd);
		return (false);
	}
	p_len = ft_strlen(info->txt.path_so);
	if (ft_strncmp(&info->txt.path_so[p_len - 4], ".xpm", 4))
	{
		printf("Invalid south texture: Use .xpm texture extension\n");
        close(fd);
		return (false);
	}
	//printf("Could open texture\n");
    close(fd);

    fd = open(info->txt.path_we, O_RDONLY);
    if (fd == -1)
	{
		//free_struct(data);
		//error_msg("Couldn't open the texture!");
        printf("Couldn't open west texture!\n");
        close(fd);
		return (false);
	}
	p_len = ft_strlen(info->txt.path_we);
	if (ft_strncmp(&info->txt.path_we[p_len - 4], ".xpm", 4))
	{
		printf("Invalid west texture: Use .xpm texture extension\n");
        close(fd);
		return (false);
	}
	//printf("Could open texture\n");
    close(fd);
	return (true);
}

void    ft_letter_to_rgb(t_info *info, char *map)
{
    int j;
    int len;

    j = 1;
    len = 0;
    while (map[j] == ' ') // Muster wiederholt sich, subfunktion????
        j++;
    while (map[++j] != ',')
        len++;
    info->txt.red = ft_substr(map, j - len - 1, len + 1);
    j++;
    while (map[j] == ' ')
        j++;
    while (map[++j] != ',')
        len++;
    info->txt.green = ft_substr(map, j - len, len + 1);
    j++;
    while (map[j] == ' ')
        j++;
    while (map[++j] != ',')
        len++;
    info->txt.blue = ft_substr(map, j - len, len + 1);
}

bool    ft_rgb_int_converter(t_info *info)
{
    info->txt.red_int = ft_atoi(info->txt.red);
    info->txt.green_int = ft_atoi(info->txt.green);
    info->txt.blue_int = ft_atoi(info->txt.blue);
    //printf("F %d, %d, %d\n", info->txt.red_int, info->txt.green_int, info->txt.blue_int);
    if (info->txt.red_int < 0 || info->txt.red_int > 255)
    {
        printf("Error: Invalid value for red!\n");
        return (false);
    }
    if (info->txt.green_int < 0 || info->txt.green_int > 255)
    {
        printf("Error: Invalid value for green!\n");
        return (false);
    }
    if (info->txt.blue_int < 0 || info->txt.blue_int > 255)
    {
        printf("Error: Invalid value for blue!\n");
        return (false);
    }
    return (true);
}

bool    check_valid_fc(t_info *info)
{
    int i;
    int fc;

    fc = 0;
    i = info->map_i;
    while (info->map[i][0] != '\n')
    {
        // man könnte auch noch hinzunehmen, dass jede Farbe nur genau einmal vorkommt!
        if (info->map[i][0] == 'F') // Werte von 0 - 255;
        {
            ft_letter_to_rgb(info, info->map[i]);
            if (!ft_rgb_int_converter(info))
                return (false);
            info->floor = argb(0, info->txt.red_int, info->txt.green_int, info->txt.blue_int);
            printf("floor %d\n", info->floor);
            clean_up_txt_colors(info);
        }
        else if (info->map[i][0] == 'C')
        {
            ft_letter_to_rgb(info, info->map[i]);
            if (!ft_rgb_int_converter(info))
                return (false);
            info->ceiling = argb(0, info->txt.red_int, info->txt.green_int, info->txt.blue_int);
			clean_up_txt_colors(info);
        }
        else
        { 
            printf("Invalid map: Only ceiling and floor allowed!\n");
            return (false);
        }
        fc++;
        info->map_i++;
        i = info->map_i;
    }
    if (fc != 2)
    {
        printf("Invalid map: There needs to be a ceiling and a floor!\n");
        return (false);
    }
    return (true);
}
