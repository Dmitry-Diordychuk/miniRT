/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:21:28 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/30 04:49:13 by kdustin          ###   ########.fr       */
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
	square.v4 = (t_point3d){square.center.x + half_side, square.center.y - half_side, square.center.z};
	t_matrix4d m;

	m = transformation_mat((t_matrix3d){1, 0, 0, 0, 1, 0, 0, 0, 1}, square.center);
	m = translate(m, (t_vector3d){0, 0, 1});
	square.center = to_vec3d(mul_mat4d_vec4d(m, to_vec4d(square.center)));
	square.v1 = to_vec3d(mul_mat4d_vec4d(m, to_vec4d(square.v1)));
	square.v2 = to_vec3d(mul_mat4d_vec4d(m, to_vec4d(square.v2)));
	square.v3 = to_vec3d(mul_mat4d_vec4d(m, to_vec4d(square.v3)));
	square.v4 = to_vec3d(mul_mat4d_vec4d(m, to_vec4d(square.v4)));
	plane = (t_plane){square.normal, square.center};
	if (!(t = intersect_plane(r, (void*)(&plane))))
		return (NULL);
	if (t[0] >= 0)
	{
		inter_point = ray_param_func(r, t[0]);
		vlen = minus_vec(square.v2, square.v1);
		plen = minus_vec(inter_point, square.v1);
		t[1] = dot_vec(plen, vlen) / dot_vec(vlen, vlen);
	}
	else
	{
		t[0] = -1;
		t[1] = -1;
	}
	if (t[1] >= 0 && t[1] <= 1)
	{
		vlen = minus_vec(square.v3, square.v2);
		plen = minus_vec(inter_point, square.v2);
		t[1] = dot_vec(plen, vlen) / dot_vec(vlen, vlen);
	}
	if (t[1] >= 0 && t[1] <= 1)
	{
		t[1] = -1;
		return (t);
	}
	t[0] = -1;
	t[1] = -1;
	return (t);
}
