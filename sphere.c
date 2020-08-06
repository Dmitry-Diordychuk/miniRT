/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:11:31 by kdustin           #+#    #+#             */
/*   Updated: 2020/08/05 22:39:22 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

void	*create_sphere(t_point3d p, double r)   			// malloc
{
	t_sphere *s;

	if (!(s = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	s->position = p;
	s->radius = r;
	return ((void*)s);
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
**	Находим пересечения луча с сферой решением квадратного уравнения       malloc
**	k3 = q;
*/

double	*intersect_sphere(t_ray3d r, void *obj)
{
	t_sphere	s;
	double		k[4];
	double		*x;
	t_vector3d	oc;
	
	s = *((t_sphere*)obj);
	oc = minus_vec(r.origin, s.position); 
	k[0] = dot_vec(r.direction, r.direction);
	k[1] = 2 * dot_vec(oc, r.direction);
	k[2] = dot_vec(oc, oc) - s.radius * s.radius;
	k[3] = (-1.0 / 2.0) * (k[1] + sgn(k[1]) * sqrt(k[1] * k[1] - 4.0 * k[0] * k[2]));
	if (!(x = malloc(sizeof(int) * 2)))
	{
		return (NULL);
	}
	x[0] = -1;
	x[1] = -1;
	x[0] = k[3] / k[0];
	x[1] = k[2] / k[3];
	return (x);
}
