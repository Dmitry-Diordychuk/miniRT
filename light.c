/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:31:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/07 16:32:05 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_light_point	*create_light_point(t_point3d position, double brightness)
{
	t_light_point	*new_light_point;

	if (!(new_light_point =
			(t_light_point*)malloc(sizeof(t_light_point))))
		return (NULL);
	new_light_point->position = position;
	new_light_point->brightness = brightness;
	return (new_light_point);
}

t_light_directional	*create_light_directional(t_vector3d direction,
							double brightness)
{
	t_light_directional	*new_light_directional;

	if (!(new_light_directional =
			(t_light_directional*)malloc(sizeof(t_light_directional))))
		return (NULL);
	new_light_directional->direction = direction;
	new_light_directional->brightness = brightness;
	return (new_light_directional);
}
