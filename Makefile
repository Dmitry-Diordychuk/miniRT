# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 21:06:57 by kdustin           #+#    #+#              #
#    Updated: 2020/08/05 03:46:05 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C ./libft/
	make -C ./minilibx_opengl_20191021/
	$(CC) -g -O0 main.c color.c vector.c ray.c sphere.c object.c camera.c screen_and_canvas.c -L./libft/ -lft -L./minilibx_opengl_20191021 -lmlx -I./libft/ -I./minilibx_opengl_20191021 -framework OpenGL -framework AppKit

clean:
	make clean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/
fclean:
	make fclean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/
	rm -f ./minilibx_opengl_20191021/libmlx.a

re:
	make re -C ./libft/
	make re -C ./minilibx_opengl_20191021/

