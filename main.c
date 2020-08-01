/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 19:45:20 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "color.h"
#include "vector.h"
#include "ray.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr +
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_color3d	background_color(t_ray3d r)
{
	t_vector3d	unit_direction;
	double		t;

	unit_direction = unit_vec(r.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (sum_vec(mul_vec_scalar((t_color3d){1.0, 1.0, 1.0}, 1.0 - t)
			,mul_vec_scalar((t_color3d){0.5, 0.7, 1.0}, t)));
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	width = 800;
	int	height = 600;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "MLX!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_pixel(&img, 100, 100, create_trgb(0, 255, 0, 0));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
