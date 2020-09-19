/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 20:31:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:41:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

void	*create_triangle(t_point3d v1, t_point3d v2, t_point3d v3)
{
	const t_vector3d v12 = sub_v(v1, v2);
	const t_vector3d v13 = sub_v(v1, v3);
	const t_vector3d normal = normalize(cross_v(v12, v13));
	t_triangle *t;

	if (!(t = (t_triangle*)malloc(sizeof(t_triangle))))
		return (NULL);
	t->v1 = v1;
	t->v2 = v2;
	t->v3 = v3;
	t->normal = normal;
	return ((void*)t);
}

double	triangle_area(t_point3d v1, t_point3d v2, t_point3d v3)
{
	return (fabs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) +
													v3.x * (v1.y - v2.y)) / 2);
}

int	tri_choose_biggest_projection(t_triangle tri)
{
	const double areaxy = triangle_area((t_point3d){tri.v1.x, tri.v1.y, 0},
								(t_point3d){tri.v2.x, tri.v2.y, 0},
								(t_point3d){tri.v3.x, tri.v3.y, 0});
	const double areaxz = triangle_area((t_point3d){tri.v1.x, tri.v1.z, 0},
								(t_point3d){tri.v2.x, tri.v2.z, 0},
								(t_point3d){tri.v3.x, tri.v3.z, 0});
	const double areayz = triangle_area((t_point3d){tri.v1.y, tri.v1.z, 0},
								(t_point3d){tri.v2.y, tri.v2.z, 0},
								(t_point3d){tri.v3.y, tri.v3.z, 0});
	int result;

	result = areaxy >= areaxz ? 1 : 2;
	if (result == 1)
		result = areaxy >= areayz ? 1 : 3;
	if (result == 2)
		result = areaxz >= areayz ? 2 : 3;
	return (result);
}

int	tri_get_quadrant(t_point3d v, t_point3d in_p)
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
	return (pt2.x -((pt2.y - yy) * ((pt1.x - pt2.x) / (pt1.y - pt2.y))));
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
// graphic gems 4
int	tri_angle_test(t_triangle tri, t_point3d in_p)
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

int	is_in_triangle(t_triangle tri, t_point3d in_p)
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
	else
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
		return(t);
	}
	return (-1);
}
