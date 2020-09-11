/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:11:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 14:59:33 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

void	*create_sphere(t_point3d p, double r)
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

	oc = minus_vec(s.position, ro);
	if (module_vec(oc) < s.radius)
		return (normalize(minus_vec(s.position, p)));
	return (normalize(minus_vec(p, s.position)));
}

/*
**	sgn(x)
*/

double	sgn(double x)
{
	if (x > 0)
		return (1);
	if (x == 0)
		return (0);
	return (-1);
}

/*
**	Находим пересечения луча с сферой решением квадратного уравнения
**	k3 = q;
*/

double	intersect_sphere(t_ray3d r, void *obj)
{
	t_sphere	s;
	double		k[4];
	double		x[2];
	t_vector3d	oc;

	s = *((t_sphere*)obj);
	oc = minus_vec(r.origin, s.position);
	k[0] = dot_vec(r.direction, r.direction);
	k[1] = 2 * dot_vec(oc, r.direction);
	k[2] = dot_vec(oc, oc) - s.radius * s.radius;
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
