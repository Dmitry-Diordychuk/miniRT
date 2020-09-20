/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 01:29:16 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:29:23 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

int		tri_get_quadrant(t_point3d v, t_point3d in_p)
{
	int quadrant;

	if (v.x > in_p.x)
	{
		quadrant = v.y > in_p.y ? 0 : 3;
		return (quadrant);
	}
	quadrant = v.y > in_p.y ? 1 : 2;
	return (quadrant);
}

double	tri_x_intercept(t_point3d pt1, t_point3d pt2, double yy)
{
	return (pt2.x - ((pt2.y - yy) * ((pt1.x - pt2.x) / (pt1.y - pt2.y))));
}

void	tri_adjust_delta(int *delta, t_point3d v1, t_point3d v2, t_point3d p_in)
{
	if (*delta == 3)
		*delta = -1;
	else if (*delta == -3)
		*delta = 1;
	else if (*delta == 2 || *delta == -2)
	{
		if (tri_x_intercept(v1, v2, p_in.y) > p_in.x)
			*delta = -(*delta);
	}
}

int		tri_angle_test(t_triangle tri, t_point3d in_p)
{
	double		angle;
	int			delta;

	angle = 0;
	delta = tri_get_quadrant(tri.v2, in_p) - tri_get_quadrant(tri.v1, in_p);
	tri_adjust_delta(&delta, tri.v1, tri.v2, in_p);
	angle += delta;
	delta = tri_get_quadrant(tri.v3, in_p) - tri_get_quadrant(tri.v2, in_p);
	tri_adjust_delta(&delta, tri.v2, tri.v3, in_p);
	angle += delta;
	delta = tri_get_quadrant(tri.v1, in_p) - tri_get_quadrant(tri.v3, in_p);
	tri_adjust_delta(&delta, tri.v3, tri.v1, in_p);
	angle += delta;
	if (angle == 4 || angle == -4)
		return (1);
	return (0);
}
