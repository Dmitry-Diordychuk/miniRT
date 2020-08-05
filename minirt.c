/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 14:20:45 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_data *data, t_point2d p, int color)
{
	char *dst;

	dst = data->addr +
	(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**	choose_obj_type
*/

int	choose_obj_intersect(t_ray3d r, t_object obj, double *nearest_root,
							t_object *nearest_obj)               //malloc
{
	double	*roots;

	if (ft_strcmp(obj.name, "Sphere") == 0)
	{
		if (!(roots = obj.intersect(r, obj.obj)))
			return (-1);
		if ((roots[0] > -1 || roots[1] > -1) &&
		(*nearest_root == -1 || (roots[0] < *nearest_root || roots[1] <
								*nearest_root)))
		{
			*nearest_obj = obj;
			*nearest_root = roots[0] < roots[1] ?
							roots[0] : roots[1];
		}
		free(roots);
	}
	return (0);
}

/*
**	Передадим массив объектов сцены. Пока заглушка. необходимо обдумать маллок или возращать ошибку.
*/

int	trace_ray(t_ray3d r, t_list *objects)
{
	double		*crossing_point;
	t_object	obj;
	t_object	nearest_obj;
	double		nearest_root;

	nearest_root = -1;
	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (choose_obj_intersect(r, obj, &nearest_root, &nearest_obj)
									< 0)
			return (-2);
		objects = objects->next;
	}
	if (nearest_root != -1)
		return (create_trgb(0, nearest_obj.color.x,
				nearest_obj.color.y, nearest_obj.color.z));
	return (-1);
}

typedef struct		s_scene {
	t_camera	camera;
	t_list		*objects;
}			t_scene;



// Разобратся с t_data , разобратся с объектами ,  разобратся с возратом из решения уравнения , разобратся с цветами, разобратся с аспкктом 
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
