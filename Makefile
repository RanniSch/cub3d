NAME		= cub3D

CC			= gcc

CFLAGS		= -Wextra -Wall -g #-fsanitize=address #-Werror #-fsanitize=leak

RM			= rm -f

HEADER		= inc/cub3d.h

MLX_DIR		= ./minilibx-linux/

MLX_DIR_MAC	= ./minilibx_opengl_20191021

MLX			= ./minilibx-linux/libmlx.a

MLX_MAC	= ./minilibx_opengl_20191021/libmlx.a

SRCS		= main.c \
			  ./src/ft_rd_map.c \
			  ./src/ft_check_valid_textures.c \
			  ./src/ft_check_valid_textures_extension.c \
			  ./src/ft_check_valid_fc.c \
			  ./src/ft_check_valid_fc_2.c \
			  ./src/ft_check_num_textures.c \
			  ./src/ft_check_walls_2.c \
			  ./src/ft_check_walls.c \
			  ./src/ft_check_valid_map.c \
			  ./src/ft_parser.c \
			  ./src/ft_map_converter_2.c \
			  ./src/ft_map_converter.c \
			  ./src/ft_linear_analysis.c \
			  ./src/ft_move_2.c \
			  ./src/ft_move.c \
			  ./src/ft_raycast_scan.c \
			  ./src/ft_raycast.c \
			  ./src/ft_raycast_utils.c \
			  ./src/ft_test_utils.c \
			  ./src/ft_vec_ops.c \
			  ./src/ft_vec_ops_2.c \
			  ./src/ft_draw_textures_2.c \
			  ./src/ft_draw_textures_3.c \
			  ./src/ft_draw_textures.c \
			  ./src/ft_init.c \
			  ./src/ft_init_info.c \
			  ./src/ft_clean_up.c \
			  ./src/ft_clean_up_2.c \
			  ./src/ft_clean_up_3.c \
			  ./src/ft_message.c \
			  

OBJS		= ${SRCS:.c=.o}

LIBFT_DIR	= ./libft/

LIBFT 		= ./libft/libft.a

GNL_DIR		= ./get_next_line/

GNL			= ./get_next_line/gnl.a

.PHONY:		all clean fclean re

all:		${NAME}



ifeq ($(shell uname), Darwin)
# Max
%.o: %.c	$(LIBFT) $(GNL)
			$(CC) -Wall -Wextra -g -c $< -o $@ 
#-Werror
else
# Ranja
%.o: %.c	$(LIBFT) $(GNL)
			$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -c $< -o $@
endif



$(LIBFT):
			make all -C $(LIBFT_DIR)

$(GNL):
			make all -C $(GNL_DIR)

ifeq ($(shell uname), Darwin)
# Max
$(MLX):
			make -C $(MLX_DIR_MAC)
else
# Ranja
$(MLX):
			make -C $(MLX_DIR)
endif

# Max
ifeq ($(shell uname), Darwin)
$(NAME):	$(LIBFT) $(MLX) $(GNL) $(OBJS)
			$(CC) $(CFLAGS) $(LIBFT) $(GNL) $(SRCS) $(MLX_MAC)  -framework OpenGL -framework AppKit -lz -o $(NAME)
else
# Ranja
$(NAME):	$(LIBFT) $(GNL) $(MLX) $(OBJS)
			$(CC) $(OBJS) $(LIBFT) $(GNL) $(MLX) -L/usr/X11/lib -lXext -lX11 -lm -o $(NAME)
endif

MAP = "maps/test29.cub"

e:	all
			./$(NAME) $(MAP)
#ASAN_OPTIONS=detect_leaks=1

l:	all
			leaks --atExit -- ./$(NAME) $(MAP)

re:			fclean all

clean:
			$(RM) $(OBJS)
			make clean -C $(LIBFT_DIR)
			make clean -C $(GNL_DIR)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C $(LIBFT_DIR)
			make fclean -C $(GNL_DIR)