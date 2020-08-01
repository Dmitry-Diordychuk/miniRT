/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:33:47 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 14:54:43 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector3d 	sum_vec(t_vector3d a, t_vector3d b)
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

t_vector3d 	mul_vec_scalar(t_vector3d a, double n)
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

t_vector3d cross_vec(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

t_vector3d unit_vec(t_vector3d a)
{
	return (div_vec_scalar(a, module_vec(a)));
}
