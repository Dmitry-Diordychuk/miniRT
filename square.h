/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:21:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/21 01:22:13 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include <stdlib.h>
# include <math.h>
# include "ray.h"
# include "vector.h"
# include "plane.h"
# include "transformation.h"

typedef struct	s_square
{
	t_point3d	center;
	t_vector3d	normal;
	double		side;
	t_point3d	v1;
	t_point3d	v2;
	t_point3d	v3;
	t_point3d	v4;
}				t_square;

void			*create_square(t_point3d center, t_vector3d normal,
													double side);
double			intersect_square(t_ray3d r, void **obj);

int				angle_test(t_square square, t_point3d in_p);

#endif
