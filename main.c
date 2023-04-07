
#include "./inc/cub3d.h"

void	init_game(t_info *info)
{
	info->row = count_nb_row(info->map_path);
    printf("num rows: %d\n", info->row);
	info->map = save_map(info);
	//info->map_i = 0;
	//info->tex.path_no = NULL;
	//info->tex.path_so = NULL;
	//info->tex.path_ea = NULL;
	//info->tex.path_we = NULL;
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
	parsing(info);
	//if (check_if_continue(v, validator) == 1)
	//	return (0);
	//skipe_empty_line(v);
	//copy_cub_file(v);
	//update_prog(v);
	return (0);
}