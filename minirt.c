/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:31:53 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/12 02:34:50 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**	trace_ray function
**	if find ray go trought object than we get it's color.
**	if we find two object in one spote we get color of neares.
*/

int	trace_ray(t_scene scene)//t_ray3d r, t_list *objects, t_light_environment env, t_list *lights)
{
	t_object	obj;
	t_object	nearest_obj;
	double		nearest_root;
	t_list		*objects;

	objects = scene.objects;
	nearest_root = -1;
	while (objects != NULL)
	{
		obj = *(t_object*)(objects->content);
		if (apply_intersect(scene.camera.ray, obj, &nearest_root, &nearest_obj) < 0)
			return (-2);
		objects = objects->next;
	}
	if (nearest_root != -1)
	{
		return (color3d_to_trgb(calculate_reflection(scene, nearest_root, nearest_obj)));
	}
	return (-1);
}

int	render_return(int ret, t_list *objects)
{
	ft_lstclear(&objects, delete_object);
	return (ret);
}

void	*ft_lstget(t_list *list, int number)
{
	int	i;

	i = 0;
	while (i < number && list != NULL)
	{
		list = list->next;
		i++;
	}
	if (list != NULL)
		return (list->content);
	return (NULL);
}
                                                                                //  разобратся с t_data, разобратся с цветами  initobj initlight malloc
int	render(t_screen screen, t_data *img, int camera_number)
{
	const t_canvas	canvas = create_canvas(screen);
	t_scene			scene;
	t_point2d		point;
	int				color;
	t_list			*lights;
	// Камера вниз не показывает
	scene = init_scene(init_objects(), init_lights(), init_cameras(), (t_light_environment){0.2, (t_color3d){255, 255, 255}});
	scene.camera = *(t_camera*)ft_lstget(scene.cameras, abs(camera_number % 4)); // 4 заменить на кол-во камер
	point.y = canvas.top_border + 1;
	while (--point.y > canvas.bottom_border)
	{
		point.x = canvas.left_border - 1;
		while (++point.x < canvas.right_border)
		{
			draw_background(img, point, screen, canvas);
			scene.camera.ray.direction = normalize(apply_matrix(scene.camera.rotation_matrix, canvas_to_viewport(point, canvas, scene.camera.viewport)));
			if ((color = trace_ray(scene)) >= 0)
			{
				draw_pixel(img, canvas_to_screen(point, screen), color);
			}
			else if (color == -2)
				return (render_return(-2, scene.objects));
		}
	}
	return (render_return(0, scene.objects));
}

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		data;
	t_screen	screen;

}				t_vars;

int	keys_handler(int keycode, t_vars *vars)
{
	static int	camera_number;

	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == 123)
	{
		camera_number--;
		render(vars->screen, &vars->data, camera_number);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	if (keycode == 124)
	{
		camera_number++;
		render(vars->screen, &vars->data, camera_number);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.screen = (t_screen){800, 600};
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.screen.width, vars.screen.height, "MLX!");
	vars.data.img = mlx_new_image(vars.mlx, vars.screen.width, vars.screen.height);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel,
						&vars.data.line_length, &vars.data.endian);
	if (render(vars.screen, &vars.data, 0) < 0)
		return (-1);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, keys_handler, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

