# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/05 15:53:34 by mtaylor           #+#    #+#              #
#    Updated: 2019/01/23 16:27:19 by mtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FLAGS = -Wall -Wextra -Werror

## Libraries
LIBFT = ./libft/libft.a
LIBMLX = ./miniLibX/libmlx.a -framework OpenGL -framework AppKit
LIB = -I libft/ -I miniLibX/ $(LIBFT) $(LIBMLX)

INCDIR	= -I ./includes/

SRCS = main.c \
	   window_and_image.c \
	   array.c dimensions.c \
	   color_gradient.c color_scheme.c \
	   draw.c line.c xy.c \
	   errors.c \
	   plot_iso.c plot_perspective.c center.c

all : $(NAME)

$(NAME) :
	make -C ./libft
	make -C ./miniLibX
	gcc $(FLAGS) $(LIB) $(addprefix ./src/, $(SRCS)) $(INCDIR) -o $(NAME)

clean :
	make -C ./libft clean
	make -C ./miniLibX clean

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all
