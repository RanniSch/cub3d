#include "../inc/cub3d.h"

void	print_dist_arr_info(t_info *info)
{
	int i;
	// int up_left;
	// int down_left;
	// int up_right;
	// int down_right;
	// double	height_on_x_value;
	// double	buf;

	i = -1;
	printf("\ndistance  col row  card_dir\n\n");
	while(++i < DISPLAY_WIDTH)
	{

		// height_on_x_value = DISPLAY_HEIGHT * FACTOR_WALL_HEIGHT / info->dist_arr[i];
		// buf = round((DISPLAY_HEIGHT - height_on_x_value) / 2);
		// up_left = (int)(buf + 0.1);
		// buf = up_left + height_on_x_value;
		// down_left = (int)(buf + 0.1);
		printf("%f   %d   %d   ", info->dist_arr[i], info->dist_info[0][i], info->dist_info[1][i]);
		if(info->dist_info[2][i] == EAST)
			printf("EAST ");
		else if(info->dist_info[2][i] == WEST)
			printf("WEST ");
		else if(info->dist_info[2][i] == NORTH)
			printf("NORTH ");
		else if(info->dist_info[2][i] == SOUTH)
			printf("SOUTH ");
		printf("%d   %d\n", info->dist_info[3][i], info->dist_info[4][i]);
		if ((i+1)%10 == 0)
			printf("-----------------------------  %d\n", (i+1));
	}
}

void	print_2d_arr(int **array, int row, int col)
{
	while (--row >= 0)
	{
		int j = -1;
		while (++j < col)
			printf("%d ", array[row][j]);
		printf("\n");
	}
}

void	draw_one_height(int x, int height_on_x_value, t_img *img)
{
	int diff;
	int y;

	y = -1;
	diff = DISPLAY_HEIGHT - height_on_x_value;
	while (++y < DISPLAY_HEIGHT - diff)
	{
		my_mlx_pixel_put(img, x, (y + diff/2), 0x009fc5e8);
	}
}

void	draw_wallshadows(double *dist_arr, t_img *img)
{
	int i;
	double height_on_x_value;

	i = -1;
	while (++i < DISPLAY_WIDTH)
	{
		height_on_x_value = DISPLAY_HEIGHT * FACTOR_WALL_HEIGHT / dist_arr[i];
		draw_one_height(i, round(height_on_x_value), img);
	}
}