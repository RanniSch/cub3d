
#include "./inc/cub3d.h"

void	init_game(t_info *info)
{
	info->row = count_nb_row(info->map_path);
    //printf("num rows: %d\n", info->row);
	info->map = save_map(info);
	info->map_i = 0;
	info->player_amount = 0;
	info->player_x = -1;
	info->player_y = -1;
	info->player_orientation = '0';
}

int	main(int argc, char **argv)
{
	t_info  *info;

	if (argc != 2)
	{
		printf("Only 1 argument is required for cub3D. Try: ./cub3d [path map]\n");
		exit(0);
	}
	info = malloc(sizeof(t_info) * 1);
	info->map_path = ft_strdup(argv[1]);
    //printf("string path %s\n", info->map_path);
	init_game(info);
	if (!parsing(info))
    {
        printf("parsing false\n");
    }
    else
    {
        printf("great\n");
    }
	//if (check_if_continue(v, validator) == 1)
	//	return (0);
	//skipe_empty_line(v);
	//copy_cub_file(v);
	//update_prog(v);
	return (0);
}