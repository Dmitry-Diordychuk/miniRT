/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:33:47 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/04 23:04:47 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector3d	sum_vec(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3d	minus_vec(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

double		dot_vec(t_vector3d a, t_vector3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vector3d	mul_vec_scalar(t_vector3d a, double n)
{
	return ((t_vector3d){a.x * n, a.y * n, a.z * n});
}

t_vector3d	div_vec_scalar(t_vector3d a, double n)
{
	return ((t_vector3d){a.x / n, a.y / n, a.z / n});
}

double		module_vec(t_vector3d a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector3d	cross_vec(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){	a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
							});
}

t_vector3d	normalize(t_vector3d a)
{
	return (div_vec_scalar(a, module_vec(a)));
}

t_vector4d	sum_vec4d(t_vector4d a, t_vector4d b)
{
	return ((t_vector4d){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

t_vector4d	sub_vec4d(t_vector4d a, t_vector4d b)
{
	return ((t_vector4d){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}

double		dot_vec4d(t_vector4d a, t_vector4d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

t_vector4d	mul_vec4d_scalar(t_vector4d a, double n)
{
	return ((t_vector4d){a.x * n, a.y * n, a.z * n, a.w * n});
}

t_vector4d	div_vec4d_scalar(t_vector4d a, double n)
{
	return ((t_vector4d){a.x / n, a.y / n, a.z / n, a.w / n});
}

double		module_vec4d(t_vector4d a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_vector4d	unit_vec4d(t_vector4d a)
{
	return (div_vec4d_scalar(a, module_vec4d(a)));
}

t_vector4d	v3_to_v4(t_vector3d v)
{
	return ((t_vector4d){v.x, v.y, v.z, 0});
}

t_vector3d	v4_to_v3(t_vector4d v)
{
	return ((t_vector3d){v.x, v.y, v.z});
}
