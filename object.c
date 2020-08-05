/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 23:36:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/04 23:37:08 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_object	create_object(const char *name, void *obj, t_color3d color)
{
	if (ft_strcmp(name, "Sphere") == 0)
		return ((t_object){ft_strdup(name), obj, intersect_sphere, color});
}

