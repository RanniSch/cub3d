#include "../inc/cub3d.h"

/*
* This function moves the pointer in the string foreward until
* it reaches the first number of the rgb input in the map.
*/
bool	ft_letter_to_rgb(t_info *info, char *map)
{
	info->str_j = 0;
	info->substr = 1;
	if (!ft_valid_rgb_code(info, map))
		return (false);
	info->str_j++;
	if (!ft_valid_rgb_code_2(info, map))
		return (false);
	info->txt.red = ft_substr(map, info->str_j - info->substr, info->substr);
	if (!ft_valid_rgb_code(info, map))
		return (false);
	info->str_j++;
	info->substr = 1;
	if (!ft_valid_rgb_code_2(info, map))
		return (false);
	info->txt.green = ft_substr(map, info->str_j - info->substr, info->substr);
	if (!ft_valid_rgb_code(info, map))
		return (false);
	info->substr = 0;
	while (map[info->str_j] && map[info->str_j] != '\n')
	{
		info->str_j++;
		info->substr++;
	}
	info->txt.blue = ft_substr(map, info->str_j - info->substr, info->substr);
	return (true);
}

bool	ft_valid_rgb_char(char *colour_str)
{
	int	i;

	i = -1;
	while (colour_str[++i] != '\0')
	{
		if (colour_str[i] < 48 || colour_str[i] > 57)
		{
			message(CHECK_TEX_11);
			return (false);
		}
	}
	return (true);
}

/*
* This function converts the rgb numbers string into ints and
* checks that the numbers are between 0 and 255.
*/
bool	ft_rgb_int_converter(t_info *info)
{
	if (!ft_valid_rgb_char(info->txt.red))
		return (false);
	if (!ft_valid_rgb_char(info->txt.green))
		return (false);
	if (!ft_valid_rgb_char(info->txt.blue))
		return (false);
	info->txt.red_int = ft_atoi(info->txt.red);
	info->txt.green_int = ft_atoi(info->txt.green);
	info->txt.blue_int = ft_atoi(info->txt.blue);
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
bool	check_valid_fc(t_info *info, char *map, char y)
{
	if (!ft_letter_to_rgb(info, map))
	{
		info->check_colour++;
		return (false);
	}
	if (!ft_rgb_int_converter(info))
	{
		info->check_colour++;
		return (false);
	}
	if (y == 'f')
	{
		info->check_f++;
		info->floor = argb(0, info->txt.red_int, info->txt.green_int,
				info->txt.blue_int);
	}
	if (y == 'c')
	{
		info->check_c++;
		info->ceiling = argb(0, info->txt.red_int, info->txt.green_int,
				info->txt.blue_int);
	}
	clean_up_txt_colors(info);
	return (true);
}
