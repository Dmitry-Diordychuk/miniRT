/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 17:47:40 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/20 18:23:19 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <stdlib.h>
# include "ray.h"

typedef struct	s_plane
{
	t_vector3d	normal;
	t_point3d	q;
}				t_plane;

void			*create_plane(t_point3d q, t_vector3d normal);
double			intersect_plane(t_ray3d r, void **obj);
t_vector3d		normal_to_camera(t_vector3d normal, t_vector3d rd);

#endif
