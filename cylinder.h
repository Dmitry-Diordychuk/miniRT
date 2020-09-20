/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:17 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 01:49:00 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include <math.h>
# include <stdlib.h>
# include "point.h"
# include "vector.h"
# include "ray.h"
# include "plane.h"

typedef struct	s_cylinder
{
	t_point3d	position;
	t_vector3d	direction;
	double		d;
	double		h;
	int			closest_t;
}				t_cylinder;

void			*create_cylinder(t_point3d p, t_vector3d direction,
									double d, double h);
double			intersect_cylinder(t_ray3d r, void **obj);
t_vector3d		calculate_cylinder_normal(t_cylinder c, t_point3d inter,
											t_ray3d r);

#endif
