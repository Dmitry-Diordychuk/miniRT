/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/03 20:13:18 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include "mlx.h"
#include "color.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"

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

void	draw_pixel(t_data *data, t_point2d p, int color)
{
	char *dst;

	dst = data->addr +
	(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_point2d	canvas_to_screen(t_point2d c, int canvas_width, int canvas_height)
{
	return ((t_point2d){canvas_width / 2 + c.x, canvas_height / 2 - c.y});
}

t_point3d	canvas_to_viewport(t_point2d c, int canvas_width, int canvas_height, int viewport_width, int viewport_height, double viewport_d)
{
	return ((t_point3d){(double)c.x * ((double)viewport_width / (double)canvas_width), (double)c.y * ((double)viewport_height / (double)canvas_height), (double)viewport_d});
}

/*
**	Передадим массив объектов сцены. Пока заглушка. необходимо обдумать маллок или возращать ошибку.
*/

t_color3d *trace_ray(t_ray3d r, t_sphere s)
{
	double *crossing_point;

	if (!(crossing_point = get_sphere_crossing(r, s)))
		return (NULL);
	if (crossing_point[0] > 0 || crossing_point[1] > 0)
		return (&(s.color));
	return (NULL);
}

int	main(void)
{
	t_point3d	origin;
	//Сфера
	t_sphere sphere = (t_sphere){(t_point3d){-10, 0, 100}, 5, (t_color3d){255, 0, 0}};

	//Рамка
	double		focal_length = 1.0;
	double		viewport_height = 1.0;
	double		viewport_width = 1.0;

	origin = (t_point3d){0, 0, 0};
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	width = 800;
	int	height = 800;

	//Холст
	double		canvas_width = width / 2;
	double		canvas_height = height / 2;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "MLX!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i;
	int j = -canvas_width;
	while (j < canvas_height)
	{
		i = -canvas_width;
		while (i < canvas_width)
		{
			t_point3d p3 = canvas_to_viewport((t_point2d){i, j}, width, height, viewport_width, viewport_height, focal_length);
			t_ray3d r = (t_ray3d){origin, p3};
			t_color3d *color = NULL;
			if ((color = trace_ray(r, sphere)))
				draw_pixel(&img, canvas_to_screen((t_point2d){i, j}, width, height), create_trgb(0, color->x, color->y, color->z));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
