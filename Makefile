# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 21:06:57 by kdustin           #+#    #+#              #
#    Updated: 2020/09/22 18:52:32 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make bonus -C ./libft/
	make -C ./minilibx_opengl_20191021/
	$(CC) -g minirt.c error.c bmp.c render.c file.c validate.c parse.c parse_utils.c parse_obj.c parse_light_camera.c color.c vector.c vector_other.c sphere.c object.c camera.c \
	screen_and_canvas.c scene.c draw.c light.c ray.c reflection.c intersection.c plane.c square.c square_intersect.c square_utils.c matrix.c transformation.c point.c triangle.c triangle_intersect.c triangle_utils.c cylinder.c cylinder_intersect.c -L./libft/ -lft -L./minilibx_opengl_20191021 -lmlx -I./libft/ -I./minilibx_opengl_20191021 -framework OpenGL -framework AppKit -o miniRT


clean:
	make clean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/

fclean:
	make fclean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/
	rm -f ./minilibx_opengl_20191021/libmlx.a
	rm -f miniRT

re: fclean
	make re -C ./libft/
	make re -C ./minilibx_opengl_20191021/

