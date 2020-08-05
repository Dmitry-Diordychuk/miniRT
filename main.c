/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:50:24 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include "mlx.h"
#include "color.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "object.h"
#include "camera.h"
#include "screen_and_canvas.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

void	draw_pixel(t_data *data, t_point2d p, int color)
{
	char *dst;

	dst = data->addr +
	(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**	Передадим массив объектов сцены. Пока заглушка. необходимо обдумать маллок или возращать ошибку.
*/

int	trace_ray(t_ray3d r, t_list *objects)
{
	double		*crossing_point;
	t_object	obj;
	t_object	obj_in_front;
	double		t_in_front;

	t_in_front = -1;
	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (ft_strcmp(obj.name, "Sphere") == 0)
		{
			if (!(crossing_point = obj.intersect(r, obj.obj)))
				return (-2);
			if (crossing_point[0] > -1 || crossing_point[1] > -1)
			{
				if (t_in_front == -1 || (crossing_point[0] < t_in_front || crossing_point[1] < t_in_front))
				{
					obj_in_front = obj;
					t_in_front = crossing_point[0] < crossing_point[1] ? crossing_point[0] : crossing_point[1];
				}
			}
			free(crossing_point);
		}
		objects = objects->next;
	}
	if (t_in_front != -1)
		return (create_trgb(0, obj_in_front.color.x, obj_in_front.color.y, obj_in_front.color.z));
	return (-1);
}

// Разобратся с t_data , разобратся с объектами ,  разобратся с возратом из решения уравнения , разобратся с цветами. 
t_data	render(t_screen screen, t_data img)
{

	//Сфера 
	t_object	obj2 = create_object("Sphere", create_sphere(-10, 10, 95, 1), (t_color3d){0, 255, 0});
	t_object	obj = create_object("Sphere", create_sphere(-10, 10, 100, 5), (t_color3d){255, 0, 0});
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
