# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 21:25:34 by rschlott          #+#    #+#              #
#    Updated: 2023/04/07 16:51:48 by rschlott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc

SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_split.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_one_split.c

SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c	

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

#If objeft doesnt exist, it will create one
OBJS =      $(SRC:.c=.o)

OBJSBONUS =      $(SRCBONUS:.c=.o) $(OBJS)

$(NAME): $(OBJS) $(SRC)
	ar rcs $(NAME) $(OBJS)
	
all: $(NAME)
 
bonus: $(OBJSBONUS)
	ar rcs $(NAME) $(OBJSBONUS)
	
clean:
	$(RM) $(OBJSBONUS)

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