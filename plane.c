/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:47:42 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/23 23:04:19 by kdustin          ###   ########.fr       */
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

double	*intersect_plane(t_ray3d r, void *obj)
{
	double		*t;
	t_plane		plane;
	double		temp1;
	double		temp2;

	plane = *((t_plane*)obj);
	temp1 = dot_vec(plane.normal, minus_vec(plane.q, r.origin));
	temp2 = dot_vec(plane.normal, r.direction);
	if (!(t = (double*)malloc(sizeof(double) * 2)))
		return (NULL);
	t[0] = -1;
	t[1] = -1;
	if (temp2 != 0)
	{
		t[0] = temp1 / temp2;
	}
	return (t);
}
