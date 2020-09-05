/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/05 13:59:13 by kdustin          ###   ########.fr       */
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
//realtime collision p233
double	*intersect_cylinder(t_ray3d r, void *obj)
{
	t_cylinder	cylinder = *(t_cylinder*)obj;
//	t_vector3d			v_d;
//	double				d;
	double				*t;
//	t_vector3d			v_o;
	t_point3d			q;
	t_vector3d			d;
	t_vector3d			m; //n = ray.direction
	double				discreminant;

	if (!(t = (double*)malloc(sizeof(double) * 2)))
		return (0);
	t[0] = -1;
	t[1] = -1;
	q = sum_vec(
		mul_vec_scalar(normalize(cylinder.center_line), cylinder.height),
		cylinder.position);
	d = minus_vec(q, cylinder.position);
	m = minus_vec(r.origin, cylinder.position);
	cylinder.md = dot_vec(m, d);
	cylinder.nd = dot_vec(r.direction, d);
	cylinder.dd = dot_vec(d, d);
//	if (cylinder.md < 0.0 && cylinder.md + cylinder.nd < 0.0)
//		return (t);
//	if (cylinder.md > cylinder.dd && cylinder.md + cylinder.nd > cylinder.dd)
//		return (t);
	cylinder.nn = dot_vec(r.direction, r.direction);
	cylinder.mn = dot_vec(m, r.direction);
	cylinder.a = cylinder.dd * cylinder.nn - cylinder.nd * cylinder.nd;
	cylinder.k = dot_vec(m, m) - pow(cylinder.diameter / 2 , 2);
	cylinder.c = cylinder.dd * cylinder.k - cylinder.md * cylinder.md;
	if (fabs(cylinder.a) < __DBL_EPSILON__)
	{
		if (cylinder.c > 0.0)
			return (t);
		if (cylinder.md < 0.0)
			t[0] = -cylinder.mn / cylinder.nn;
		else if (cylinder.md > cylinder.dd)
			t[0] = (cylinder.nd - cylinder.mn) / cylinder.nn;
		else
			t[0] = 0.0;
		return (t);
	}
	cylinder.b = cylinder.dd * cylinder.mn - cylinder.nd * cylinder.md;
	discreminant = cylinder.b * cylinder.b - cylinder.a * cylinder.c;
	if (discreminant < 0.0)
		return (t);
	t[0] = (-cylinder.b - sqrt(discreminant)) / cylinder.a;
	if (t[0] < 0.0)// || t[0] > 1.0)
	{
		t[0] = -1;
		return (t);
	}
	if (cylinder.md + t[0] * cylinder.nd < 0.0)
	{
		if (cylinder.nd <= 0.0)
		{
			t[0] = -1;
			return (t);
		}
		t[0] = -cylinder.md / cylinder.nd;
		if (cylinder.k + 2 * t[0] * (cylinder.mn + t[0] * cylinder.nn) <= 0.0)
			return (t);
		t[0] = -1;
		return (t);
	}
	else if (cylinder.md + t[0] * cylinder.nd > cylinder.dd)
	{
		if (cylinder.nd >= 0.0)
		{
			t[0] = -1;
			return (t);
		}
		t[0] = (cylinder.dd - cylinder.md) / cylinder.nd;
		if (cylinder.k + cylinder.dd - 2 * cylinder.md + t[0] * (2 * (cylinder.mn - cylinder.nd) + t[0] * cylinder.nn) <= 0.0)
			return (t);
		t[0] = -1;
		return (t);
	}
	return (t);
//	if (module_vec(cross_vec(r.direction, cylinder.center_line)) == 0)
//	{
//		if (parallel_ray_cast(r, cylinder))
//		{
//			t[0] = HUGE;
//			t[1] = -HUGE;
//		}
//		return (t);
//	}
//	v_d = normalize(cross_vec(r.direction, cylinder.center_line));
//	d = fabs(dot_vec(minus_vec(r.origin, cylinder.position), v_d));
//	if (d > (cylinder.diameter / 2))
//		return (t);
//	v_o = cross_vec(minus_vec(r.origin, cylinder.position), cylinder.center_line);
//	t[0] = -dot_vec(v_o, v_d) / module_vec(v_d);
//	v_o = normalize(cross_vec(v_d, cylinder.center_line));
//	double s = fabs(sqrt(pow(cylinder.diameter / 2, 2) - pow(d, 2)) / dot_vec(r.direction, v_o));
//	t[1] = t[0] + s;
//	t[0] = t[0] - s;
//	return (t);
}
