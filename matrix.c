/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:53:52 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 02:08:39 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double		det_mat(t_matrix3d m)
{
	return (m.m00 * (m.m11 * m.m22 - m.m12 * m.m21)
			- m.m01 * (m.m10 * m.m22 - m.m12 * m.m20)
				+ m.m02 * (m.m10 * m.m21 - m.m11 * m.m20));
}

t_matrix3d	invert_mat3d(t_matrix3d m)
{
	double		det;

	det = det_mat(m);
	m.m00 = (m.m11 * m.m22 - m.m12 * m.m21) / det;
	m.m01 = (m.m02 * m.m21 - m.m01 * m.m22) / det;
	m.m02 = (m.m01 * m.m12 - m.m02 * m.m11) / det;
	m.m10 = (m.m12 * m.m20 - m.m10 * m.m22) / det;
	m.m11 = (m.m00 * m.m22 - m.m02 * m.m20) / det;
	m.m12 = (m.m02 * m.m10 - m.m00 * m.m12) / det;
	m.m20 = (m.m10 * m.m21 - m.m11 * m.m20) / det;
	m.m21 = (m.m01 * m.m20 - m.m00 * m.m21) / det;
	m.m22 = (m.m00 * m.m11 - m.m01 * m.m10) / det;
	return (m);
}

t_matrix4d	mul_mat4d(t_matrix4d a, t_matrix4d b)
{
	t_matrix4d m;

	m.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30;
	m.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31;
	m.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32;
	m.m03 = a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33;
	m.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30;
	m.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	m.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	m.m13 = a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
	m.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30;
	m.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	m.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	m.m23 = a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
	m.m30 = a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30;
	m.m31 = a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	m.m32 = a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	m.m33 = a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
	return (m);
}

t_matrix4d	get_i_mat4d(void)
{
	t_matrix4d m;

	m.m00 = 1;
	m.m01 = 0;
	m.m02 = 0;
	m.m03 = 0;
	m.m10 = 0;
	m.m11 = 1;
	m.m12 = 0;
	m.m13 = 0;
	m.m20 = 0;
	m.m21 = 0;
	m.m22 = 1;
	m.m23 = 0;
	m.m30 = 0;
	m.m31 = 0;
	m.m32 = 0;
	m.m33 = 1;
	return (m);
}

t_vector4d	mul_mat4d_vec4d(t_matrix4d m, t_vector4d v)
{
	t_vector4d res;

	res.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w;
	res.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w;
	res.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w;
	res.w = m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w;
	return (res);
}
