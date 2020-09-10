/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:31:50 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/10 23:38:03 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_list	*init_lights()
{
	t_list			*lights;
	t_list			*temp;
	t_object		*object;

	if (!(object = create_object("Light_point",
			create_light_point((t_point3d){1, 1, 0}, 0.8),
						(t_color3d){255, 0, 0}, 0)))
		return (NULL);
	if (!(lights = ft_lstnew(object)))
	{
		delete_object(object);
		return (NULL);
	}

	if (!(object = create_object("Light_point",
			create_light_directional((t_point3d){-1, 1, 0}, 0.5),
						(t_color3d){0, 255, 0}, 0)))
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
//
//	if (!(object = create_object("Light_point",
//			create_light_directional((t_point3d){-4, 4, 0}, 0.5),
//						(t_color3d){255, 255, 255}, 0)))
//	{
//		ft_lstclear(&lights, delete_object);
//		return (NULL);
//	}
//	if (!(temp = ft_lstnew(object)))
//	{
//		delete_object(object);
//		ft_lstclear(&lights, delete_object);
//		return (NULL);
//	}
//	ft_lstadd_back(&lights, temp);

//	if (!(object = create_object("Light_directional",
//			create_light_directional((t_vector3d){1, 4, 4}, 0.2),
//						(t_color3d){255, 255, 255}, 0)))
//	{
//		ft_lstclear(&lights, delete_object);
//		return (NULL);
//	}
//	if (!(temp = ft_lstnew(object)))
//	{
//		delete_object(object);
//		ft_lstclear(&lights, delete_object);
//		return (NULL);
//	}
//	ft_lstadd_back(&lights, temp);
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
	new_light_directional->direction = direction;
	new_light_directional->brightness = brightness;
	return ((void*)new_light_directional);
}
