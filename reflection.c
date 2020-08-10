/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:05:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/11 01:10:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection.h"

double	calculate_diffuse_reflection(t_point3d point, t_vector3d norm,
					t_light_environment env, t_list *lights)
{
	double			temp;
	double			point_brightness;
	t_object		*light;
	t_light_directional	light_d;

	point_brightness = env.brightness;
	while (lights != NULL)
	{
		light = (t_object*)lights->content;
		if (ft_strcmp(light->type, "Light_directional") == 0)
			light_d = *(t_light_directional*)light->container;
		else if (ft_strcmp(light->type, "Light_point") == 0)
		{
			light_d.direction = minus_vec(((t_light_point*)light->
						container)->position, point);
			light_d.brightness = ((t_light_point*)light->
							container)->brightness;
		}
		if ((temp =
		(light_d.brightness * dot_vec(norm, light_d.direction)) /
		(module_vec(norm) * module_vec(light_d.direction))) > 0)
			point_brightness += temp;
		lights = lights->next;
	}
	return (point_brightness);
}

double	calculate_reflection(t_scene scene, double nearest_root,
							t_object nearest_obj)
{
	t_point3d	point;
	t_vector3d	norm;
	double		reflection_result;

	point = ray_param_func(scene.camera.ray, nearest_root);
	norm = unit_vec(minus_vec(point, ((t_sphere*)(nearest_obj.container))->
								position));	//считаем для сферы нужно обобщить
	reflection_result = calculate_diffuse_reflection(point, norm,
					scene.environment_light, scene.lights);
	return (reflection_result);
}
