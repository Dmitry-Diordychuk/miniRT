/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 00:33:45 by kdustin          ###   ########.fr       */
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

	if (!(roots = obj.intersect_function(r, obj.container)))
		return (-1);
	if ((roots[0] > -1 || roots[1] > -1) &&
	(*nearest_root == -1 || (roots[0] < *nearest_root || roots[1] <
								*nearest_root)))
	{
		*nearest_obj = obj;
		*nearest_root = roots[0] < roots[1] ? roots[0] : roots[1];
	}
	free(roots);
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
		return (create_trgb(0, nearest_obj.color.x, nearest_obj.color.y,
							nearest_obj.color.z));
	return (-1);
}

t_list	*init_objects()
{
	t_object	*obj;
	t_list		*temp;
	t_list		*objects;

	if (!(obj = create_object("Sphere", create_sphere((t_point3d){-10, 10, 95}, 1), (t_color3d){0, 255, 0})))
		return (NULL);
	if (!(objects = ft_lstnew((void*)obj)))
	{
		delete_object((void*)obj);
		return (NULL);
	}
	if (!(obj = create_object("Sphere", create_sphere((t_point3d){-10, 10, 100}, 5), (t_color3d){255, 0, 0})))
	{
		ft_lstclear(&objects, delete_object);
		return (NULL);
	}
	if (!(temp = ft_lstnew((void*)obj)))
	{	
		delete_object((void*)obj);
		ft_lstclear(&objects, delete_object);
		return (NULL);
	}
	ft_lstadd_back(&objects, temp);
	return (objects);
}

typedef struct	s_scene {
	t_camera	camera;
	t_list		*objects;
}		t_scene;

// Разобратся с t_data , разобратся с объектами ,  разобратся с возратом из решения уравнения , разобратся с цветами, разобратся с аспкктом 
int	render(t_screen screen, t_data *img)
{
	t_canvas	canvas = create_canvas(screen);
	t_scene		scene;
	t_point2d	point;
	int		color;

	scene.objects = init_objects();
	scene.camera.viewport = (t_viewport){1.0, 1.0, 1.0};
	scene.camera.ray.origin = (t_point3d){0, 0, 0};
	point.y = canvas.top_border;
	while (point.y > canvas.bottom_border)
	{
		point.x = canvas.left_border;
		while (point.x < canvas.right_border)
		{
			draw_pixel(img, canvas_to_screen(point, screen), create_trgb(0, 0, 200 - canvas.height / 5 + point.y / 5, 255 - canvas.height / 5 + point.y / 5));
			scene.camera.ray.direction = canvas_to_viewport(point, canvas, scene.camera.viewport);
			if ((color = trace_ray(scene.camera.ray, scene.objects)) >= 0)
				draw_pixel(img, canvas_to_screen(point, screen), color);
			else if (color == -2)
				break; ///////////////////////////////////////обработка ошибки
			point.x++;
		}
		point.y--;
	}
	ft_lstclear(&(scene.objects), delete_object);
	return (0);
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
	render(screen, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
