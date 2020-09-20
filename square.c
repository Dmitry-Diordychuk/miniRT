/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:21:28 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:04:01 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

t_square	calculate_vertices(t_square s)
{
	double				half_side;
	t_matrix4d			m;

	half_side = s.side / 2;
	s.v1 =
		(t_point3d){s.center.x - half_side, s.center.y + half_side, s.center.z};
	s.v2 =
		(t_point3d){s.center.x + half_side, s.center.y + half_side, s.center.z};
	s.v3 =
		(t_point3d){s.center.x + half_side, s.center.y - half_side, s.center.z};
	s.v4 =
		(t_point3d){s.center.x - half_side, s.center.y - half_side, s.center.z};
	if (s.normal.x == 0 && s.normal.y == 0 &&
							(s.normal.z == 1 || s.normal.z == -1))
		return (s);
	m = rotate_local(get_i_mat4d(), acos(dot_v((t_vector3d){0, 0, -1},
	s.normal)), normalize(cross_v((t_vector3d){0, 0, -1}, s.normal)), s.center);
	s.normal = (t_vector3d){0, 0, -1};
	s.normal = v4_to_v3(mul_mat4d_vec4d(m, v3_to_v4(s.normal)));
	s.center = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s.center)));
	s.v1 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s.v1)));
	s.v2 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s.v2)));
	s.v3 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s.v3)));
	s.v4 = p4_to_p3(mul_mat4d_vec4d(m, p3_to_p4(s.v4)));
	return (s);
}

void		*create_square(t_point3d center, t_vector3d normal, double side)
{
	t_square	*s;
	t_square	vert;

	if (!(s = (t_square*)malloc(sizeof(t_square))))
		return (NULL);
	s->center = center;
	s->normal = normalize(normal);
	s->side = side;
	vert = calculate_vertices(*s);
	s->v1 = vert.v1;
	s->v2 = vert.v2;
	s->v3 = vert.v3;
	s->v4 = vert.v4;
	return ((void*)s);
}
