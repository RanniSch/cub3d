
#include "../inc/cub3d.h"

/*
* Checks the correct amount of textures and rgb colours.
* Only one NO, EA, SO, WE, F and C allowed.
*/
bool	ft_texture_values(t_info *info)
{
	if (info->check_no != 1 || info->check_ea != 1 || info->check_so != 1
		|| info->check_we != 1)
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
