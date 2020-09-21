/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 14:48:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void		delete_content(const char *type, void *content)
{
	if (ft_strcmp("Sphere", type) == 0)
		free((t_sphere*)content);
	if (ft_strcmp("Plane", type) == 0)
		free((t_plane*)content);
	if (ft_strcmp("Light_point", type) == 0)
		free((t_light_point*)content);
	if (ft_strcmp("Light_directional", type) == 0)
		free((t_light_directional*)content);
	if (ft_strcmp("Square", type) == 0)
		free((t_square*)content);
	if (ft_strcmp("Triangle", type) == 0)
		free((t_triangle*)content);
	if (ft_strcmp("Cylinder", type) == 0)
		free((t_cylinder*)content);
}

void		*create_object(const char *type, void *obj, t_color3d color)
{
	t_object *object;

	if (obj == NULL)
		return (NULL);
	if (!(object = (t_object*)malloc(sizeof(t_object))))
	{
		delete_content(type, obj);
		return (NULL);
	}
	ft_strcpy(object->type, type);
	object->container = obj;
	if (ft_strcmp("Sphere", type) == 0)
		object->intersect_function = intersect_sphere;
	if (ft_strcmp("Plane", type) == 0)
		object->intersect_function = intersect_plane;
	if (ft_strcmp("Square", type) == 0)
		object->intersect_function = intersect_square;
	if (ft_strcmp("Triangle", type) == 0)
		object->intersect_function = intersect_triangle;
	if (ft_strcmp("Cylinder", type) == 0)
		object->intersect_function = intersect_cylinder;
	object->color = color;
	return ((void*)object);
}

void		delete_object(void *item)
{
	t_object	*object;

	object = (t_object*)item;
	delete_content(object->type, object->container);
	free(object);
}

t_vector3d	get_point_normal(t_object o, t_point3d p, t_ray3d r)
{
	if (ft_strcmp(o.type, "Sphere") == 0)
	{
		return (calculate_sphere_normal(*(t_sphere*)(o.container), p,
														r.origin));
	}
	else if (ft_strcmp(o.type, "Plane") == 0)
		return (normal_to_camera(((t_plane*)o.container)->normal, r.direction));
	else if (ft_strcmp(o.type, "Square") == 0)
	{
		return (normal_to_camera(((t_square*)o.container)->normal,
														r.direction));
	}
	else if (ft_strcmp(o.type, "Triangle") == 0)
	{
		return (normal_to_camera(((t_triangle*)o.container)->normal,
														r.direction));
	}
	else if (ft_strcmp(o.type, "Cylinder") == 0)
		return (calculate_cylinder_normal(*(t_cylinder*)o.container, p, r));
	return ((t_vector3d){0, 0, 0});
}
