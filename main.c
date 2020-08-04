/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/04 21:05:59 by kdustin          ###   ########.fr       */
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

typedef struct		s_viewport {
	const double	focal_length;
	const double	height;
	const double	width;
}			t_viewport;

typedef struct		s_screen {
	const int	width;
	const int	height;
	const int	aspect_ratio;
}			t_screen;

typedef struct		s_canvas {
	const int	left_border;
	const int	right_border;
	const int	top_border;
	const int	bottom_border;
	const int	width;
	const int	height;
}			t_canvas;

typedef	struct		s_camera {
	t_ray3d		ray;
	t_viewport	viewport;
}			t_camera;

typedef struct		s_object {
	char		*name;
	void		*obj;
	double		*(*intersect)(t_ray3d, void*);
	t_color3d	color;
}			t_object;

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

t_point2d	canvas_to_screen(t_point2d canvas_point, t_screen screen)
{
	return ((t_point2d){
			.x = screen.width / 2 + canvas_point.x,
			.y = screen.height / 2 - canvas_point.y
			});
}

/*
**	This function transform canvas point coordinates to viewport coordinates
*/

t_point3d	canvas_to_viewport(t_point2d canvas_point, t_canvas canvas, t_viewport viewport)
{
	return ((t_point3d){
		.x = canvas_point.x * (viewport.width / canvas.width) * 4 / 3,
		.y = canvas_point.y * (viewport.height / canvas.height), 
		.z = viewport.focal_length
		});
}

/*
**	Передадим массив объектов сцены. Пока заглушка. необходимо обдумать маллок или возращать ошибку.
*/

int	trace_ray(t_ray3d r, t_list *objects)
{
	double		*crossing_point;
	t_object	obj;

	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (ft_strcmp(obj.name, "Sphere") == 0)
		{
			if (!(crossing_point = obj.intersect(r, obj.obj)))
				return (-2);
			if (crossing_point[0] > 0 || crossing_point[1] > 0)
				return (create_trgb(0, obj.color.x, obj.color.y, obj.color.z));
		}
		objects = objects->next;
	}
	return (-1);
}

t_canvas	create_canvas(t_screen screen)
{
	return ((t_canvas){
				.left_border	= -screen.width / 2,
				.right_border	= screen.width / 2,
				.top_border	= screen.height / 2,
				.bottom_border	= -screen.height / 2,
				.width		= screen.width,
				.height		= screen.height
				});
}

t_object	create_object(const char *name, void *obj, t_color3d color)
{
	if (ft_strcmp(name, "Sphere") == 0)
		return ((t_object){ft_strdup(name), obj, intersect_sphere, color});
}

void	*create_sphere(double x, double y, double z, double r)   		// malloc
{
	t_sphere *s;

	if (!(s = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	s->coor = (t_point3d){
				.x = x,
				.y = y,
				.z = z
				};
	s->r = r;
	return ((void*)s);
}

// Разобратся с t_data , разобратся с объектами ,  разобратся с возратом из решения уравнения , разобратся с цветами. 
t_data	render(t_screen screen, t_data img)
{

	//Сфера 
	t_object	obj2 = create_object("Sphere", create_sphere(-10, 10, 100, 1), (t_color3d){0, 255, 0});
	t_object	obj = create_object("Sphere", create_sphere(10, 10, 100, 5), (t_color3d){255, 0, 0});
	t_list		*objects;

	objects = ft_lstnew((void*)&obj);
	ft_lstadd_back(&objects, ft_lstnew((void*)&obj2));

	//Холст
	t_canvas	canvas = create_canvas(screen);

	t_camera	camera;
	int		x;
	int		y;
	int		color;

	camera.viewport = (t_viewport){1.0, 1.0, 1.0};
	camera.ray.origin = (t_point3d){0, 0, 0};
	y = canvas.top_border;
	while (y > canvas.bottom_border)
	{
		x = canvas.left_border;
		while (x < canvas.right_border)
		{
			draw_pixel(&img, canvas_to_screen((t_point2d){x, y}, screen), create_trgb(0, 0, 200 - canvas.height / 5 + y / 5, 255 - canvas.height / 5 + y / 5));
			camera.ray.direction = canvas_to_viewport((t_point2d){x, y}, canvas, camera.viewport);
			if ((color = trace_ray(camera.ray, objects)) >= 0)
				draw_pixel(&img, canvas_to_screen((t_point2d){x, y}, screen), color);
			else if (color == -2)
				break; ///////////////////////////////////////обработка ошибки
			x++;
		}
		y--;
	}
	return (img);
}

int	main(void)
{
	t_screen	screen = (t_screen){800, 600, 4 / 3};	
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
