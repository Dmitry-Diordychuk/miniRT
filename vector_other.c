/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:51:17 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 14:52:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3d	normalize(t_vector3d a)
{
	return (div_vs(a, module_v(a)));
}

t_vector4d	v3_to_v4(t_vector3d v)
{
	return ((t_vector4d){v.x, v.y, v.z, 0});
}

t_vector3d	v4_to_v3(t_vector4d v)
{
	return ((t_vector3d){v.x, v.y, v.z});
}

t_vector3d	mul_vs(t_vector3d a, double n)
{
	return ((t_vector3d){a.x * n, a.y * n, a.z * n});
}

t_vector3d	div_vs(t_vector3d a, double n)
{
	return ((t_vector3d){a.x / n, a.y / n, a.z / n});
}
