/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:09:25 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/04 17:36:00 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <stdlib.h>
# include "ray.h"
# include "color.h"
# include "math.h"

typedef struct		s_sphere {
	t_vector3d	coor;
	double		r;
}			t_sphere;

double			sgn(double x);
double			*intersect_sphere(t_ray3d r, void *obj);

#endif

