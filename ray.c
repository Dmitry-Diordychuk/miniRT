/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:46:56 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 16:43:47 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

/*
**	origin - vector to the point from wich we cast ray.
**	direction - is vector faced to the point in vector faced to.
**	When we move t steps we get a new point along the ray.
*/

t_point3d	move(t_ray3d r, double t)
{
	return	(sum_vec(r.origin, mul_vec_scalar(r.direction, t)));
}
