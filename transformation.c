/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:21:44 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/30 04:46:25 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_matrix4d	transformation_mat(t_matrix3d m, t_vector3d t)
{
	t_matrix4d res;

	res.m00 = m.m00;
	res.m01 = m.m01;
	res.m02 = m.m02;
	res.m10 = m.m10;
	res.m11 = m.m11;
	res.m12 = m.m12;
	res.m20 = m.m20;
	res.m21 = m.m21;
	res.m22 = m.m22;
	res.m03 = t.x;
	res.m13 = t.y;
	res.m23 = t.z;
	res.m30 = 0;
	res.m31 = 0;
	res.m32 = 0;
	res.m33 = 1;
	return (res);
}

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
	if (is_empty(m) == 0)
		res = mul_mat4d(res, m);
	return (res);
}

t_matrix4d	rotate(t_matrix4d m, double a, t_vector3d v)
{
	t_matrix4d res;

	res.m00 = cos(a) + pow(v.x, 2) * (1 - cos(a));
	res.m01 = v.x * v.y * (1 - cos(a)) - v.z * sin(a);
	res.m02 = v.x * v.z * (1 - cos(a)) + v.y * sin(a);
	res.m03 = 0;
	res.m10 = v.y * v.x * (1 - cos(a)) + v.z * sin(a);
	res.m11 = cos(a) + pow(v.y, 2) * (1 - cos(a));
	res.m12 = v.y * v.z * (1 - cos(a)) - v.x * sin(a);
	res.m13 = 0;
	res.m20 = v.z * v.x * (1 - cos(a)) - v.y * sin(a);
	res.m21 = v.z * v.y * (1 - cos(a)) + v.x * sin(a);
	res.m22 = cos(a) + pow(v.z, 2) * (1 - cos(a));
	res.m23 = 0;
	res.m30 = 0;
	res.m31 = 0;
	res.m32 = 0;
	res.m33 = 1;
	if(is_empty(m) == 0)
		res = mul_mat4d(res, m);
	return (res);
}

t_matrix4d	scale(t_matrix4d m, t_vector3d v)
{
	t_matrix4d res;

	res.m00 = v.x;
	res.m01 = 0;
	res.m02 = 0;
	res.m03 = 0;
	res.m10 = 0;
	res.m11 = v.y;
	res.m12 = 0;
	res.m13 = 0;
	res.m20 = 0;
	res.m21 = 0;
	res.m22 = v.z;
	res.m23 = 0;
	res.m30 = 0;
	res.m31 = 0;
	res.m32 = 0;
	res.m33 = 1;
	if (is_empty(m) == 0)
		res = mul_mat4d(res, m);
	return (res);
}

int			is_empty(t_matrix4d m)
{
	if (
	m.m00 == 0 &&
	m.m01 == 0 &&
	m.m02 == 0 &&
	m.m03 == 0 &&
	m.m10 == 0 &&
	m.m11 == 0 &&
	m.m12 == 0 &&
	m.m13 == 0 &&
	m.m20 == 0 &&
	m.m21 == 0 &&
	m.m22 == 0 &&
	m.m23 == 0 &&
	m.m30 == 0 &&
	m.m31 == 0 &&
	m.m32 == 0 &&
	m.m33 == 0
	)
		return (1);
	return (0);
}
