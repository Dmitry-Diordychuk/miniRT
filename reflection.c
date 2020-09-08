/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:05:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/09 01:26:06 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection.h"

int	check_shadow(t_scene scene, t_reflection_data data)
{
	t_ray3d		l;
	t_object	obj;
	double		t;
	t_list		*objects;

	//l.origin = sum_vec(data.point, mul_vec_scalar(data.normal, 0.00001));
	l.origin = data.point;
	l.direction = data.light.direction;
	objects = scene.objects;
	while (objects != NULL)
	{
		t = -1;
		obj = *(t_object*)(objects->content);
		if (apply_intersect(l, obj, &t, NULL))
			return (-1);
		if (t > (0.0000000000001) && t < data.max_t)
			return (1);
		objects = objects->next;
	}
	return (0);
}

double	reflect_specular(t_scene scene, t_reflection_data data)
{
	double		temp;
	t_vector3d	v;
	t_vector3d	r;

	v = minus_vec(scene.camera.ray.origin, data.point);
	r = minus_vec(mul_vec_scalar(mul_vec_scalar(data.normal, 2),
	dot_vec(data.normal, data.light.direction)), data.light.direction);
	if ((temp = dot_vec(r, v)) > 0)
		return (data.light.brightness *
		pow(temp / (module_vec(r) * module_vec(v)), data.specular));
	return (0);
}

double	reflect_diffusion(t_scene scene, t_reflection_data data)
{
	double	result;
	double	temp;

	result = 0;
	if ((temp =
	(data.light.brightness * dot_vec(data.normal, data.light.direction)) /
	(module_vec(data.normal) * module_vec(data.light.direction))) > 0)
		result += temp;
	return (result);
}

double	calculate_diffusion_specular(t_scene scene, t_reflection_data data)
{
	double			point_brightness;
	t_object		*light;
	t_list			*lights;

	data.max_t = MAXFLOAT;
	lights = scene.lights;
	point_brightness = scene.environment_light.brightness;
	while (lights != NULL)
	{
		light = (t_object*)(lights->content);
		if (ft_strcmp(light->type, "Light_directional") == 0)
			data.light = *(t_light_directional*)light->container;
		else if (ft_strcmp(light->type, "Light_point") == 0)
		{
			data.max_t = 1;
			data.light.direction = minus_vec(((t_light_point*)light
					->container)->position, data.point);
			data.light.brightness = ((t_light_point*)light->
					container)->brightness;
		}
		if (check_shadow(scene, data) == 0)
		{
			point_brightness += reflect_diffusion(scene, data);
			if (data.specular >= 0)
				point_brightness += reflect_specular(scene, data);
		}
		lights = lights->next;
	}
	return (point_brightness);
}

double	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj)
{
	t_reflection_data	data;
	double				reflection_result;
	t_point3d			int_point;

	data.point = ray_param_func(scene.camera.ray, nearest_root);
	if (ft_strcmp(nearest_obj.type, "Sphere") == 0)
		data.normal = calculate_sphere_normal(*(t_sphere*)(nearest_obj.container), data.point, scene.camera.ray.origin);
	else if (ft_strcmp(nearest_obj.type, "Plane") == 0)
		data.normal = calculate_plane_normal(((t_plane*)nearest_obj.container)->normal, scene.camera.ray.direction);
	else if (ft_strcmp(nearest_obj.type, "Square") == 0)
		data.normal = calculate_plane_normal(((t_square*)nearest_obj.container)->normal, scene.camera.ray.direction);
	else if (ft_strcmp(nearest_obj.type, "Triangle") == 0)
		data.normal = calculate_plane_normal(((t_triangle*)nearest_obj.container)->normal, scene.camera.ray.direction);
	else if (ft_strcmp(nearest_obj.type, "Cylinder") == 0)
		data.normal = calculate_cylinder_normal(*(t_cylinder*)nearest_obj.container, scene.camera.ray.direction);
	data.specular = nearest_obj.specular;
	reflection_result = calculate_diffusion_specular(scene, data);
	return (reflection_result);
}
