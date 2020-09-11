/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:05:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 18:06:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection.h"

int	check_shadow(t_scene scene, t_reflection_data data)
{
	t_ray3d		l;
	t_object	obj;
	double		t;
	t_list		*objects;

	//l.origin = sum_vec(data.point, mul_vec_scalar(data.normal, __FLT));
	l.origin = data.point;
	l.direction = data.light.direction;
	objects = scene.objects;
	while (objects != NULL)
	{
		t = -1;
		obj = *(t_object*)(objects->content);
		if (apply_intersect(l, obj, &t, NULL))
			return (-1);
		if (t > __FLT_EPSILON__ && t < data.max_t)
			return (1);
		objects = objects->next;
	}
	return (0);
}

void	reflect_specular(t_scene scene, t_reflection_data data, t_vector3d *color)
{
	t_vector3d	reflected_vec;
	t_vector3d	light_direction = normalize(data.light.direction);
	double		cos = dot_vec(data.normal, light_direction);
	double		refview;

	if (cos > 0)
	{
		reflected_vec = minus_vec(mul_vec_scalar(data.normal, 2 * dot_vec(data.normal, mul_vec_scalar(light_direction, -1))), mul_vec_scalar(light_direction, -1));
		refview = dot_vec(reflected_vec, scene.camera.ray.direction);
		if (refview < 0)
		 refview = 0;
		*color = sum_vec(*color, mul_vec_scalar(mul_vec_scalar(data.light_color, 0.77), pow(refview, data.specular)));
	}
}

void	reflect_diffusion(t_scene scene, t_reflection_data data, t_vector3d *color)
{
	double	cos = dot_vec(normalize(data.normal), normalize(data.light.direction));
	if (cos > 0)
	{
		*color = sum_vec(*color, mul_vec_scalar(mul_vec_scalar(data.light_color, 0.4), cos));
	}
}

t_color3d	calculate_diffusion_specular(t_scene scene, t_reflection_data data)
{
	t_color3d		point_color;
	t_object		*light;
	t_list			*lights;

	data.max_t = MAXFLOAT;
	lights = scene.lights;
	point_color = mul_vec_scalar(div_vec_scalar(scene.environment_light.color, 255), scene.environment_light.brightness);
	while (lights != NULL)
	{
		light = (t_object*)(lights->content);
		if (ft_strcmp(light->type, "Light_point") == 0)
		{
			data.max_t = 1;
			data.light.direction = minus_vec(((t_light_point*)light
					->container)->position, data.point);
			data.light.brightness = ((t_light_point*)light->container)->brightness;
			data.light_position = ((t_light_point*)light->container)->position;
			data.light_color = mul_vec_scalar(div_vec_scalar(light->color, 255), data.light.brightness);
		}
		point_color = sum_vec(point_color, mul_vec_scalar(data.light_color, 0.25));
		if (check_shadow(scene, data) == 0)
		{
			reflect_diffusion(scene, data, &point_color);
			if (data.specular >= 0)
				reflect_specular(scene, data, &point_color);
		}
		lights = lights->next;
	}
	return ((t_color3d){point_color.x * data.obj_color.x, point_color.y * data.obj_color.y, point_color.z * data.obj_color.z});
}

t_color3d	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj)
{
	t_reflection_data	data;
	t_color3d			reflection_result;
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
	data.obj_color = nearest_obj.color;
	reflection_result = calculate_diffusion_specular(scene, data);
	return (reflection_result);
}
