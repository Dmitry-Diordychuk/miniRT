/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 21:58:40 by kdustin          ###   ########.fr       */
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

typedef struct	s_point2d {
	int	x;
	int	y;
}		t_point2d;

typedef struct		s_sphere {
	t_vector3d	coor;
	double		r;
}			t_sphere;

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr +
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_point2d	canvas_to_screen(t_point2d c, int canvas_width, int canvas_height)
{
	return ((t_point2d){canvas_width / 2 + c.x, canvas_height / 2 - c.y});
}

t_point3d	canvas_to_viewport(t_point2d c, int canvas_width, int canvas_height, int viewport_width, int viewport_height, double viewport_d)
{
	return ((t_point3d){c.x * (viewport_width / canvas_width), c.y * (viewport_height / canvas_height), viewport_d});
}

double		get_sphere_t(t_ray3d r, t_sphere s)
{
	double		k1;
	double		k2;
	double		k3;
	t_vector3d	oc;

	oc = minus_vec(r.origin, s.coor); 
	k1 = dot_vec(r.direction, r.direction);
	k2 = 2 * dot_vec(oc, r.direction);
	k3 = dot_vec(oc, oc) - s.r * s.r;
	//Решение k1 * t^2 + k2 * t + k3 = 0
	return (0);
}

int	main(void)
{
	t_point3d	origin;
	//Рамка
	double		focal_length = 1.0;
	double		viewport_height = 1.0;
	double		viewport_width = 1.0;

	origin = (t_point3d){0, 0, 0};
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	width = 800;
	int	height = 600;

	//Холст
	double		canvas_center_x = width / 2;
	double		canvas_center_y = height / 2;		

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "MLX!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i = 0;
	int j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			draw_pixel(&img, i, j, create_trgb(0, 255, 0, 0));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
