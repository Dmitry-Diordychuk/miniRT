/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 03:14:09 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/08 03:14:26 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point3d	ray_param_func(t_ray3d r, double t)
{
	return ((t_point3d)sum_vec(r.origin, mul_vec_scalar(r.direction, t)));
}
