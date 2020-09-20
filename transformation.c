/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:21:44 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:09:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_matrix4d	translate(t_matrix4d m, t_vector3d v)
{
	t_matrix4d res;

	res.m00 = 1;
	res.m01 = 0;
	res.m02 = 0;
	res.m03 = v.x;
	res.m10 = 0;
	res.m11 = 1;
	res.m12 = 0;
	res.m13 = v.y;
	res.m20 = 0;
	res.m21 = 0;
	res.m22 = 1;
	res.m23 = v.z;
	res.m30 = 0;
	res.m31 = 0;
	res.m32 = 0;
	res.m33 = 1;
	res = mul_mat4d(res, m);
	return (res);
}

t_matrix4d	rotate(t_matrix4d m, double a, t_vector3d v)
{
	t_matrix4d		res;
	const double	c = cos(a);
	const double	one_sub_c = 1 - cos(a);
	const double	s = sin(a);

	res.m00 = c + pow(v.x, 2) * (one_sub_c);
	res.m01 = v.x * v.y * (one_sub_c) - s * v.z;
	res.m02 = v.x * v.z * (one_sub_c) + v.y * s;
	res.m03 = 0;
	res.m10 = v.x * v.y * (one_sub_c) + v.z * s;
	res.m11 = c + pow(v.y, 2) * (one_sub_c);
	res.m12 = v.y * v.z * (one_sub_c) - v.x * s;
	res.m13 = 0;
	res.m20 = v.x * v.z * (one_sub_c) - v.y * s;
	res.m21 = v.y * v.z * (one_sub_c) + v.x * s;
	res.m22 = c + pow(v.z, 2) * (one_sub_c);
	res.m23 = 0;
	res.m30 = 0;
	res.m31 = 0;
	res.m32 = 0;
	res.m33 = 1;
	res = mul_mat4d(res, m);
	return (res);
}

t_matrix4d	rotate_local(t_matrix4d m, double a, t_vector3d v, t_vector3d obj)
{
	t_vector3d temp;

	if (a == 0)
		return (m);
	temp.x = obj.x;
	temp.y = obj.y;
	temp.z = obj.z;
	m = translate(m, (t_vector3d){-obj.x, -obj.y, -obj.z});
	m = rotate(m, a, v);
	m = translate(m, temp);
	return (m);
}

t_vector3d	apply_matrix(t_matrix4d m, t_vector3d target)
{
	return (v4_to_v3(mul_mat4d_vec4d(m, v3_to_v4(target))));
}
