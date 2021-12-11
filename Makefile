# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamori <velvelhype@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 03:20:19 by kamori            #+#    #+#              #
#    Updated: 2021/11/23 04:47:58 by kamori           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
CC = gcc
# CFLAGS = -Werror -Wall -Wextra
CFLAGS = 
SRCS = main.c \
read_file.c \
check.c \
draw.c \
# draw.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) \
	minilibx_macos/libmlx.a \
	-framework OpenGL -framework AppKit \
	libft/libft.a -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
	make re -C libft