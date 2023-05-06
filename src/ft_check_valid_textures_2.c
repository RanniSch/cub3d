
#include "../inc/cub3d.h"

/*
* This function moves the pointer in the string foreward until
* it reaches the first number of the rgb input in the map.
*/
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
    while (map[++j] != ',' && map[j]) // max hat hier (&& map[j]) dazu gefügt, war ein heap buffer overflow, Ranja: ist das ok?
        len++;
    info->txt.blue = ft_substr(map, j - len, len + 1);
}

/*
* This function converts the rgb numbers string into ints and
* checks that the numbers are between 0 and 255.
*/
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

/*
* This function has the if, else if, else statements to check
* weither the input from the map is 'F' for floor or 'C' for ceiling.
* ft_letter_to_rgb and ft_rgb_int_converter are called here.
*/
bool    ft_fc_helper(t_info *info, int i)
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
    return (true);
}

/*
* This function launches the process of checking for valid floor and ceiling
* and saving these values and passing them into the argb function!
*/
bool    check_valid_fc(t_info *info)
{
    int i;
    int fc;

    fc = 0;
    i = info->map_i;
    while (info->map[i][0] != '\n')
    {
        if (!ft_fc_helper(info, i))
            return (false);
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
