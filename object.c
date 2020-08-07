/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 17:41:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void		delete_content(const char *type, void *content)
{
	if (ft_strcmp("Sphere", type) == 0)
		free((t_sphere*)content);
	if (ft_strcmp("Light_point", type) == 0)
		free((t_light_point*)content);
	if (ft_strcmp("Light_directional", type) == 0)
		free((t_light_directional*)content);
}

t_object	*create_object(const char *type, void *obj, t_color3d color)
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
	object->color = color;
	return (object);
}

void		delete_object(void *item)
{
	t_object	*object;

	object = (t_object*)item;
	delete_content(object->type, object->container);
	free(object);
}

t_list		*init_objects(void)
{
	t_object	*obj;
	t_list		*temp;
	t_list		*objects;

	if (!(obj = create_object("Sphere",
	create_sphere((t_point3d){-10, 10, 95}, 1), (t_color3d){0, 255, 0})))
		return (NULL);
	if (!(objects = ft_lstnew((void*)obj)))
	{
		delete_object((void*)obj);
		return (NULL);
	}
	if (!(obj = create_object("Sphere",
	create_sphere((t_point3d){-10, 10, 100}, 5), (t_color3d){255, 0, 0})))
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

