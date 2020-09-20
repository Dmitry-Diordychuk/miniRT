/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:33:47 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 14:52:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vector3d	sum_v(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3d	sub_v(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

double		dot_v(t_vector3d a, t_vector3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vector3d	cross_v(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){	a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
							});
}

double		module_v(t_vector3d a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
