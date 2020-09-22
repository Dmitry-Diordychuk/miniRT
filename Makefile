# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 21:06:57 by kdustin           #+#    #+#              #
#    Updated: 2020/09/22 20:48:01 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS = -L./libft/ -lft
LIBFT_DIR = ./libft/

MLX_FLAGS = -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
MLX_DIR = ./minilibx_opengl_20191021

OBJS =	minirt.o				\
		error.o					\
		bmp.o					\
		render.o				\
		file.o					\
		validate.o				\
		parse.o					\
		parse_utils.o			\
		parse_obj.o				\
		parse_light_camera.o	\
		color.o					\
		vector.o				\
		vector_other.o			\
		sphere.o				\
		object.o				\
		camera.o				\
		screen_and_canvas.o		\
		scene.o					\
		draw.o					\
		light.o					\
		ray.o					\
		reflection.o			\
		intersection.o			\
		plane.o					\
		square.o				\
		square_intersect.o		\
		square_utils.o			\
		matrix.o				\
		transformation.o		\
		point.o					\
		triangle.o				\
		triangle_intersect.o	\
		triangle_utils.o		\
		cylinder.o				\
		cylinder_intersect.o

HEADERS =	bmp.h				\
			camera.h			\
			color.h				\
			cylinder.h			\
			draw.h				\
			file.h				\
			intersection.h		\
			light.h				\
			matrix.h			\
			minirt.h			\
			object.h			\
			parse.h				\
			plane.h				\
			point.h				\
			ray.h				\
			reflection.h		\
			render.h			\
			scene.h				\
			screen_and_canvas.h	\
			sphere.h			\
			transformation.h	\
			triangle.h			\
			validate.h			\
			vars.h				\
			vector.h

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C ./libft/
	make -C ./minilibx_opengl_20191021/
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_FLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -I$(LIBFT_DIR) -I$(MLX_DIR) -o $@

clean: $(OBJS)
	make clean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/
	rm -f $^

fclean: $(OBJS)
	make fclean -C ./libft/
	make clean -C ./minilibx_opengl_20191021/
	rm -f ./minilibx_opengl_20191021/libmlx.a
	rm -f $^
	rm -f miniRT

re: fclean
	make re -C ./libft/
	make re -C ./minilibx_opengl_20191021/

