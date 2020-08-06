/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/06 15:45:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	*create_object(const char *type, void *obj, t_color3d color)
{
	t_object *object;
	
	if (!(object = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	ft_strcpy(object->type, type);
	object->container = obj;
	if (ft_strcmp("Sphere", type) == 0)
		object->intersect_function = intersect_sphere;
	object->color = color;	
	return (object);
}

void		delete_object(void *item)
{
	t_object	*object = (t_object*)item;
	if (ft_strcmp("Sphere", object->type) == 0)
		free((t_sphere*)object->container);
	free(object);
}
