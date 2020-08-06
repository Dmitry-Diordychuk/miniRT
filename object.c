/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/06 16:27:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	delete_content(const char *type, void *content)
{
	if (ft_strcmp("Sphere", type) == 0)
		free((t_sphere*)content);
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
