#include "../inc/cub3d.h"

void	print_dist_arr_info(t_info *info)
{
	int	i;

	i = -1;
	printf("\ndistance  col row  card_dir\n\n");
	while (++i < DISPLAY_WIDTH)
	{
		printf("%f   %d   %d   ", info->dist_arr[i], \
			info->dist_info[0][i], info->dist_info[1][i]);
		if (info->dist_info[2][i] == EAST)
			printf("EAST ");
		else if (info->dist_info[2][i] == WEST)
			printf("WEST ");
		else if (info->dist_info[2][i] == NORTH)
			printf("NORTH ");
		else if (info->dist_info[2][i] == SOUTH)
			printf("SOUTH ");
		printf("%d   %d\n", info->dist_info[3][i], info->dist_info[4][i]);
		if ((i + 1) % 10 == 0)
			printf("-----------------------------  %d\n", (i + 1));
	}
}

void	print_2d_arr(int **array, int row, int col)
{
	int	j;

	while (--row >= 0)
	{
		j = -1;
		while (++j < col)
		{
			if (array[row][j] == 1)
				printf("1");
			else if (array[row][j] == 0)
				printf(" ");
			else
				printf("ERROR");
		}
		printf("\n");
	}
}

void	draw_one_height(int x, int height_on_x_value, t_img *img)
{
	int	diff;
	int	y;

	y = -1;
	diff = DISPLAY_HEIGHT - height_on_x_value;
	while (++y < DISPLAY_HEIGHT - diff)
	{
		my_mlx_pixel_put(img, x, (y + diff / 2), 0x009fc5e8);
	}
}

void	draw_wallshadows(double *dist_arr, t_img *img)
{
	int		i;
	double	height_on_x_value;

	i = -1;
	while (++i < DISPLAY_WIDTH)
	{
		height_on_x_value = DISPLAY_HEIGHT * FACTOR_WALL_HEIGHT / dist_arr[i];
		draw_one_height(i, round(height_on_x_value), img);
	}
}
