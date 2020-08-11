/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:05:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/11 18:55:51 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection.h"

double	calculate_specular_reflection(t_point3d point, t_vector3d norm, t_light_environment enc, t_list *lights, double s, t_vector3d v)
{
	t_object light;
	t_light_directional light_d;
	double	point_brightness;
	double	cosinus;

//	if (s < 0)
//		return (0);
	point_brightness = 0;
	while (lights != NULL)
	{
		light = *(t_object*)lights->content;
		if (ft_strcmp(light.type, "Light_directional") == 0)
			light_d = *(t_light_directional*)light.container;
		else if (ft_strcmp(light.type, "Light_point") == 0)
		{
			light_d.direction = minus_vec(((t_light_point*)light
						.container)->position, point);
			light_d.brightness = ((t_light_point*)light.container)
								->brightness;
		}
		t_vector3d r = minus_vec(mul_vec_scalar(mul_vec_scalar(norm, 2), dot_vec(norm, light_d.direction)), light_d.direction);
		if ((cosinus = (dot_vec(r, v) / (module_vec(r) * module_vec(v) > 0))))
			point_brightness += light_d.brightness * pow(cosinus, s);
		lights = lights->next;
	}
	return (point_brightness);
}

double	calculate_diffusion_specular(t_point3d point, t_vector3d norm, t_scene scene, double s)
{
	double			temp;
	double			point_brightness;
	t_object		*light;
	t_light_directional	light_d;
	t_vector3d		v;
	t_vector3d		r;

	point_brightness = scene.environment_light.brightness;
	while (scene.lights != NULL)
	{
		light = (t_object*)(scene.lights->content);
		if (ft_strcmp(light->type, "Light_directional") == 0)
			light_d = *(t_light_directional*)light->container;
		else if (ft_strcmp(light->type, "Light_point") == 0)
		{
			light_d.direction = minus_vec(((t_light_point*)light
						->container)->position, point);
			light_d.brightness = ((t_light_point*)light->container)
								->brightness;
		}
		if ((temp =
		(light_d.brightness * dot_vec(norm, light_d.direction)) /
		(module_vec(norm) * module_vec(light_d.direction))) > 0)
			point_brightness += temp;
		if (s >= 0)
		{
			v = minus_vec(scene.camera.ray.origin, point);
			r = minus_vec(mul_vec_scalar(mul_vec_scalar(norm, 2), dot_vec(norm, light_d.direction)), light_d.direction);
			if ((temp = dot_vec(r, v)) > 0)
				point_brightness += light_d.brightness * pow(temp / (module_vec(r) * module_vec(v)), s);
		}
		scene.lights = (scene.lights)->next;
	}
	return (point_brightness);
}

double	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj)
{
	t_point3d	point;
	t_vector3d	norm;
	double		reflection_result;
	t_vector3d	v;

	point = ray_param_func(scene.camera.ray, nearest_root);
	norm = unit_vec(minus_vec(point, ((t_sphere*)(nearest_obj.container))->
								position));	//считаем для сферы нужно обобщить
	reflection_result = calculate_diffusion_specular(point, norm, scene, nearest_obj.specular);	
	//v = minus_vec(scene.camera.ray.origin, point);
	//reflection_result += calculate_specular_reflection(point, norm, scene.environment_light, scene.lights, nearest_obj.specular, v);
	return (reflection_result);
}
