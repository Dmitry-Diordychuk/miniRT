/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:11:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/22 21:02:58 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

void		*create_sphere(t_point3d p, double r)
{
	t_sphere *s;

	if (!(s = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	s->position = p;
	s->radius = r;
	return ((void*)s);
}

t_vector3d	calculate_sphere_normal(t_sphere s, t_point3d p, t_point3d ro)
{
	t_vector3d	oc;

	oc = sub_v(s.position, ro);
	if (module_v(oc) < s.radius)
		return (normalize(sub_v(s.position, p)));
	return (normalize(sub_v(p, s.position)));
}

/*
**	sgn(x)
*/

double		sgn(double x)
{
	if (x > 0)
		return (1);
	if (x == 0)
		return (0);
	return (-1);
}

double		intersect_sphere(t_ray3d r, void **obj)
{
	t_sphere	s;
	double		k[4];
	double		x[2];
	t_vector3d	oc;

	s = *((t_sphere*)*obj);
	oc = sub_v(r.origin, s.position);
	k[0] = dot_v(r.direction, r.direction);
	k[1] = 2 * dot_v(oc, r.direction);
	k[2] = dot_v(oc, oc) - s.radius * s.radius;
	k[3] = pow(k[1], 2) - 4 * k[0] * k[2];
	if (k[3] < 0)
		return (-1);
	k[3] = sqrt(k[3]);
	x[0] = (-k[1] + k[3]) / (2 * k[0]);
	x[1] = (-k[1] - k[3]) / (2 * k[0]);
	if (x[0] < 0 && x[1] < 0)
		return (-1);
	if (x[0] < 0)
		return (x[1]);
	if (x[1] < 0)
		return (x[0]);
	if (x[0] < x[1])
		return (x[0]);
	return (x[1]);
}
