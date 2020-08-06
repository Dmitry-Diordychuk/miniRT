/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/06 15:13:22 by kdustin          ###   ########.fr       */
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

