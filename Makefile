NAME		= cub3d

CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -g -fsanitize=address

RM			= rm -f

HEADER		= inc/cub3d.h

MLX_DIR		= ./minilibx-linux/

MLX			= ./minilibx-linux/libmlx.a

SRCS		= main.c \
			  ./src/rd_map.c \
			  ./src/ft_parser.c \
			  ./src/ft_check_walls.c
			  

OBJS		= ${SRCS:.c=.o}

LIBFT_DIR	= ./libft/

LIBFT 		= ./libft/libft.a

GNL_DIR		= ./get_next_line/

GNL			= ./get_next_line/gnl.a

.PHONY:		all clean fclean re

all:		${NAME}

%.o: %.c	$(LIBFT) $(GNL)
			$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -c $< -o $@

$(LIBFT):
			make all -C $(LIBFT_DIR)

$(GNL):
			make all -C $(GNL_DIR)

$(MLX):
			make -C $(MLX_DIR)


$(NAME):	$(LIBFT) $(GNL) $(MLX) $(OBJS)
			$(CC) $(OBJS) $(LIBFT) $(GNL) $(MLX) -L/usr/X11/lib -lXext -lX11 -o $(NAME)

re:			fclean all

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)