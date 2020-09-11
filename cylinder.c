/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/11 15:23:04 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_vector3d	normal;

t_vector3d	calculate_cylinder_normal(t_cylinder cylinder, t_point3d int_point)
{
	return (normal);
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

int	sign(double n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	return (1);
}

void	ft_swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double	intersect_cylinder(t_ray3d r, void *obj)
{
	t_cylinder	cylinder = *(t_cylinder*)obj;
	double		t[4];
	double		d;
	t_vector3d	vec_d;
	t_vector3d	vec_o;
	t_vector3d	rc;
	t_vector3d	b;
	t_vector3d	D;
	t_plane		p;
	double		tbottom;
	double		ttop;
	t_point3d	h_bottom;
	t_point3d	h_top;
	double		s1;
	double		s2;
	double		s3;
	double		s4;
	t_point3d	hb;

	t[0] = -1;
	t[1] = -1;
	t[2] = -1;
	t[3] = -1;
	vec_d = normalize(cross_vec(r.direction, cylinder.center_line));
	if (module_vec(vec_d) == 0)
	{
		d = dot_vec(minus_vec(r.origin, cylinder.position), cylinder.center_line);
		D = minus_vec(minus_vec(r.origin, cylinder.position), mul_vec_scalar(cylinder.center_line, d));
		d = module_vec(D);
		return (__DBL_MIN__);
	}
	rc = minus_vec(r.origin, cylinder.position);
	d = fabs(dot_vec(rc, vec_d));
	b = sum_vec(cylinder.position, mul_vec_scalar(cylinder.center_line, cylinder.height));
	if (d > cylinder.diameter / 2)
		return (-1);
	vec_o = cross_vec(rc, cylinder.center_line);
	double tt = - dot_vec(vec_o, vec_d) / module_vec(cross_vec(r.direction, cylinder.center_line));
	vec_o = normalize(cross_vec(vec_d, cylinder.center_line));
	double		s = sqrt(pow(cylinder.diameter/2, 2) - d * d) / dot_vec(r.direction, vec_o);
	t[0] = tt - s;
	t[1] = tt + s;
	p.normal = normalize(cylinder.center_line);
	p.q = cylinder.position;
	tbottom = intersect_plane(r, (void*)&p);
	p.q = b;
	ttop = intersect_plane(r, (void*)&p);
	if (tbottom >= 0)
	{
		h_bottom = ray_param_func(r, tbottom);
		if (module_vec(minus_vec(h_bottom, cylinder.position)) > cylinder.diameter / 2)
			t[2] = -1;
		else
			t[2] = tbottom;
	}
	if (ttop >= 0)
	{
		h_top = ray_param_func(r, ttop);
		if (module_vec(minus_vec(h_top, b)) > cylinder.diameter / 2)
			t[3] = -1;
		else
			t[3] = ttop;
	}
	s1 = fabs(dot_vec(minus_vec(cylinder.position, ray_param_func(r, t[0])), cylinder.center_line)) / module_vec(cylinder.center_line);
	s2 = fabs(dot_vec(minus_vec(b, ray_param_func(r, t[0])), cylinder.center_line)) / module_vec(cylinder.center_line);
	if (!(fabs(s1) < fabs(cylinder.height) && sign(s1) == sign(cylinder.height) && fabs(s2) < fabs(cylinder.height) && sign(s2) == sign(cylinder.height)))
		t[0] = -1;
	s3 = fabs(dot_vec(minus_vec(cylinder.position, ray_param_func(r, t[1])), cylinder.center_line)) / module_vec(cylinder.center_line);
	s4 = fabs(dot_vec(minus_vec(b, ray_param_func(r, t[1])), cylinder.center_line)) / module_vec(cylinder.center_line);
	if (!(fabs(s3) < fabs(cylinder.height) && sign(s3) == sign(cylinder.height) && fabs(s4) < fabs(cylinder.height) && sign(s4) == sign(cylinder.height)))
		t[1] = -1;
	int	number_1;
	if (t[0] < 0)
		if (t[1] < 0)
			number_1 = -1;
		else
			number_1 = 1;
	else
		if (t[1] < 0)
			number_1 = 0;
		else
			number_1 = t[0] < t[1] ? 0 : 1;
	int number_2;
	if (t[2] < 0)
		if (t[3] < 0)
			number_2 = -1;
		else
			number_2 = 3;
	else
		if (t[3] < 0)
			number_2 = 2;
		else
			number_2 = t[2] < t[3] ? 2 : 3;
	int number_3;
	if (number_1 == -1)
		if (number_2 == -1)
			number_3 = -1;
		else
			number_3 = number_2;
	else
		if (number_2 == -1)
			number_3 = number_1;
		else
			number_3 = t[number_1] < t[number_2] ? number_1 : number_2;
	if (number_3 == 0 || number_3 == 1)
	{
		hb = minus_vec(ray_param_func(r, t[number_3]), cylinder.position);
		normal = calculate_plane_normal(div_vec_scalar(minus_vec(hb, mul_vec_scalar(cylinder.center_line, dot_vec(hb, cylinder.center_line))), cylinder.diameter/2), r.direction);
	}
	else if (number_3 == 2 || number_3 == 3)
	{
		normal = calculate_plane_normal(cylinder.center_line, r.direction);
	}
	if (number_3 != -1)
	{
		t[0] = t[number_3];
		t[1] = -1;
	}
	return (t[0]);
}
