/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 01:27:33 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:33:21 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

double	triangle_area(t_point3d v1, t_point3d v2, t_point3d v3)
{
	return (fabs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) +
													v3.x * (v1.y - v2.y)) / 2);
}

int		tri_choose_biggest_projection(t_triangle tri)
{
	int		result;
	double	areaxy;
	double	areaxz;
	double	areayz;

	areaxy = triangle_area((t_point3d){tri.v1.x, tri.v1.y, 0},
								(t_point3d){tri.v2.x, tri.v2.y, 0},
								(t_point3d){tri.v3.x, tri.v3.y, 0});
	areaxz = triangle_area((t_point3d){tri.v1.x, tri.v1.z, 0},
								(t_point3d){tri.v2.x, tri.v2.z, 0},
								(t_point3d){tri.v3.x, tri.v3.z, 0});
	areayz = triangle_area((t_point3d){tri.v1.y, tri.v1.z, 0},
								(t_point3d){tri.v2.y, tri.v2.z, 0},
								(t_point3d){tri.v3.y, tri.v3.z, 0});
	result = areaxy >= areaxz ? 1 : 2;
	if (result == 1)
		result = areaxy >= areayz ? 1 : 3;
	if (result == 2)
		result = areaxz >= areayz ? 2 : 3;
	return (result);
}

int		is_in_triangle(t_triangle tri, t_point3d in_p)
{
	int chosen_plane;

	chosen_plane = tri_choose_biggest_projection(tri);
	if (chosen_plane == 2)
	{
		in_p = (t_point3d){in_p.x, in_p.z, 0};
		tri.v1 = (t_point3d){tri.v1.x, tri.v1.z, 0};
		tri.v2 = (t_point3d){tri.v2.x, tri.v2.z, 0};
		tri.v3 = (t_point3d){tri.v3.x, tri.v3.z, 0};
	}
	else if (chosen_plane == 3)
	{
		in_p = (t_point3d){in_p.y, in_p.z, 0};
		tri.v1 = (t_point3d){tri.v1.y, tri.v1.z, 0};
		tri.v2 = (t_point3d){tri.v2.y, tri.v2.z, 0};
		tri.v3 = (t_point3d){tri.v3.y, tri.v3.z, 0};
	}
	if (tri_angle_test(tri, in_p))
		return (1);
	return (0);
}

double	intersect_triangle(t_ray3d r, void **obj)
{
	double		t;
	t_triangle	triangle;
	t_plane		plane;
	t_point3d	inter_point;

	triangle = *(t_triangle*)(*obj);
	plane = (t_plane){triangle.normal, triangle.v1};
	t = intersect_plane(r, (void*)(&plane));
	if (t >= 0 && is_in_triangle(triangle, ray_func(r, t)))
	{
		return (t);
	}
	return (-1);
}
