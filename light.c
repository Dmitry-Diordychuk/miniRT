/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:31:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/10 16:02:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_list	*init_lights()
{
	t_list			*lights;
	t_list			*temp;
	t_object		*object;

	if (!(object = create_object("Light_point",
			create_light_point((t_point3d){0, 0, 0}, 1.0),
						(t_color3d){255, 255, 255})))
		return (NULL);
	if (!(lights = ft_lstnew(object)))
	{
		delete_object(object);
		return (NULL);
	}
	if (!(object = create_object("Light_directional",
			create_light_directional((t_vector3d){0, 0, 1}, 0.0),
						(t_color3d){255, 255, 255})))
	{
		ft_lstclear(&lights, delete_object);
		return (NULL);
	}
	if (!(temp = ft_lstnew(object)))
	{
		delete_object(object);
		ft_lstclear(&lights, delete_object);
		return (NULL);
	}
	ft_lstadd_back(&lights, temp);
	return (lights);
}

void	*create_light_point(t_point3d position, double brightness)
{
	t_light_point	*new_light_point;

	if (!(new_light_point =
			(t_light_point*)malloc(sizeof(t_light_point))))
		return (NULL);
	new_light_point->position = position;
	new_light_point->brightness = brightness;
	return ((void*)new_light_point);
}

void	*create_light_directional(t_vector3d direction,
							double brightness)
{
	t_light_directional	*new_light_directional;

	if (!(new_light_directional =
			(t_light_directional*)malloc(sizeof(t_light_directional))))
		return (NULL);
	new_light_directional->direction = mul_vec_scalar(direction, -1);
	new_light_directional->brightness = brightness;
	return ((void*)new_light_directional);
}

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
