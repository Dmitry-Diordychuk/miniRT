/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:31:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 16:47:05 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

void	*create_light_point(t_point3d position, double brightness,
							t_color3d color)
{
	t_light_point	*new_light_point;

	if (!(new_light_point = (t_light_point*)malloc(sizeof(t_light_point))))
		return (NULL);
	new_light_point->position = position;
	new_light_point->brightness = brightness;
	new_light_point->color = color;
	return ((void*)new_light_point);
}

void	delete_light(void *obj)
{
	t_light_point	*light;

	light = (t_light_point*)obj;
	free(light);
}
