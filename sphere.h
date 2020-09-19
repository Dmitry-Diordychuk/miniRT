/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:09:25 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 22:40:10 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"

typedef struct		s_sphere
{
	t_vector3d	position;
	double		radius;
}			t_sphere;

void			*create_sphere(t_point3d p, double r);
double			sgn(double x);
double			intersect_sphere(t_ray3d r, void **obj);
t_vector3d		calculate_sphere_normal(t_sphere s, t_point3d p, t_point3d ro);

#endif

