
#include "../inc/cub3d.h"

bool    ft_valid_rgb_code(t_info *info, char *map)
{
    info->str_j++;
    //printf("map: %c_%d\n", map[info->str_j], info->str_j);
    if (map[info->str_j] == ' ')
    {
        info->str_j++;
        while (map[info->str_j] < 48 && map[info->str_j] > 57)
        {
            if (map[info->str_j] != ' ')
            {
                message(CHECK_TEX_9);
                return (false);
            }
            info->str_j++;
        }
        return (true);
    }
    message(CHECK_TEX_9);
    return (false);
}

/*
* This function moves the pointer in the string foreward until
* it reaches the first number of the rgb input in the map.
*/
bool    ft_letter_to_rgb(t_info *info, char *map)
{
    info->str_j = 0;
    info->len = 1;
    if (!ft_valid_rgb_code(info, map))
        return (false);
    info->str_j++;
    while (map[info->str_j] != ',')
    {
        info->str_j++;
        info->len++;
    }
    //printf("map: %c_%d %d\n", map[info->str_j], info->str_j, info->len);
    info->txt.red = ft_substr(map, info->str_j - info->len, info->len);
    //printf("_%s_\n", info->txt.red);
    if (!ft_valid_rgb_code(info, map))
        return (false);
    info->str_j++;
    info->len = 1;
    while (map[info->str_j] != ',')
    {
        info->str_j++;
        info->len++;
    }
    //printf("map: %c_%d %d\n", map[info->str_j], info->str_j, info->len);
    info->txt.green = ft_substr(map, info->str_j - info->len, info->len);
    //printf("_%s_\n", info->txt.green);
    if (!ft_valid_rgb_code(info, map))
        return (false);
    info->len = 0;
    //printf("map: %c_%d %d\n", map[info->str_j], info->str_j, info->len);
    while (map[info->str_j] && map[info->str_j] != '\n' && map[info->str_j] != ' ') // max hat hier (&& map[j]) dazu gefügt, war ein heap buffer overflow, Ranja: ist das ok?
    {
        info->str_j++;
        info->len++;
    }
    //printf("map: %c_%d %d\n", map[info->str_j], info->str_j, info->len);
    info->txt.blue = ft_substr(map, info->str_j - info->len, info->len);
    //printf("_%s_\n", info->txt.blue);
    return (true);
}

/*
* This function converts the rgb numbers string into ints and
* checks that the numbers are between 0 and 255.
*/
bool    ft_rgb_int_converter(t_info *info)
{
    info->txt.red_int = ft_atoi(info->txt.red); // first check that each element of string is between 0-9 + max 3 indexes
    info->txt.green_int = ft_atoi(info->txt.green);
    info->txt.blue_int = ft_atoi(info->txt.blue);
    //printf("F %d, %d, %d\n", info->txt.red_int, info->txt.green_int, info->txt.blue_int);
    if (info->txt.red_int < 0 || info->txt.red_int > 255)
    {
        message(CHECK_TEX_3);
        return (false);
    }
    if (info->txt.green_int < 0 || info->txt.green_int > 255)
    {
        message(CHECK_TEX_4);
        return (false);
    }
    if (info->txt.blue_int < 0 || info->txt.blue_int > 255)
    {
        message(CHECK_TEX_5);
        return (false);
    }
    return (true);
}

/*
* This function launches the process of checking for valid floor and ceiling
* and saving these values and passing them into the argb function!
* ft_letter_to_rgb and ft_rgb_int_converter are called here.
*/
bool    check_valid_fc(t_info *info, char *map, char y) // Werte von 0 - 255;
{
    if (!ft_letter_to_rgb(info, map))
        return (false);
    if (!ft_rgb_int_converter(info))
        return (false);
    if (y == 'f')
    {
        //printf("F %d, %d, %d\n", info->txt.red_int, info->txt.green_int, info->txt.blue_int); // prints floor colours!!!
        info->floor = argb(0, info->txt.red_int, info->txt.green_int, info->txt.blue_int);
    }
    if (y == 'c')
    {
        //printf("C %d, %d, %d\n", info->txt.red_int, info->txt.green_int, info->txt.blue_int); // prints ceiling colours!!!
        info->ceiling = argb(0, info->txt.red_int, info->txt.green_int, info->txt.blue_int);
    }
    clean_up_txt_colors(info);
    return (true);
}
