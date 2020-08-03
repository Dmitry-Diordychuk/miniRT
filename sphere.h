/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:09:25 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/03 20:18:45 by kdustin          ###   ########.fr       */
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
	t_color3d	color;
}			t_sphere;

double			sgn(double x);
double			*get_sphere_crossing(t_ray3d r, t_sphere s);

#endif

