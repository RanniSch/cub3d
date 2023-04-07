
NAME = gnl.a
CC = gcc

SRC =	get_next_line.c \
		get_next_line_utils.c

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

#If objeft doesnt exist, it will create one
OBJS =      $(SRC:.c=.o)

$(NAME): $(OBJS) $(SRC)
	ar rcs $(NAME) $(OBJS)
	
all: $(NAME)
 
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# if object file doesnt exist, or soruce file has changed, (refers to) two different files
%.o: %.c
	$(CC) -c $^ $(CFLAGS)  -o $@

#remmeber to add  "libft.so" to clean
#so:
#	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRCBONUS) 
#	gcc -nostartfiles -shared -o libft.so $(OBJSBONUS)

re: fclean all

.PHONY: all fclean re bonus