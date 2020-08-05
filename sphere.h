/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:09:25 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 03:33:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"

typedef struct		s_sphere {
	t_vector3d	coor;
	double		r;
}			t_sphere;

void			*create_sphere(double x, double y, double z, double r);
double			sgn(double x);
double			*intersect_sphere(t_ray3d r, void *obj);

#endif

