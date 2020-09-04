/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/03 18:22:49 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_vector3d	calculate_cylinder_normal(t_cylinder cylinder, t_point3d int_point)
{
	const t_vector3d	vec_h = minus_vec(int_point, cylinder.position);

	return (div_vec_scalar(minus_vec(vec_h, mul_vec_scalar(cylinder.center_line,
			dot_vec(vec_h, cylinder.center_line))), (cylinder.diameter / 2)));
}

void	*create_cylinder(t_point3d position, t_vector3d center_line, double diameter, double height)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->position = position;
	cylinder->center_line = center_line;
	cylinder->diameter = diameter;
	cylinder->height = height;
	return ((void*)cylinder);
}

// True if in
int		parallel_ray_cast(t_ray3d r, t_cylinder cylinder)
{
	double		d;
	t_vector3d	v_d;
	t_vector3d	rc;

	rc = minus_vec(r.origin, cylinder.position);
	d = dot_vec(rc, cylinder.center_line);
	v_d = minus_vec(rc, mul_vec_scalar(cylinder.center_line, d));
	d = module_vec(v_d);
	if (d <= (cylinder.diameter / 2))
		return (1);
	return (0);
}

double	*intersect_cylinder(t_ray3d r, void *obj)
{
	const t_cylinder	cylinder = *(t_cylinder*)obj;
	t_vector3d			v_d;
	double				d;
	double				*t;
	t_vector3d			v_o;

	if (!(t = (double*)malloc(sizeof(double) * 2)))
		return (0);
	t[0] = -1;
	t[1] = -1;
	if (module_vec(cross_vec(r.direction, cylinder.center_line)) == 0)
	{
		if (parallel_ray_cast(r, cylinder))
		{
			t[0] = HUGE;
			t[1] = -HUGE;
		}
		return (t);
	}
	v_d = unit_vec(cross_vec(r.direction, cylinder.center_line));
	d = fabs(dot_vec(minus_vec(r.origin, cylinder.position), v_d));
	if (d > (cylinder.diameter / 2))
		return (t);
	v_o = cross_vec(minus_vec(r.origin, cylinder.position), cylinder.center_line);
	t[0] = -dot_vec(v_o, v_d) / module_vec(v_d);
	v_o = unit_vec(cross_vec(v_d, cylinder.center_line));
	double s = fabs(sqrt(pow(cylinder.diameter / 2, 2) - pow(d, 2)) / dot_vec(r.direction, v_o));
	t[1] = t[0] + s;
	t[0] = t[0] - s;
	return (t);
}
