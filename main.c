/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/04 03:46:05 by kdustin          ###   ########.fr       */
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

typedef struct		viewport_s{
	const double	focal_length;
	const double	height;
	const double	width;
}			viewport_t;

typedef struct		screen_s{
	const int	width;
	const int	height;
}			screen_t;

typedef struct		canvas_s{
	const int	left_border;
	const int	right_border;
	const int	top_border;
	const int	bottom_border;
	const int	width;
	const int	height;
}			canvas_t;

void	draw_pixel(t_data *data, t_point2d p, int color)
{
	char *dst;

	dst = data->addr +
	(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**	This function transform canvas point coordinates to screen coordinates
*/

t_point2d	canvas_to_screen(t_point2d canvas_point, screen_t screen)
{
	return ((t_point2d){
			.x = screen.width / 2 + canvas_point.x,
			.y = screen.height / 2 - canvas_point.y
			});
}

/*
**	This function transform canvas point coordinates to viewport coordinates
*/

t_point3d	canvas_to_viewport(t_point2d canvas_point, canvas_t canvas, viewport_t viewport)
{
	return ((t_point3d){
		.x = canvas_point.x * (viewport.width / canvas.width),
		.y = canvas_point.y * (viewport.height / canvas.height),
		.z = viewport.focal_length
		});
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

canvas_t	create_canvas(screen_t screen)
{
	return ((canvas_t){
				.left_border	= -screen.width / 2,
				.right_border	= screen.width / 2,
				.top_border	= screen.height / 2,
				.bottom_border	= -screen.height / 2,
				.width		= screen.width,
				.height		= screen.height
				});
}

// Разобратся с t_data , разобратся с объектами ,  разобратся с возратом из решения уравнения , разобратся с цветами. 
t_data	render(screen_t screen, t_data img)
{
	//Сфера
	t_sphere sphere = (t_sphere){(t_point3d){-10, 0, 100}, 5, (t_color3d){255, 0, 0}};

	//Холст
	canvas_t	canvas = create_canvas(screen);

	//Рамка
	viewport_t	viewport = (viewport_t){1.0, 1.0, 1.0};

	//Луч
	const t_point3d	origin = (t_point3d){0, 0, 0};
	t_point3d	direction;

	int i;
	int j;
	
	j = canvas.bottom_border;
	while (j < canvas.top_border)
	{
		i = canvas.left_border;
		while (i < canvas.right_border)
		{
			direction = canvas_to_viewport((t_point2d){i, j}, canvas, viewport);
			t_ray3d r = (t_ray3d){origin, direction};
			t_color3d *color = NULL;
			if ((color = trace_ray(r, sphere)))
				draw_pixel(&img, canvas_to_screen((t_point2d){i, j}, screen), create_trgb(0, color->x, color->y, color->z));
			i++;
		}
		j++;
	}
	return (img);
}

int	main(void)
{
	screen_t	screen = (screen_t){800, 800};	
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screen.width, screen.height, "MLX!");
	img.img = mlx_new_image(mlx, screen.width, screen.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);	
	img = render(screen, img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
