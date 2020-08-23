# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 21:06:57 by kdustin           #+#    #+#              #
#    Updated: 2020/08/22 23:58:37 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make bonus -C ./libft/
	make -C ./minilibx_opengl_20191021/
	$(CC) -g minirt.c color.c vector.c sphere.c object.c camera.c \
	screen_and_canvas.c scene.c draw.c light.c ray.c reflection.c -L./libft/ -lft -L./minilibx_opengl_20191021 -lmlx -I./libft/ -I./minilibx_opengl_20191021 -framework OpenGL -framework AppKit

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

