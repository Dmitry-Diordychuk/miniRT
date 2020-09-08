/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:47:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/08 19:43:48 by kdustin          ###   ########.fr       */
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

t_vector3d	calculate_plane_normal(t_vector3d normal, t_vector3d rd)
{
	double	dot;

	dot = dot_vec(normal, rd);
	if (dot > 0)
		return (mul_vec_scalar(normal, -1));
	return (normal);
}

double	*intersect_plane(t_ray3d r, void *obj)
{
	double		*t;
	t_plane		plane;
	double		temp1;
	double		temp2;

	plane = *((t_plane*)obj);

	temp2 = dot_vec(plane.normal, r.direction);
	if (!(t = (double*)malloc(sizeof(double) * 2)))
		return (NULL);
	t[0] = -1;
	t[1] = -1;
	if (temp2 != 0)
	{
		temp1 = dot_vec(plane.normal, minus_vec(plane.q, r.origin));
		t[0] = temp1 / temp2;
	}
	return (t);
}
