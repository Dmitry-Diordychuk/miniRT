/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:26:06 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/01 16:23:32 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "vector.h"

typedef struct		s_ray3d{
	t_point3d	origin;
	t_vector3d	direction;
}			t_ray3d;

t_vector3d		move(t_ray3d r, double t);

#endif
