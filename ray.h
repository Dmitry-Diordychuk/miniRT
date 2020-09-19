/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:26:06 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:02:53 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct		s_ray3d{
	t_point3d	origin;
	t_vector3d	direction;
}			t_ray3d;

t_point3d	ray_func(t_ray3d r, double t);

#endif

