/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:47:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:41:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

void	*create_plane(t_point3d q, t_vector3d normal)
{
	t_plane *plane;

	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		return (NULL);
	plane->q = q;
	plane->normal = normal;
	return (plane);
}

t_vector3d	normal_to_camera(t_vector3d normal, t_vector3d rd)
{
	double	dot;

	dot = dot_v(normal, rd);
	if (dot > 0)
		return (mul_vs(normal, -1));
	return (normal);
}

double	intersect_plane(t_ray3d r, void **obj)
{
	double		t;
	t_plane		plane;
	double		temp1;
	double		temp2;

	t = -1;
	plane = *((t_plane*)*obj);
	temp2 = dot_v(plane.normal, r.direction);
	if (temp2 != 0)
	{
		temp1 = dot_v(plane.normal, sub_v(plane.q, r.origin));
		t = temp1 / temp2;
	}
	return (t);
}
