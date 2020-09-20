/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 01:53:11 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_vector3d	calculate_cylinder_normal(t_cylinder c, t_point3d inter, t_ray3d r)
{
	if (c.closest_t == 0 || c.closest_t == 1)
	{
		return (normal_to_camera(div_vs(sub_v(sub_v(inter, c.position),
		mul_vs(c.direction, dot_v(sub_v(inter, c.position), c.direction))),
		c.d / 2), r.direction));
	}
	return (normal_to_camera(c.direction, r.direction));
}

void		*create_cylinder(t_point3d p, t_vector3d direction,
								double d, double h)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->position = p;
	cylinder->direction = normalize(direction);
	cylinder->d = d;
	cylinder->h = h;
	return ((void*)cylinder);
}
