/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:21:28 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/31 02:22:57 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

void	*create_square(t_point3d center, t_vector3d normal, double side)
{
	t_square *s;

	if (!(s = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	s->center = center;
	s->normal = center;
	s->side = side;
	return ((void*)s);
}

int	is_intersect_segment(t_point3d v1, t_point3d v2, t_point3d in_p)
{
	double		t;
	t_vector3d	vec1;
	t_vector3d	vec2;
	t_vector3d	vec3;

	v1.z = 0;
	v2.z = 0;
	vec1 = minus_vec(in_p, v1);
	vec2 = minus_vec(v2, v1);
	vec3 = (t_vector3d){-1, 0, 0};
	t = module_vec(cross_vec(vec2, vec1)) / dot_vec(vec2, vec3);
	if (t >= 0)
	{
		t = dot_vec(vec1, vec3) / dot_vec(vec2, vec3);
		if (t >= 0 && t <= 1)
			return (1);
		return (0);
	}
	return (0);
}

int	is_in_square(t_square square, t_point3d in_p)
{
	double x_max;
	double x_min;
	double y_max;
	double y_min;

	x_max = square.v1.x;
	x_min = square.v1.x;
	y_max = square.v1.y;
	y_min = square.v1.y;
	x_max < square.v2.x ? x_max = square.v2.x : 0;
	x_max < square.v3.x ? x_max = square.v3.x : 0;
	x_max < square.v4.x ? x_max = square.v4.x : 0;
	x_min > square.v2.x ? x_min = square.v2.x : 0;
	x_min > square.v3.x ? x_min = square.v3.x : 0;
	x_min > square.v4.x ? x_min = square.v4.x : 0;
	y_min > square.v2.y ? y_min = square.v2.y : 0;
	y_min > square.v3.y ? y_min = square.v3.y : 0;
	y_min > square.v4.y ? y_min = square.v4.y : 0;
	y_max < square.v2.y ? y_max = square.v2.y : 0;
	y_max < square.v3.y ? y_max = square.v3.y : 0;
	y_max < square.v4.y ? y_max = square.v4.y : 0;
	if (in_p.x < x_min || in_p.x > x_max || in_p.y < y_min || in_p.y > y_max)
		return (0);
	return (1);
}

double	*intersect_square(t_ray3d r, void *obj)
{
	double		*t;
	t_square	square;
	t_plane		plane;
	double		half_side;
	t_vector3d	vlen;
	t_vector3d	plen;
	t_point3d	inter_point;

	square = *(t_square*)(obj);
	half_side = square.side / 2;
	square.v1 = (t_point3d){square.center.x - half_side, square.center.y + half_side, square.center.z};
	square.v2 = (t_point3d){square.center.x - half_side, square.center.y - half_side, square.center.z};
	square.v3 = (t_point3d){square.center.x + half_side, square.center.y - half_side, square.center.z};
	square.v4 = (t_point3d){square.center.x + half_side, square.center.y + half_side, square.center.z};
	t_matrix4d m;

	m = get_i_mat4d();
	m = rotate_local(m, 3.14 / 2, (t_vector3d){0.0, 0.0, 0.0}, square.center);
	square.normal = v4_to_v3(mul_mat4d_vec4d(m, v3_to_v4(square.normal)));
	square.center = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(square.center)));
	square.v1 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(square.v1)));
	square.v2 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(square.v2)));
	square.v3 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(square.v3)));
	square.v4 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(square.v4)));
	plane = (t_plane){square.normal, square.center};
	if (!(t = intersect_plane(r, (void*)(&plane))))
		return (NULL);
	if (t[0] >= 0 && is_in_square(square, ray_param_func(r, t[0])))
	{
		return(t);
	}
	t[0] = -1;
	t[1] = -1;
	return (t);
}
