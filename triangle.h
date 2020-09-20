/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 20:31:59 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:29:37 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include <math.h>
# include <stdlib.h>
# include "point.h"
# include "ray.h"
# include "plane.h"

typedef struct	s_triangle
{
	t_point3d	v1;
	t_point3d	v2;
	t_point3d	v3;
	t_vector3d	normal;
}				t_triangle;

void			*create_triangle(t_point3d v1, t_point3d v2, t_point3d v3);

double			intersect_triangle(t_ray3d r, void **obj);

int				tri_angle_test(t_triangle tri, t_point3d in_p);

#endif
