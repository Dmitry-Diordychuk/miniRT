/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:53:14 by kdustin           #+#    #+#             */
/*   Updated: 2020/09/19 23:14:16 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_vector3d	calculate_cylinder_normal(t_cylinder cylinder, t_point3d int_point, t_ray3d r)
{
	if (cylinder.closest_t == 0 || cylinder.closest_t == 1)
		return (normal_to_camera(div_vs(sub_v(sub_v(int_point, cylinder.position), mul_vs(cylinder.direction, dot_v(sub_v(int_point, cylinder.position), cylinder.direction))), cylinder.d/2), r.direction));
	return (normal_to_camera(cylinder.direction, r.direction));
}

void	*create_cylinder(t_point3d position, t_vector3d direction, double d, double h)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	cylinder->position = position;
	cylinder->direction = normalize(direction);
	cylinder->d = d;
	cylinder->h = h;
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

double	is_point_oncap(double t, t_ray3d r, t_cylinder c, t_point3d circle_cent)
{
	if (t >= 0 && module_v(sub_v(ray_func(r, t), circle_cent)) > c.d / 2)
		return (-1);
	return (t);
}

double	is_point_between(t_cylinder cylinder, t_ray3d r, t_vector3d b, double t)
{
	t_point3d	inter_point;
	double		s1;
	double		s2;

	inter_point = ray_func(r, t);
	s1 =
	fabs(dot_v(sub_v(cylinder.position, inter_point), cylinder.direction))
											/ module_v(cylinder.direction);
	s2 =
	fabs(dot_v(sub_v(b, inter_point), cylinder.direction))
											/ module_v(cylinder.direction);
	if (!(fabs(s1) < fabs(cylinder.h) && sign(s1) == sign(cylinder.h)
	&& fabs(s2) < fabs(cylinder.h) && sign(s2) == sign(cylinder.h)))
		return (-1);
	return (t);
}

int	choose_closest_point(double *t)
{
	int	comp_1;
	int comp_2;
	int result;

	if (t[0] < 0)
		comp_1 = t[1] < 0 ? -1 : 1;
	else if (t[1] < 0)
		comp_1 = 0;
	else
		comp_1 = t[0] < t[1] ? 0 : 1;
	if (t[2] < 0)
		comp_2 = t[3] < 0 ? -1 : 3;
	else if (t[3] < 0)
		comp_2 = 2;
	else
		comp_2 = t[2] < t[3] ? 2 : 3;
	if (comp_1 == -1)
		return (comp_2 == -1 ? -1 : comp_2);
	else if (comp_2 == -1)
		return (comp_1);
	return (t[comp_1] < t[comp_2] ? comp_1 : comp_2);
}

double	intersect_cylinder(t_ray3d r, void **obj)
{
	t_cylinder	*c;
	double		t[4];
	double		d;
	t_vector3d	v[3];
	t_plane		*p;

	c = (t_cylinder*)*obj;
	v[0] = normalize(cross_v(r.direction, c->direction));
	v[1] = sub_v(r.origin, c->position);
	if ((d = fabs(dot_v(v[1], v[0]))) > c->d / 2)
		return (-1);
	v[2] = sum_v(c->position, mul_vs(c->direction, c->h));
	v[1] = cross_v(v[1], c->direction);
	t[2] = -dot_v(v[1], v[0]) / module_v(cross_v(r.direction, c->direction));
	v[1] = normalize(cross_v(v[0], c->direction));
	t[3] = sqrt(pow(c->d/2, 2) - d * d) / dot_v(r.direction, v[1]);
	t[0] = is_point_between(*c, r, v[2], t[2] - t[3]);
	t[1] = is_point_between(*c, r, v[2], t[2] + t[3]);
	p = &(t_plane){normalize(c->direction), c->position};
	t[2] = is_point_oncap(intersect_plane(r, (void**)&p), r, *c, c->position);
	p->q = v[2];
	t[3] = is_point_oncap(intersect_plane(r, (void**)&p), r, *c, v[2]);
	c->closest_t = choose_closest_point(t);
	return (c->closest_t != -1 ? t[c->closest_t] : -1);
}
