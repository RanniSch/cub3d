NAME		= cub3D

CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -g -fsanitize=address

RM			= rm -f

HEADER		= inc/cub3d.h

MLX_DIR		= ./minilibx-linux/

MLX_DIR_MAC	= ./minilibx_opengl_20191021

MLX			= ./minilibx-linux/libmlx.a

MLX_MAC	= ./minilibx_opengl_20191021/libmlx.a

SRCS		= main.c \
			  ./src/rd_map.c \
			  ./src/ft_check_walls_2.c \
			  ./src/ft_check_walls.c \
			  ./src/ft_check_valid_map.c \
			  ./src/ft_parser.c \
			  ./src/ft_linear_analysis.c \
			  ./src/ft_move_2.c \
			  ./src/ft_move.c \
			  ./src/ft_raycast_scan.c \
			  ./src/ft_raycast.c \
			  ./src/ft_test_utils.c \
			  ./src/ft_vec_ops.c \
			  ./src/ft_vec_ops_2.c \
			  
			  

OBJS		= ${SRCS:.c=.o}

LIBFT_DIR	= ./libft/

LIBFT 		= ./libft/libft.a

GNL_DIR		= ./get_next_line/

GNL			= ./get_next_line/gnl.a

.PHONY:		all clean fclean re

all:		${NAME}
# ifeq (a, a)
# all:
#     echo 'true' 
# else
# all:
#     echo 'false' 
# endif


%.o: %.c	$(LIBFT) $(GNL)
			$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -c $< -o $@

$(LIBFT):
			make all -C $(LIBFT_DIR)

$(GNL):
			make all -C $(GNL_DIR)
# Ranja
# $(MLX):
# 			make -C $(MLX_DIR)

$(MLX):
			make -C $(MLX_DIR_MAC)

# Max
$(NAME):	$(MLX) Makefile $(GNL)
			$(CC) $(CFLAGS) $(LIBFT) $(GNL) $(SRCS) $(MLX_MAC)  -framework OpenGL -framework AppKit -lz -o $(NAME)

# Ranja
# $(NAME):	$(LIBFT) $(GNL) $(MLX) $(OBJS)
# 			$(CC) $(OBJS) $(LIBFT) $(GNL) $(MLX) -L/usr/X11/lib -lXext -lX11 -o $(NAME)

re:			fclean all

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)